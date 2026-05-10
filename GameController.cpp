#include "GameController.h"
#include "raylib.h"
#include <cstdlib>

GameController::GameController()
    : food(26, 26),
      snake1(5,  13, KEY_W, KEY_S, KEY_A, KEY_D),
      snake2(21, 13, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT) {
    gameOver = false;
    score1 = 0;
    score2 = 0;
    winner = 0;
    countdownTimer = 3.0f;
    mode  = GameMode::MENU;
    state = GameState::PLAYING;
    for (int i = 0; i < 5; i++)
        obstacles.push_back(Obstacle());
}

void GameController::reshuffleObstacles() {
    obstacles.clear();
    for (int i = 0; i < 5; i++)
        obstacles.push_back(Obstacle());
}

void GameController::resetGame() {
    snake1    = Snake(5,  13, KEY_W, KEY_S, KEY_A, KEY_D);
    snake2    = Snake(21, 13, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
    food      = Food(26, 26);
    gameOver  = false;
    score1    = 0;
    score2    = 0;
    winner    = 0;
    reshuffleObstacles();
}

//  AI Logic 
Direction GameController::getAIDirection() {
    Position head = snake2.getHead();
    Position food = this->food.getPosition();

    Direction preferred[4];
    int count = 0;

    if (food.x > head.x) preferred[count++] = RIGHT;
    if (food.x < head.x) preferred[count++] = LEFT;
    if (food.y > head.y) preferred[count++] = DOWN;
    if (food.y < head.y) preferred[count++] = UP;

    Direction all[4] = {UP, DOWN, LEFT, RIGHT};
    for (int i = 0; i < 4; i++) {
        bool already = false;
        for (int j = 0; j < count; j++)
            if (preferred[j] == all[i]) already = true;
        if (!already) preferred[count++] = all[i];
    }

    for (int i = 0; i < 4; i++) {
        Direction d = preferred[i];
        Position next = head;
        if (d == UP)    next.y--;
        if (d == DOWN)  next.y++;
        if (d == LEFT)  next.x--;
        if (d == RIGHT) next.x++;

        bool safe = true;
        if (next.x < 0 || next.x >= 26 || next.y < 0 || next.y >= 26) safe = false;
        if (snake2.containsPosition(next)) safe = false;
        if (snake1.containsPosition(next)) safe = false;
        for (int j = 0; j < (int)obstacles.size(); j++)
            if (next == obstacles[j].getPosition()) safe = false;

        if (safe) return d;
    }

    return snake2.getDirection();
}

void GameController::updateAI() {
    Direction aiDir = getAIDirection();
    snake2.changeDirection(aiDir);
    snake2.update();
}

//  handleMenuInput 
void GameController::handleMenuInput() {
    if (mode == GameMode::MENU) {
        if (IsKeyPressed(KEY_ONE)) {
            mode = GameMode::COUNTDOWN;
            countdownTimer = 3.0f;
            // store which mode to go to after countdown
            winner = 1;  // reuse winner as temp flag (1 = 1player, 2 = 2player)
        }
        if (IsKeyPressed(KEY_TWO)) {
            mode = GameMode::COUNTDOWN;
            countdownTimer = 3.0f;
            winner = 2;
        }
    }
    // R to restart from game over screen
    if (gameOver && IsKeyPressed(KEY_R)) {
        GameMode currentMode = mode;  // remember 1player or 2player
        resetGame();
        mode = GameMode::MENU; //go back to menu instead of countdown
        countdownTimer = 3.0f;
        winner = (currentMode == GameMode::ONE_PLAYER) ? 1 : 2;
    }
}

//  update 
void GameController::update() {
    if (mode == GameMode::MENU) return;

    if (mode == GameMode::COUNTDOWN) {
        countdownTimer -= GetFrameTime();
        if (countdownTimer <= 0) {
            if (winner == 1) mode = GameMode::ONE_PLAYER;
            else             mode = GameMode::TWO_PLAYER;
            winner = 0;  // reset winner
        }
        return;
    }

    if (gameOver) return;
    snake1.update();
    if (mode == GameMode::ONE_PLAYER)
        updateAI();
    else
        snake2.update();

    Position head1 = snake1.getHead();
    Position head2 = snake2.getHead();

    // Food collision
    if (head1 == food.getPosition()) {
        snake1.grow();
        score1 += food.getPoints();
        food.respawn();
        reshuffleObstacles();
    }
    if (head2 == food.getPosition()) {
        snake2.grow();
        score2 += food.getPoints();
        food.respawn();
        reshuffleObstacles();
    }

    food.update();

    // Wall collision
    bool p1Dead = (head1.x < 0 || head1.x >= 26 || head1.y < 0 || head1.y >= 26);
    bool p2Dead = (head2.x < 0 || head2.x >= 26 || head2.y < 0 || head2.y >= 26);

    // Self collision
    if (snake1.checkSelfCollision()) p1Dead = true;
    if (snake2.checkSelfCollision()) p2Dead = true;

    // Hit each other
    if (snake1.collidesWithOther(snake2)) p1Dead = true;
    if (snake2.collidesWithOther(snake1)) p2Dead = true;

    // Obstacle collision
    for (int i = 0; i < (int)obstacles.size(); i++) {
        if (head1 == obstacles[i].getPosition()) p1Dead = true;
        if (head2 == obstacles[i].getPosition()) p2Dead = true;
    }

    if (p1Dead || p2Dead) {
        gameOver = true;
        if      (p1Dead && !p2Dead) winner = 2;
        else if (p2Dead && !p1Dead) winner = 1;
        else                         winner = 0;
    }
}

//  draw 
void GameController::draw() {

    // MENU SCREEN
    if (mode == GameMode::MENU) {
        ClearBackground(BLACK);
        DrawText("SNAKE GAME",
                 400 - MeasureText("SNAKE GAME", 50)/2,
                 150, 50, GREEN);
        DrawText("Press 1  —  1 Player vs AI",
                 400 - MeasureText("Press 1  —  1 Player vs AI", 24)/2,
                 300, 24, WHITE);
        DrawText("Press 2  —  2 Players",
                 400 - MeasureText("Press 2  —  2 Players", 24)/2,
                 350, 24, WHITE);
        DrawText("P1: WASD   |   P2: Arrow Keys",
                 400 - MeasureText("P1: WASD   |   P2: Arrow Keys", 18)/2,
                 450, 18, DARKGRAY);
        return;
    }

    if (mode == GameMode::COUNTDOWN) {
        // draw empty grid while counting
        for (int i = 0; i <= 800; i += 30) {
            DrawLine(i, 0, i, 800, DARKGRAY);
            DrawLine(0, i, 800, i, DARKGRAY);
        }
        int count = (int)countdownTimer + 1;
        const char* txt = TextFormat("%i", count);
        DrawText(txt,
                400 - MeasureText(txt, 120)/2,
                280, 120, GREEN);
        DrawText("GET READY!",
                400 - MeasureText("GET READY!", 28)/2,
                420, 28, WHITE);
        return;
    }

    // GRID (replaces board.drawGrid())
    for (int i = 0; i <= 800; i += 30) {
        DrawLine(i, 0, i, 800, DARKGRAY);
        DrawLine(0, i, 800, i, DARKGRAY);
    }

    snake1.draw(GREEN, (Color){34, 139, 34, 255});

    if (mode == GameMode::ONE_PLAYER)
        snake2.draw(RED, (Color){180, 0, 0, 255});
    else
        snake2.draw(BLUE, (Color){0, 80, 180, 255});

    food.draw();
    for (int i = 0; i < (int)obstacles.size(); i++)
        obstacles[i].draw();

    // Scores
    DrawText(TextFormat("P1: %i", score1), 10, 10, 20, GREEN);
    if (mode == GameMode::ONE_PLAYER)
        DrawText(TextFormat("AI: %i", score2), 730, 10, 20, RED);
    else
        DrawText(TextFormat("P2: %i", score2), 730, 10, 20, BLUE);

    // Controls hint
    DrawText("WASD", 10, 780, 14, DARKGREEN);
    if (mode == GameMode::TWO_PLAYER)
        DrawText("Arrow Keys", 690, 780, 14, DARKBLUE);
    else
        DrawText("vs AI", 710, 780, 14, (Color){180,0,0,255});

    // GAME OVER overlay
    if (gameOver) {
        DrawRectangle(200, 300, 400, 160, (Color){0, 0, 0, 200});
        if (winner == 1)
            DrawText("PLAYER 1 WINS!", 245, 330, 36, GREEN);
        else if (winner == 2) {
            if (mode == GameMode::ONE_PLAYER)
                DrawText("AI WINS!", 310, 330, 36, RED);
            else
                DrawText("PLAYER 2 WINS!", 245, 330, 36, BLUE);
        } else {
            DrawText("DRAW!", 350, 330, 36, WHITE);
        }
        DrawText("Press R to play again", 230, 390, 18, LIGHTGRAY);
    }
}
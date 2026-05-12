//neha 
#include "GameController.h"
#include "raylib.h"
#include <cstdlib>
//constructor of gameController class
GameController::GameController()
    : food(26, 26),
    // x=5 and y=13 for snake1 starting point
      snake1(5,  13, KEY_W, KEY_S, KEY_A, KEY_D),
      //x=21,y=13 for snake2 starting point
      snake2(21, 13, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT) {
    gameOver = false;
    score1 = 0;
    score2 = 0;
    winner = 0;
    //counter starting at 3.0 float
    countdownTimer = 3.0f;
    mode  = GameMode::MENU;
    state = GameState::PLAYING;
    for (int i = 0; i < 5; i++)
        obstacles.push_back(Obstacle());
}

void GameController::reshuffleObstacles() {
    //to reshuffle first clear obstacles
    obstacles.clear();
    for (int i = 0; i < 5; i++)
        obstacles.push_back(Obstacle());
}

void GameController::resetGame() {
    //after reset intialize 
    snake1    = Snake(5,  13, KEY_W, KEY_S, KEY_A, KEY_D);
    snake2    = Snake(21, 13, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
    food      = Food(26, 26);
    gameOver  = false;
    score1    = 0;
    score2    = 0;
    winner    = 0;
    reshuffleObstacles();
}


Direction GameController::getAIDirection() {
    Position head = snake2.getHead();//getting snakes direction
    Position food = this->food.getPosition();//foods direction
     //we add our preferred direction first in preferred[i] according to where food is
    Direction preferred[4];
    int count = 0;
   //if food to right
    if (food.x > head.x) preferred[count++] = RIGHT;
    //food to left
    if (food.x < head.x) preferred[count++] = LEFT;
    //food down
    if (food.y > head.y) preferred[count++] = DOWN;
    //food up
    if (food.y < head.y) preferred[count++] = UP;

    Direction all[4] = {UP, DOWN, LEFT, RIGHT};
    for (int i = 0; i < 4; i++) {
        bool already = false;
        for (int j = 0; j < count; j++)
            if (preferred[j] == all[i]) already = true;
            //after preferred if any direction missing we add them
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

//for updating AI direction ,we call getAIDirection()
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
            winner = 1;
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

void GameController::draw() {
    //Menu Screen
    if (mode == GameMode::MENU) {
        ClearBackground(BLACK);

        //40 is the font of Serpent Arena,130 y location of in pixels,colour green
        DrawText("SERPENT ARENA",
                400 - MeasureText("SERPENT ARENA", 40)/2,
                130, 40, GREEN);

        // Mode selection
        DrawText("Press 1 for 1 Player vs AI",
                400 - MeasureText("Press 1 for 1 Player vs AI", 20)/2,
                200, 20, WHITE);
        DrawText("Press 2 for 2 Players",
                400 - MeasureText("Press 2 for 2 Players", 20)/2,
                230, 20, WHITE);
        DrawText("P1: WASD   |   P2: Arrow Keys",
                400 - MeasureText("P1: WASD   |   P2: Arrow Keys", 16)/2,
                260, 16, DARKGRAY);

        // Divider 
        DrawLine(200, 290, 600, 290, DARKGRAY);

        DrawText("HOW TO PLAY",
                400 - MeasureText("HOW TO PLAY", 20)/2,
                305, 20, YELLOW);

        // sign for food and there points
        DrawCircle(220, 345, 10, RED);
        DrawText("Normal Food  +10 pts", 245, 338, 18, WHITE);
        //special food 
        DrawRectangle(205, 368, 20, 20, GOLD);
        DrawText("Special Food  +20 pts (disappears!)", 245, 371, 18, WHITE);
        //obstacles sign
        DrawRectangle(205, 403, 20, 20, DARKGRAY);
        DrawRectangle(207, 405, 16, 16, GRAY);
        DrawText("Obstacle  (reshuffles each food)", 245, 406, 18, WHITE);

        // Divider-Horizontal line
        DrawLine(200, 435, 600, 435, DARKGRAY);
       //A few precautions
        DrawText("Don't hit the wall!",
         400 - MeasureText("Don't hit the wall!", 16)/2,
         450, 16, DARKGRAY);
        DrawText("Hit the other snake to win!",
        400 - MeasureText("Hit the other snake to win!", 16)/2,
        472, 16, DARKGRAY);
        DrawText("Press R after game over to restart",
        400 - MeasureText("Press R after game over to restart", 16)/2,
        494, 16, DARKGRAY);
         return;
    }

    //countdown
    if (mode == GameMode::COUNTDOWN) {
        //horizontal and vertical lines during countdown
        for (int i = 0; i <= 800; i += 30) {
            DrawLine(i, 0, i, 800, DARKGRAY);
            DrawLine(0, i, 800, i, DARKGRAY);
        }
        //converts decimal to integer
        int count = (int)countdownTimer + 1;
        //converts countdown to char
        const char* txt = TextFormat("%i", count);
        //countdown shown in green colour
        DrawText(txt,
                400 - MeasureText(txt, 120)/2,
                280, 120, GREEN);
                //get ready shown in white colour font 28
        DrawText("GET READY!",
                400 - MeasureText("GET READY!", 28)/2,
                420, 28, WHITE);
        return;
    }
    
    //board of the game drawing after countdown done
    for (int i = 0; i <= 800; i += 30) {
        DrawLine(i, 0, i, 800, DARKGRAY);
        DrawLine(0, i, 800, i, DARKGRAY);
    }
    //snake1 drawn in green colour
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

    // WASD written in the bottom left corner
    DrawText("WASD", 10, 780, 14, DARKGREEN);
    if (mode == GameMode::TWO_PLAYER)
    //arrow keys written at the bottom right
        DrawText("Arrow Keys", 690, 780, 14, DARKBLUE);
    else
    //vs AI written on the bottom right if game with AI
        DrawText("vs AI", 710, 780, 14, (Color){180,0,0,255});

    //game results
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
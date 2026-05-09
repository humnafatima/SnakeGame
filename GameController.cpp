#include "GameController.h"

#include "raylib.h"

 

GameController::GameController()

    : food(20, 20),

      snake1(5,  10, KEY_W, KEY_S, KEY_A, KEY_D),

      snake2(15, 10, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT) {

    gameOver = false;

    score1 = 0;

    score2 = 0;

    winner = 0;

    for (int i = 0; i < 5; i++)

        obstacles.push_back(Obstacle());

}

 

void GameController::reshuffleObstacles() {

    obstacles.clear();

    for (int i = 0; i < 5; i++)

        obstacles.push_back(Obstacle());

}

 

void GameController::update() {

    if (gameOver) return;

 

    snake1.update();

    snake2.update();

 

    Position head1 = snake1.getHead();

    Position head2 = snake2.getHead();

 

    // Food collision

    if (head1 == food.getPosition()) {

        snake1.grow();

        score1 += food.getPoints();

        food.respawn();

        reshuffleObstacles();  // obstacles move when food eaten

    }

    if (head2 == food.getPosition()) {

        snake2.grow();

        score2 += food.getPoints();

        food.respawn();

        reshuffleObstacles();

    }

 

    food.update();

 

    // Wall collision

    bool p1Dead = (head1.x < 0 || head1.x >= 20 || head1.y < 0 || head1.y >= 20);

    bool p2Dead = (head2.x < 0 || head2.x >= 20 || head2.y < 0 || head2.y >= 20);

 

    // Self collision

    if (snake1.checkSelfCollision()) p1Dead = true;

    if (snake2.checkSelfCollision()) p2Dead = true;

 

    // Hit each other

    if (snake1.collidesWithOther(snake2)) p1Dead = true;

    if (snake2.collidesWithOther(snake1)) p2Dead = true;

 

    // Obstacle collision

    for (int i = 0; i < obstacles.size(); i++) {

        if (head1 == obstacles[i].getPosition()) p1Dead = true;

        if (head2 == obstacles[i].getPosition()) p2Dead = true;

    }

 

    if (p1Dead || p2Dead) {

        gameOver = true;

        if      (p1Dead && !p2Dead) winner = 2;

        else if (p2Dead && !p1Dead) winner = 1;

        else                         winner = 0;  // draw

    }

}

 

void GameController::draw() {

    board.drawGrid();

    snake1.draw(GREEN,  (Color){34, 139, 34, 255});

    snake2.draw(BLUE,   (Color){0,  80,  180, 255});

    food.draw();

    for (int i = 0; i < obstacles.size(); i++)

        obstacles[i].draw();

 

    // Scores

    DrawText(TextFormat("P1: %i", score1), 10,  10, 20, GREEN);

    DrawText(TextFormat("P2: %i", score2), 480, 10, 20, BLUE);

    DrawText("P1: WASD",       10,  580, 14, DARKGREEN);

    DrawText("P2: Arrow Keys", 430, 580, 14, DARKBLUE);

 

    if (gameOver) {

        DrawRectangle(100, 220, 400, 160, (Color){0,0,0,180});

        if (winner == 1)

            DrawText("PLAYER 1 WINS!", 145, 250, 36, GREEN);

        else if (winner == 2)

            DrawText("PLAYER 2 WINS!", 145, 250, 36, BLUE);

        else

            DrawText("DRAW!", 230, 250, 36, WHITE);

        DrawText("Close and rerun to play again", 130, 310, 18, LIGHTGRAY);

    }

}
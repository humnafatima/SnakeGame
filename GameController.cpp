#include "GameController.h"
#include "raylib.h"
GameController::GameController(){
    gameOver=false;
    score=0;
    for(int i=0;i<5;i++){
        obstacles.push_back(Obstacle());
    }
}

void GameController::update(){
    snake.update();
    Position head=snake.getHead();
    if(head==food.getPosition()){
        snake.grow();
        if(food.isSpecial())
        score=score+20;
        else
        score=score+10;
        food.generate();
    }
    if(head.x<0||head.x>=20||head.y<0||head.y>=20){
        gameOver=true;
    }
    if(snake.checkSelfCollision()){
        gameOver=true;
    }
    for(int i=0;i<obstacles.size();i++){
      if(head==obstacles[i].getPosition()){
        gameOver=true;
      }
    }
}
void GameController::draw(){
    board.drawGrid();
    snake.draw();
    food.draw();
    for(int i=0;i<obstacles.size();i++){
        obstacles[i].draw();
    }
    DrawText(TextFormat("Score %i",score),10,10,20,WHITE);
    if(gameOver){
        DrawText("GAME OVER",200,250,40,RED);
    }
}
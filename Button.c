/*******************************************************************************************
*
*   raylib [textures] example - Image loading and texture creation
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <stdio.h>
#include "raylib.h"
#include <time.h>

//Check if mouseOver button is click buttonRec or not return btnState
int IsClicked(bool mouseOn){
    int btnState = 0;
    if(mouseOn){
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btnState = 2;
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) btnState = 1;
    }
    return btnState;
}

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
} 

//Check if button is over given buttonRec or not return bool
bool IsMouseOver(Vector2 mousePos, Rectangle srcRec){
    bool mouseOn;
    if(CheckCollisionPointRec(mousePos, srcRec)) mouseOn = true;
    else mouseOn = false;
    return mouseOn;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Snake Ladder - Computer programming");
    
    Image btnImg = LoadImage("src/img/btn.png");
    
    Texture2D rollBtn = LoadTexture("src/img/roll.png");
    Texture2D battleBtn = LoadTexture("src/img/roll.png");
    Texture2D menuBg = LoadTexture("src/img/menu.png");
    Texture2D backGround = LoadTexture("src/img/bg.png");
    Texture2D startBtn = LoadTextureFromImage(btnImg);
    
    int boardPosX[40] = {-250, -340, -430, -520, -610, -700, -790, -880, -880, -880, -790, -700, -610, -520, -430, -340, -250, -160, -70, -70, -70, -160, -250, -340, -430, -520, -610, -700, -790, -880, -880, -880, -790, -700, -610, -520, -430, -340, -250, -160};
    int boardPosY[40] = {-630, -630, -630, -630, -630, -630, -630, -630, -555, -485, -485, -485, -485, -485, -485, -485, -485, -485, -485, -410, -335, -335, -335, -335, -335, -335, -335, -335, -335, -335, -260, -185, -185, -185, -185, -185, -185, -185, -185, -185};
    
    int rollFrameHeight = rollBtn.height / 2;
   
    Rectangle greenRec = {323, 620, 87, 70};
    Rectangle startBtnRec = {0, 0, startBtn.width, startBtn.height};
    Rectangle rollBtnRec = {0, 0, rollBtn.width, rollFrameHeight};
    Rectangle battleBtnRec = {0, 0, battleBtn.width, rollFrameHeight};
    Rectangle Char1 = {0, 0, 50, 50};
    
    Rectangle startBtnBound = {screenWidth / 2 - startBtn.width / 2, screenHeight / 4, startBtn.width, startBtn.height};
    Rectangle rollBtnBound = {1030, 570, rollBtn.width, rollFrameHeight};
    Rectangle battleBtnBound = {1025, 25, battleBtn.width, rollFrameHeight};
    
    bool gameStart = false, battleBegin = false, playerRoll = false, battleDone = false, delayWin = false;
    bool mouseOn1, mouseOn2, mouseOn3, mouseOn4;
    
    int btnState = 0;
    int randNum, randNumBattle;
    int playerPos[4];
    int playerPlay, playerTurn=0, loser;
    int samePos = 0, player1Randnum, player2Randnum, clickBattle=0;
    int framesCounter = 0, currentFrame = 0;
    
    char randStr[3] = "", player1Randstr[3] = "", player2Randstr[3] = "", playerPosStr[4][3];
    
    SetTargetFPS(60);
    playerPos[0] = 0;
    playerPos[1] = 0;
    playerPos[2] = 0;
    playerPos[3] = 0;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        Vector2 mousePos = GetMousePosition();
        mouseOn1 = IsMouseOver(mousePos, startBtnBound);
        mouseOn2 = IsMouseOver(mousePos, rollBtnBound);
        mouseOn3 = IsMouseOver(mousePos, battleBtnBound);
        
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            SetWindowPosition(50, 50);
        }
        
        if(playerTurn > 3){
            playerTurn = 0;
        }
        
         if (framesCounter >= (60/8)){
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5){
                currentFrame = 0;
                battleBegin = false;
                playerPos[playerTurn] -= 1;
                clickBattle = 0;
            }
            
        }
        
        // Draw
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            if(gameStart == true){
                
                DrawTexture(backGround, 0, 0, WHITE);
                DrawText(randStr, 1130, 500, 50, BLACK);
                if(battleBegin == true){
                    DrawTextureRec(battleBtn, battleBtnRec, (Vector2){battleBtnBound.x, battleBtnBound.y}, WHITE);
                    if(IsClicked(mouseOn3) == 1){
                        battleBtnRec.y = 0;
                        if(clickBattle == 0){
                            randNumBattle = GetRandomValue(1, 6);
                            player1Randnum = randNumBattle;
                            sprintf(player1Randstr, "%d", randNumBattle);
                            clickBattle = 1;
                            randNumBattle = GetRandomValue(1, 6);
                            player2Randnum = randNumBattle;
                            sprintf(player2Randstr, "%d", randNumBattle);
                        }
                    }else if(IsClicked(mouseOn3) == 2) battleBtnRec.y = rollFrameHeight;
                    if(clickBattle == 0){
                        *player1Randstr = "?";
                        *player2Randstr = "?";
                    }
                    DrawText(player1Randstr, 100, 20, 50, BLACK);
                    DrawText(player2Randstr, 200, 20, 50, BLACK);
                    if(clickBattle == 1){
                            battleBtnRec.y = 0;
                            DrawTextureRec(battleBtn, battleBtnRec, (Vector2){battleBtnBound.x, battleBtnBound.y}, WHITE);
                            if(player1Randnum > player2Randnum){
                                playerPos[playerTurn] -= 1;
                                clickBattle = 0;
                                battleBegin = false;
                                battleDone = true;
                            }else if(player2Randnum > player1Randnum){
                                playerPos[samePos] -= 1;
                                clickBattle = 0;
                                battleBegin = false;
                                battleDone = true;
                            }else{
                                clickBattle = 0;
                                player1Randnum = 0;
                                player2Randnum = 0;
                                *player1Randstr = "?";
                                *player2Randstr = "?";
                            }
                            delayWin = true;
                    }
                }else{
                    DrawTextureRec(rollBtn, rollBtnRec, (Vector2){rollBtnBound.x, rollBtnBound.y}, WHITE);
                    if(IsClicked(mouseOn2) == 1){
                        rollBtnRec.y = 0;
                        randNum = GetRandomValue(1, 6);
                        playerPos[playerTurn] = playerPos[playerTurn] + randNum;
                        sprintf(randStr, "%d", randNum);
                        playerRoll = true;
                    }else if(IsClicked(mouseOn2) == 2) rollBtnRec.y = rollFrameHeight;
                }
                
                DrawText(randStr, 1130, 500, 50, BLACK);
                if(playerPos[playerTurn] > 39) playerPos[playerTurn] = 39 - (playerPos[playerTurn] % 39);

                DrawRectanglePro(Char1, (Vector2){boardPosX[playerPos[0]], boardPosY[playerPos[0]]}, 0, BLACK);
                DrawRectanglePro(Char1, (Vector2){boardPosX[playerPos[1]], boardPosY[playerPos[1]]}, 0, RED);
                DrawRectanglePro(Char1, (Vector2){boardPosX[playerPos[2]], boardPosY[playerPos[2]]}, 0, GREEN);
                DrawRectanglePro(Char1, (Vector2){boardPosX[playerPos[3]], boardPosY[playerPos[3]]}, 0, BLUE);
                
                sprintf(playerPosStr[0], "%d", playerPos[0]);
                sprintf(playerPosStr[1], "%d", playerPos[1]);
                sprintf(playerPosStr[2], "%d", playerPos[2]);
                sprintf(playerPosStr[3], "%d", playerPos[3]);
            
                DrawText(playerPosStr[0], 1030, 200, 40, BLACK);
                DrawText(playerPosStr[1], 1030, 300, 40, RED);
                DrawText(playerPosStr[2], 1030, 400, 40, GREEN);
                DrawText(playerPosStr[3], 1030, 500, 40, BLUE);
                
                for(int i=0; i<=3; i++){
                    if(playerPos[playerTurn] == playerPos[i] && i != playerTurn && playerPos[playerTurn] != 0){
                        battleBegin = true;
                        samePos = i;
                        playerRoll = false;
                        battleDone = false;
                    }
                }
                
                
    
                
                
                
                
                
                
                
                
                
                
                
            }else{
                DrawTexture(menuBg, 0, 0, WHITE);
                DrawTextureRec(startBtn, startBtnRec, (Vector2){startBtnBound.x, startBtnBound.y}, WHITE);
                if(IsClicked(mouseOn1) == 2){
                    DrawTextureRec(startBtn, startBtnRec, (Vector2){startBtnBound.x, startBtnBound.y}, BLACK);
                }else if(IsClicked(mouseOn1) == 1){
                    gameStart = true;
                }
            }
        EndDrawing();
        if(delayWin) delay(1);
        delayWin = false;
        if(playerRoll == true || battleDone == true){
            playerTurn += 1;
            playerRoll = false;
            battleDone = false;
        }
    }
    
    UnloadImage(btnImg);
    UnloadTexture(rollBtn);
    UnloadTexture(menuBg);
    UnloadTexture(startBtn);
    UnloadTexture(backGround);

    CloseWindow();

    return 0;
}
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
    Texture2D menuBg = LoadTexture("src/img/menu.png");
    Texture2D backGround = LoadTexture("src/img/bg.png");
    Texture2D startBtn = LoadTextureFromImage(btnImg);
    
    int boardPosX[40] = {-250, -340, -430, -520, -610, -700, -790, -880, -880, -880, -790, -700, -610, -520, -430, -340, -250, -160, -70, -70, -70, -160, -250, -340, -430, -520, -610, -700, -790, -880, -880, -880, -790, -700, -610, -520, -430, -340, -250, -160};
    int boardPosY[40] = {-630, -630, -630, -630, -630, -630, -630, -630, -555, -485, -485, -485, -485, -485, -485, -485, -485, -485, -485, -410, -335, -335, -335, -335, -335, -335, -335, -335, -335, -335, -260, -185, -185, -185, -185, -185, -185, -185, -185, -185};
    
    int rollFrameHeight = rollBtn.height / 2;
   
    Rectangle greenRec = {323, 620, 87, 70};
    Rectangle startBtnRec = {0, 0, startBtn.width, startBtn.height};
    Rectangle rollBtnRec = {0, 0, rollBtn.width, rollFrameHeight};
    Rectangle Char1 = {0, 0, 50, 50};
    
    Rectangle startBtnBound = {screenWidth / 2 - startBtn.width / 2, screenHeight / 4, startBtn.width, startBtn.height};
    Rectangle rollBtnBound = {1030, 570, rollBtn.width, rollFrameHeight};
    
    bool gameStart = false;
    bool mouseOn1, mouseOn2, mouseOn3, mouseOn4;
    
    int btnState = 0;
    int randNum;
    int playerPos[4];
    int playerPlay, playerTurn;
    
    char randStr[3] = "";
    
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
        
        playerTurn = 0;
        
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            SetWindowPosition(50, 50);
        }
        
        // Draw
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            if(gameStart == true){
                DrawTexture(backGround, 0, 0, WHITE);
                DrawTextureRec(rollBtn, rollBtnRec, (Vector2){rollBtnBound.x, rollBtnBound.y}, WHITE);
                if(IsClicked(mouseOn2) == 1){
                   rollBtnRec.y = 0;
                   randNum = GetRandomValue(1, 6);
                   playerPos[playerTurn] = playerPos[playerTurn] + randNum;
                   sprintf(randStr, "%d", randNum);
                }else if(IsClicked(mouseOn2) == 2) rollBtnRec.y = rollFrameHeight;
                if(playerPos[playerTurn] > 39) playerPos[playerTurn] = 39 - (playerPos[playerTurn] % 39);

                DrawRectanglePro(Char1, (Vector2){boardPosX[playerPos[playerTurn]], boardPosY[playerPos[playerTurn]]}, 0, BLACK);
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
        
    }
    
    UnloadImage(btnImg);
    UnloadTexture(rollBtn);
    UnloadTexture(menuBg);
    UnloadTexture(startBtn);
    UnloadTexture(backGround);

    CloseWindow();

    return 0;
}
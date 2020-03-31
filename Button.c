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
int Button(bool mouseOn, Rectangle buttonRec, Texture2D btn, Vector2 pos){
    int btnState = 0;
    DrawTextureRec(btn, buttonRec, pos, WHITE);
    if(mouseOn){
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btnState = 2;
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) btnState = 1;
    }else{
        btnState = 0;
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
    Texture2D backGround = LoadTexture("src/img/bg.png");
    Texture2D startBtn = LoadTextureFromImage(btnImg);
    
    int boardPosX[6] = {-560, -490, -420, -350, -280, -210};
    int boardPosY[6] = {-530, -530, -530, -530, -530, -530};
    
    int rollFrameHeight = rollBtn.height / 2;
   
    Rectangle startBtnRec = {0, 0, startBtn.width, startBtn.height};
    Rectangle rollBtnRec = {0, 0, rollBtn.width, rollFrameHeight};
    Rectangle Char1 = {0, 0, 50, 50};
    
    Rectangle startBtnBound = {screenWidth / 2 - startBtn.width / 2, screenHeight / 4, startBtn.width, startBtn.height};
    Rectangle rollBtnBound = {1030, 570, rollBtn.width, rollFrameHeight};
    
    bool gameStart = false;
    bool mouseOn1, mouseOn2, mouseOn3, mouseOn4;
    int btnState = 0;
    int randNum;
    char randStr[3] = "";
    int framesCounter = 0;
    int currentFrames = 0;
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        framesCounter++;
        
        Vector2 mousePos = GetMousePosition();
        mouseOn1 = IsMouseOver(mousePos, startBtnBound);
        mouseOn2 = IsMouseOver(mousePos, rollBtnBound);
        
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            SetWindowPosition(50, 50);
        }
        
        if( framesCounter >= (60/8) && gameStart == true){
            framesCounter = 0;
            currentFrames++;
            if(currentFrames > 5) currentFrames = 0;
        }
        // Draw
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            if(gameStart == true){
                DrawTexture(backGround, 0, 0, WHITE);
                if(Button(mouseOn2, rollBtnRec, rollBtn, (Vector2){rollBtnBound.x, rollBtnBound.y}) == 1){
                   randNum = GetRandomValue(1, 6);
                   sprintf(randStr, "%d", randNum);
                }
                if(Button(mouseOn2, rollBtnRec, rollBtn, (Vector2){rollBtnBound.x, rollBtnBound.y}) == 2) rollBtnRec.y = rollFrameHeight;
                else rollBtnRec.y = 0;
                
                DrawText(randStr, 850, 200, 20, BLACK);
                DrawRectanglePro(Char1, (Vector2){boardPosX[currentFrames], boardPosY[currentFrames]}, 0, BLACK);
            }else{
                gameStart = Button(mouseOn1, startBtnRec, startBtn, (Vector2){startBtnBound.x, startBtnBound.y});
            }
        EndDrawing();
        
    }
    
    UnloadImage(btnImg);
    UnloadTexture(rollBtn);
    UnloadTexture(startBtn);
    UnloadTexture(backGround);

    CloseWindow();

    return 0;
}
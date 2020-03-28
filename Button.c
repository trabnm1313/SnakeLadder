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

#include "raylib.h"

//Check if mouseOver button is click buttonRec or not return btnState
int Button(bool mouseOn, Rectangle buttonRec, Texture2D btn, Vector2 pos){
    int btnState = 0;
    DrawTextureRec(btn, buttonRec, pos, WHITE);
    if(mouseOn){
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            DrawTextureRec(btn, buttonRec, pos, BLACK);
        }
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
    
    Image bg = LoadImage("src/img/bg.png");
    Image btnImg = LoadImage("src/img/btn.png");
    
    ImageResize(&bg, 800, 600);
    Texture2D backGround = LoadTextureFromImage(bg);
    Texture2D startBtn = LoadTextureFromImage(btnImg);
    
   
    Rectangle startBtnRec = {0, 0, startBtn.width, startBtn.height};
    Rectangle randBtnRec = {0, 0, startBtn.width, startBtn.height};
    
    Rectangle startBtnBound = {screenWidth / 2 - startBtn.width / 2, screenHeight / 4, startBtn.width, startBtn.height};
    Rectangle randBtnBound = {850, 50, startBtn.width, startBtn.height};
    
    bool gameStart = false;
    bool mouseOn1, mouseOn2, mouseOn3, mouseOn4;
    int btnState = 0;
    int randNum;
    char randStr[3] = "";
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Vector2 mousePos = GetMousePosition();
        mouseOn1 = IsMouseOver(mousePos, startBtnBound);
        mouseOn2 = IsMouseOver(mousePos, randBtnBound);
        
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            SetWindowPosition(50, 50);
        }
        // Draw
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            if(gameStart == true){
                DrawTexture(backGround, 0, 0, WHITE);
                if(Button(mouseOn2, randBtnRec, startBtn, (Vector2){randBtnBound.x, randBtnBound.y})){
                   randNum = GetRandomValue(1, 6);
                   sprintf(randStr, "%d", randNum);
                }
                DrawText(randStr, 850, 200, 20, BLACK);
            }else{
                gameStart = Button(mouseOn1, startBtnRec, startBtn, (Vector2){startBtnBound.x, startBtnBound.y});
            }

            
        EndDrawing();
        
    }
    
    UnloadImage(bg);
    UnloadImage(btnImg);
    UnloadTexture(startBtn);
    UnloadTexture(backGround);

    CloseWindow();

    return 0;
}
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
    if(mouseOn){
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btnState = 1;
        else btnState = 2;
        if(btnState==1) DrawTextureRec(btn, buttonRec, pos, BLACK);
        else if(btnState==2) DrawTextureRec(btn, buttonRec, pos, WHITE);
        }else{
            DrawTextureRec(btn, buttonRec, pos, WHITE);
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
    Texture2D btn = LoadTextureFromImage(btnImg);
    
    
    Rectangle buttonRec1 = {0, 0, btn.width, btn.height};
    Rectangle buttonRec2 = {0, 0, btn.width, btn.height};
    Rectangle buttonRec3 = {0, 0, btn.width, btn.height};
    Rectangle buttonRec4 = {0, 0, btn.width, btn.height};
    
    Rectangle buttonBound1 = {850, 50, btn.width, btn.height};
    Rectangle buttonBound2 = {850, 200, btn.width, btn.height};
    Rectangle buttonBound3 = {850, 350, btn.width, btn.height};
    Rectangle buttonBound4 = {850, 500, btn.width, btn.height};
    
    bool mouseOn1, mouseOn2, mouseOn3, mouseOn4;
    int btnState = 0;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Vector2 mousePos = GetMousePosition();
        mouseOn1 = IsMouseOver(mousePos, buttonBound1);
        mouseOn2 = IsMouseOver(mousePos, buttonBound2);
        mouseOn3 = IsMouseOver(mousePos, buttonBound3);
        mouseOn4 = IsMouseOver(mousePos, buttonBound4);
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            SetWindowPosition(50, 50);
        }
        // Draw
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            DrawTexture(backGround, 0, 0, WHITE);
            Button(mouseOn1, buttonRec1, btn, (Vector2){buttonBound1.x, buttonBound1.y});
            Button(mouseOn2, buttonRec2, btn, (Vector2){buttonBound2.x, buttonBound2.y});
            Button(mouseOn3, buttonRec3, btn, (Vector2){buttonBound3.x, buttonBound3.y});
            Button(mouseOn4, buttonRec4, btn, (Vector2){buttonBound4.x, buttonBound4.y});

            
        EndDrawing();
        
    }
    
    UnloadImage(bg);
    UnloadImage(btnImg);
    UnloadTexture(btn);
    UnloadTexture(backGround);

    CloseWindow();

    return 0;
}
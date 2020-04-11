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
    
    //Image variable.
    Image btnImg = LoadImage("src/img/btn.png");
    
    //Texture variable.
    Texture2D rollBtn = LoadTexture("src/img/roll.png");
    Texture2D battleBtn = LoadTexture("src/img/roll.png");
    Texture2D menuBg = LoadTexture("src/img/menu.png");
    Texture2D backGround = LoadTexture("src/img/bg.png");
    Texture2D startBtn = LoadTextureFromImage(btnImg);
    
    //Color Array.
    Color playerColor[4];
    
    //board slot position.
    int boardPosX[40] = {-250, -340, -430, -520, -610, -700, -790, -880, -880, -880, -790, -700, -610, -520, -430, -340, -250, -160, -70, -70, -70, -160, -250, -340, -430, -520, -610, -700, -790, -880, -880, -880, -790, -700, -610, -520, -430, -340, -250, -160};
    int boardPosY[40] = {-630, -630, -630, -630, -630, -630, -630, -630, -555, -485, -485, -485, -485, -485, -485, -485, -485, -485, -485, -410, -335, -335, -335, -335, -335, -335, -335, -335, -335, -335, -260, -185, -185, -185, -185, -185, -185, -185, -185, -185};
    
    //Frame height of button.
    int rollFrameHeight = rollBtn.height / 2;
   
    //Rectangle Rec src.
    Rectangle playerSelectRec[3];
    Rectangle startBtnRec = {0, 0, startBtn.width, startBtn.height};
    Rectangle rollBtnRec = {0, 0, rollBtn.width, rollFrameHeight};
    Rectangle battleBtnRec = {0, 0, battleBtn.width, rollFrameHeight};
    Rectangle Char1 = {0, 0, 50, 50};
    
    //Rectangle bound src.
    Rectangle startBtnBound = {screenWidth / 2 - startBtn.width / 2, screenHeight / 4, startBtn.width, startBtn.height};
    Rectangle rollBtnBound = {1030, 570, rollBtn.width, rollFrameHeight};
    Rectangle battleBtnBound = {1025, 25, battleBtn.width, rollFrameHeight};
    
    //Game state and true/false variable.
    bool gameStart = false, battleBegin = false, playerRoll = false, battleDone = false, delayWin = false;
    bool mouseOn1, mouseOn2, mouseOn3, mouseOnPlayerSelect[3];
    
    //Integer variable.
    int btnState = 0;
    int randNum, randNumBattle;
    int playerPos[4], playerNum=2;
    int playerPlay, playerTurn=0, loser;
    int samePos = 0, player1Randnum, player2Randnum, clickBattle=0;
    
    //Character/String variable.
    char randStr[3] = "", player1Randstr[3] = "", player2Randstr[3] = "", playerPosStr[4][3];
    
    SetTargetFPS(60);
    
    //Init.
    playerPos[0] = 0;
    playerPos[1] = 0;
    playerPos[2] = 0;
    playerPos[3] = 0;
    
    playerSelectRec[0] = (Rectangle){850, 30, 100, 50};
    playerSelectRec[1] = (Rectangle){1000, 30, 100, 50};
    playerSelectRec[2] = (Rectangle){1150, 30, 100, 50};
    
    playerColor[0] = (Color){ 0, 0, 0, 255 };
    playerColor[1] = (Color){ 230, 41, 55, 255 };
    playerColor[2] = (Color){ 0, 228, 48, 255 };
    playerColor[3] = (Color){ 0, 121, 241, 255 };
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Get mouse position to mousePos.
        Vector2 mousePos = GetMousePosition();
        //Check collision between mousePos and button/rectangle, return bool.
        mouseOn1 = IsMouseOver(mousePos, startBtnBound);
        mouseOn2 = IsMouseOver(mousePos, rollBtnBound);
        mouseOn3 = IsMouseOver(mousePos, battleBtnBound);
        for(int i=0; i<3; i++){
            mouseOnPlayerSelect[i] = IsMouseOver(mousePos, playerSelectRec[i]);
        }
        
        //Check for "F11" is press and toggle fullscreen mode.
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            SetWindowPosition(50, 50);
        }
        if(IsKeyPressed(KEY_P)){
            gameStart = false;
            playerPos[0] = 0;
            playerPos[1] = 0;
            playerPos[2] = 0;
            playerPos[3] = 0;
            *player1Randstr = "";
            *player2Randstr = "";
            playerTurn = 0;
            *randStr = "";
            battleBegin = false;
            battleDone = false;
            playerRoll = false;
        }
        
        //Cycle player turn from player 1 to player 4;
        if(playerTurn > playerNum-1){
            playerTurn = 0;
        }
        
        // Draw
        BeginDrawing();
            
            //Clear all background from starting to white.
            ClearBackground(RAYWHITE);
            
            //Check if game is started or not.
            if(gameStart == true){
                
                //Draw background.
                DrawTexture(backGround, 0, 0, WHITE);
                
                //Check if battle is need to begin.
                if(battleBegin == true){
                    //Draw Battle button
                    DrawTextureRec(battleBtn, battleBtnRec, (Vector2){battleBtnBound.x, battleBtnBound.y}, WHITE);
                    //Check for button press and random number for fighting.
                    if(IsClicked(mouseOn3) == 1){
                        battleBtnRec.y = 0;
                        if(clickBattle == 0){
                            randNumBattle = GetRandomValue(1, 6);
                            player1Randnum = randNumBattle;
                            sprintf(player1Randstr, "%d", randNumBattle);
                            randNumBattle = GetRandomValue(1, 6);
                            player2Randnum = randNumBattle;
                            sprintf(player2Randstr, "%d", randNumBattle);
                            clickBattle = 1;
                        }
                    }else if(IsClicked(mouseOn3) == 2) battleBtnRec.y = rollFrameHeight;
                    //If battle didn't start place string for "?".
                    if(clickBattle == 0){
                        *player1Randstr = "?";
                        *player2Randstr = "?";
                    }
                    //Draw random number of each player in battle.
                    DrawText(player1Randstr, 100, 20, 50, BLACK);
                    DrawText(player2Randstr, 200, 20, 50, BLACK);
                    //Comparing random number from each player and battle result.
                    if(clickBattle == 1){
                            //Re-draw button to first frame prevent second frame of getting delay.
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
                            //Make delayable after progress this frame.
                            delayWin = true;
                    }
                    
                //NO Battle need to begin.
                }else{
                    //Draw dice roll button for player.
                    DrawTextureRec(rollBtn, rollBtnRec, (Vector2){rollBtnBound.x, rollBtnBound.y}, WHITE);
                    //Random number and check for button press when rollBtn is pressed.
                    if(IsClicked(mouseOn2) == 1){
                        rollBtnRec.y = 0;
                        randNum = GetRandomValue(1, 6);
                        playerPos[playerTurn] = playerPos[playerTurn] + randNum;
                        sprintf(randStr, "%d", randNum);
                        playerRoll = true;
                    }else if(IsClicked(mouseOn2) == 2) rollBtnRec.y = rollFrameHeight;
                }
                //Draw random number that roll from rollBtn.
                DrawText(randStr, 1130, 500, 50, BLACK);
                //Check if player exceed board limit, player will revert back for each number exceed.
                if(playerPos[playerTurn] > 39) playerPos[playerTurn] = 39 - (playerPos[playerTurn] % 39);
                
                //Draw player character
                for(int i=0; i<playerNum; i++){
                    DrawRectanglePro(Char1, (Vector2){boardPosX[playerPos[i]], boardPosY[playerPos[i]]}, 0, playerColor[i]);
                }
                
                //Buffer player position to string and Draw it.
                for(int i=0; i<playerNum; i++){
                sprintf(playerPosStr[i], "%d", playerPos[i]);
                DrawText(playerPosStr[i], 1030, 200+(i*100), 40, playerColor[i]);
                }
                
                //Check IF there any battle need to begin in game.
                for(int i=0; i<playerNum; i++){
                    if(playerPos[playerTurn] == playerPos[i] && i != playerTurn && playerPos[playerTurn] != 0){
                        battleBegin = true;
                        samePos = i;
                        playerRoll = false;
                        battleDone = false;
                    }
                }
                
            //Game didn't start yet.
            }else{
                
                //Draw start menu background.
                DrawTexture(menuBg, 0, 0, WHITE);
                //Draw startBtn.
                DrawTextureRec(startBtn, startBtnRec, (Vector2){startBtnBound.x, startBtnBound.y}, WHITE);
                for(int i=0; i<3; i++){
                    DrawRectangleRec(playerSelectRec[i], BLACK);
                    if(IsClicked(mouseOnPlayerSelect[i]) == 1){
                        playerNum = i+2;
                    }else if(IsClicked(mouseOnPlayerSelect[i]) == 2) DrawRectangleRec(playerSelectRec[i], WHITE);
                }
                //Check if start button is pressed or not.
                if(IsClicked(mouseOn1) == 1) gameStart = true;
                else if(IsClicked(mouseOn1) == 2) DrawTextureRec(startBtn, startBtnRec, (Vector2){startBtnBound.x, startBtnBound.y}, BLACK);
                
            }
        //END Drawing progress.    
        EndDrawing();
        
        //Check if need to delay.
        if(delayWin) delay(1);
        delayWin = false;
        
        //Check for roll and battle state.
        if(playerRoll == true || battleDone == true){
            playerTurn += 1;
            playerRoll = false;
            battleDone = false;
        }
    }
    
    
    //Unload Texture, Image, etc out of memory.
    UnloadImage(btnImg);
    UnloadTexture(rollBtn);
    UnloadTexture(menuBg);
    UnloadTexture(startBtn);
    UnloadTexture(backGround);

    CloseWindow();

    return 0;
}
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
#include <string.h>
#include <ctype.h>

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
    
    //Init audio
    InitAudioDevice();
    
    //Music variable.
    Music music = LoadMusicStream("src/sound/bgm.ogg");
    
    //Sound variable.
    Sound fxButton = LoadSound("src/sound/click.mp3");
    Sound fxBattle = LoadSound("src/sound/battle.mp3");
    Sound fxClaim = LoadSound("src/sound/claim.mp3");
    
    
    
    
    
    //Image variable.
    Image character[4];
    
    //Texture variable.
    Texture2D selectBtn[3];
    Texture2D characterTexture[4];
    Texture2D menuBtn = LoadTexture("src/img/back_to_menu.png");
    Texture2D rollBtn = LoadTexture("src/img/roll.png");
    Texture2D battleBtn = LoadTexture("src/img/battle.png");
    Texture2D menuBg = LoadTexture("src/img/menu.png");
    Texture2D backGround = LoadTexture("src/img/bg.png");
    Texture2D endBg = LoadTexture("src/img/end.png");
    Texture2D startBtn = LoadTexture("src/img/start.png");
    
    
    //Struct?
    struct Player{
        int playerPos;
        int playerHP;
        bool enemyWin;
        bool itemClaim;
        bool healClaim;
        bool shieldOn;
        bool bootsOn;
        Color playerColor;
    }playerInfo[4];
    
    //board slot position.
    int boardPosX[40] = {-250, -340, -430, -520, -610, -700, -790, -880, -880, -880, -790, -700, -610, -520, -430, -340, -250, -160, -70, -70, -70, -160, -250, -340, -430, -520, -610, -700, -790, -880, -880, -880, -790, -700, -610, -520, -430, -340, -250, -160};
    int boardPosY[40] = {-630, -630, -630, -630, -630, -630, -630, -630, -555, -485, -485, -485, -485, -485, -485, -485, -485, -485, -485, -410, -335, -335, -335, -335, -335, -335, -335, -335, -335, -335, -260, -185, -185, -185, -185, -185, -185, -185, -185, -185};
    
    //Frame height of button.
    int rollFrameHeight = rollBtn.height / 2;
   
    //Rectangle Rec src.
    Rectangle endRec = {0, 0, screenWidth, screenHeight};
    Rectangle selectBtnRec[3];
    Rectangle menuBtnRec = {0, 0, menuBtn.width, rollFrameHeight};
    Rectangle startBtnRec = {0, 0, startBtn.width, rollFrameHeight};
    Rectangle rollBtnRec = {0, 0, rollBtn.width, rollFrameHeight};
    Rectangle battleBtnRec = {0, 0, battleBtn.width, rollFrameHeight};
    Rectangle Char1 = {0, 0, 50, 50};
    
    //Rectangle bound src.
    Rectangle startBtnBound = {screenWidth / 2 - startBtn.width / 2, screenHeight / 4, startBtn.width, startBtn.height};
    Rectangle menuBtnBound = {screenWidth / 2 - startBtn.width / 2, screenHeight / 4, startBtn.width, startBtn.height};
    Rectangle rollBtnBound = {1030, 570, rollBtn.width, rollFrameHeight};
    Rectangle battleBtnBound = {1025, 25, battleBtn.width, rollFrameHeight};
    Rectangle selectBtnBound[3];
    
    //Game state and true/false variable.
    bool gameStart=false, gameEnd=false, battleBegin=false, playerRoll=false, battleDone=false, delayable=false, trap=false, enemyFight=false, itemEvent=false, tied=false, wait=false, healEvent=false;
    bool mouseOn_startBtn, mouseOn_rollBtn, mouseOn_battleBtn, mouseOn_menuBtn, mouseOn_playerSelect[3];
    
    //Integer variable.
    int btnState = 0, battleMsgShow=0;
    int randNum, randNumBattle, randPlayer;
    int playerNum=2;
    int playerTurn=0;
    int samePos=0, samePosItem=-1, samePosHeal=-1, player1Randnum, player2Randnum, itemRand=0, clickBattle=0, jackPot=100, bootsNum=0, win=-1;
    int enemyPos[4] = {5, 15, 24, 33}, itemPos[3] = {7, 20, 30}, healPos[3]={18, 27, 34};
    
    //Character/String variable.
    char randStr[3] = "", player1Randstr[3] = "", player2Randstr[3] = "", playerPosStr[4][3], samePosStr[3], playerTurnStr[3], battleMsg[50], playerHPStr[4][3], rollNumber[30]="", player1[10]="", player2[10]="", winStr[20]="", selectStr[60]="", playerNumStr[20]="";
    
    SetTargetFPS(60);
    PlayMusicStream(music);
    SetMusicVolume(music, 0.4);
    SetSoundVolume(fxButton, 0.75);
    SetSoundVolume(fxBattle, 0.75);
    SetSoundVolume(fxClaim, 0.75);
    
    //Init.
    for(int i=0; i<4; i++){
        playerInfo[i].playerPos = 0;
        playerInfo[i].playerHP = 2;
        playerInfo[i].enemyWin = false;
        playerInfo[i].itemClaim = false;
        playerInfo[i].shieldOn = false;
        playerInfo[i].bootsOn = false;
        playerInfo[i].healClaim = false;
        sprintf(selectStr, "src/img/no%d.png", i+1);
        character[i] = LoadImage(selectStr);
        ImageResize(&character[i], 50, 50);
        characterTexture[i] = LoadTextureFromImage(character[i]);
        UnloadImage(character[i]);
        selectStr[0] = '\0';
    }
    for(int i=0; i<3; i++){
        sprintf(selectStr, "src/img/%dplayer.png", i+2);
        selectBtn[i] = LoadTexture(selectStr);
        selectBtnRec[i] = (Rectangle){0, 0, selectBtn[0].width, selectBtn[0].height / 2};
        selectBtnBound[i] = (Rectangle){850+(i*150), 10, selectBtn[0].width, selectBtn[0].height / 2};
        selectStr[0] = '\0';
    }
    
    playerInfo[0].playerColor = (Color){ 0, 0, 0, 255 };
    playerInfo[1].playerColor = (Color){ 230, 41, 55, 255 };
    playerInfo[2].playerColor = (Color){ 0, 228, 48, 255 };
    playerInfo[3].playerColor = (Color){ 0, 121, 241, 255 };
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(music);
        
        //Get mouse position to mousePos.
        Vector2 mousePos = GetMousePosition();
        //Check collision between mousePos and button/rectangle, return bool.
        mouseOn_startBtn = IsMouseOver(mousePos, startBtnBound);
        mouseOn_rollBtn = IsMouseOver(mousePos, rollBtnBound);
        mouseOn_battleBtn = IsMouseOver(mousePos, battleBtnBound);
        mouseOn_menuBtn = IsMouseOver(mousePos, menuBtnBound);
        for(int i=0; i<3; i++){
            mouseOn_playerSelect[i] = IsMouseOver(mousePos, selectBtnBound[i]);
        }
        
        //Check for "F11" is press and toggle fullscreen mode.
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            SetWindowPosition(50, 50);
        }
        if(IsKeyPressed(KEY_P)){
            gameStart = false;
            gameEnd = false;
            for(int i=0; i<4; i++){
                playerInfo[i].playerPos = 0;
                playerInfo[i].playerHP = 2;
                playerInfo[i].enemyWin = false;
                playerInfo[i].itemClaim = false;
                playerInfo[i].shieldOn = false;
                playerInfo[i].bootsOn = false;
                playerInfo[i].healClaim = false;
            }
            player1Randstr[0] = '\0';
            player2Randstr[0] = '\0';
            playerTurn = 0;
            randStr[0] = '\0';
            battleBegin = false;
            itemEvent = false;
            healEvent = false;
            battleDone = false;
            playerRoll = false;
            win = -1; 
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
                
                //HealClaiming Event
                if(healEvent && !playerInfo[samePosHeal].healClaim){
                    PlaySound(fxClaim);
                    jackPot = GetRandomValue(1, 100);
                    if(jackPot == 1){
                        playerInfo[samePosHeal].playerHP += 3;
                        sprintf(player1, "Jackpot!! P%d got heal by 3", samePosHeal);
                    }else{
                        playerInfo[samePosHeal].playerHP += 1;
                        sprintf(player1, "P%d got heal by 1", samePosHeal);
                    }
                    DrawText(player1, 300, 45, 40, BLACK);
                    delayable = true;
                    wait = true;
                    healEvent = false;
                    playerInfo[samePosHeal].healClaim = true;
                }
                
                //ItemClaiming Event
                if(itemEvent && !playerInfo[samePosItem].itemClaim){
                    PlaySound(fxClaim);
                    playerRoll = true;
                    sprintf(player1, "P%d obtain item ", samePosItem);
                    itemRand = GetRandomValue(1, 5);
                    DrawText(player1, 300, 45, 40, BLACK);
                    if(itemRand == 1) {
                        playerInfo[samePosItem].shieldOn = true;
                        DrawText("*Shield*!", 600, 45, 40, YELLOW);
                    }
                    else if(itemRand == 2){
                        playerInfo[samePosItem].bootsOn = true;
                        DrawText("*Boots*!", 600, 45, 40, BLUE);
                    }else if(itemRand == 3){
                        randPlayer = GetRandomValue(0, playerNum);
                        randNum = GetRandomValue(1, 3);
                        playerInfo[randPlayer].playerPos -= randNum;
                        DrawText("*Curse* and someone got cursed!", 600, 45, 35, RED);
                    }else if(itemRand == 4){
                        randNum = GetRandomValue(0, playerNum);
                        playerTurn = randNum;
                        DrawText("*CHAOS*!", 600, 45, 40, PURPLE);
                        playerRoll = false;
                    }else if(itemRand == 5){
                        samePos = GetRandomValue(0, playerNum-1);
                        while(samePos == samePosItem) samePos = GetRandomValue(0, playerNum-1);
                        PlaySound(fxBattle);
                        battleBegin = true;
                        playerRoll = false;
                        battleDone = false;
                        DrawText("*Arena!* and challenged someone.", 600, 45, 35, WHITE);
                    }
                    delayable = true;
                    wait = true;
                    itemEvent = false;
                    playerInfo[samePosItem].itemClaim = true;
                }
                
                //Check if battle is need to begin.
                if(battleBegin == true){
                    sprintf(player1, "P%d: ", samePos+1);
                    sprintf(player2, "P%d: ", playerTurn+1);
                    if(battleMsgShow == 1 && !tied && !wait){
                        PlaySound(fxBattle);
                        DrawText(battleMsg, 300, 45, 40, BLACK);
                        battleMsgShow = 2;
                        delayable = true;
                    }else if(tied){
                        DrawText("Tie!", 300, 45, 40, BLACK);
                        tied = false;
                        delayable = true;
                    }else if(wait);
                    else{
                        //Draw Battle button
                        DrawTextureRec(battleBtn, battleBtnRec, (Vector2){battleBtnBound.x, battleBtnBound.y}, WHITE);
                    }
                    
                    
                    //Check for button press and random number for fighting.
                    if(IsClicked(mouseOn_battleBtn) == 1){
                        PlaySound(fxButton);
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
                    }else if(IsClicked(mouseOn_battleBtn) == 2) battleBtnRec.y = rollFrameHeight;
                    //If battle didn't start place string for "?".
                    if(clickBattle == 0){
                        player1Randstr[0] = '?';
                        player1Randstr[1] = '\0';
                        player2Randstr[0] = '?';
                        player2Randstr[1] = '\0';
                    }
                    //Draw random number of each player in battle.
                    DrawText(player1, 30, 40, 45, playerInfo[playerTurn].playerColor);
                    DrawText(player1Randstr, 100, 40, 45, BLACK);
                    if(enemyFight) DrawText("AI: ", 160, 40, 45, WHITE);
                    else DrawText(player2, 160, 40, 45, playerInfo[samePos].playerColor);
                    DrawText(player2Randstr, 250, 40, 45, BLACK); 
                    //Comparing random number from each player and battle result.
                    if(clickBattle == 1){
                        //Re-draw button to first frame prevent second frame of getting delay.
                        battleBtnRec.y = 0;
                        DrawTextureRec(battleBtn, battleBtnRec, (Vector2){battleBtnBound.x, battleBtnBound.y}, WHITE);
                        if(player1Randnum > player2Randnum){
                            if(enemyFight){
                                playerInfo[samePos].enemyWin = true;
                                playerInfo[samePos].playerPos += 1;
                                DrawText("Player win!", 300, 45, 40, playerInfo[playerTurn].playerColor);
                                enemyFight = false;
                            }else{
                                DrawText("P1 win!", 300, 45, 40, playerInfo[samePos].playerColor);
                                playerInfo[playerTurn].playerHP -= 1;
                                playerInfo[playerTurn].playerPos -= 1;
                                playerInfo[playerTurn].itemClaim = false;
                                playerInfo[playerTurn].enemyWin = false;
                            }
                            battleBegin = false;
                            battleDone = true;
                            clickBattle = 0;
                        }else if(player2Randnum > player1Randnum){
                            if(enemyFight){
                                playerInfo[samePos].enemyWin = true;
                                DrawText("Enemy win!", 300, 45, 40, WHITE);
                                enemyFight = false;
                            }else DrawText("P2 Win!", 300, 45, 40, playerInfo[playerTurn].playerColor);
                            playerInfo[samePos].playerHP -=1;
                            playerInfo[samePos].playerPos -= 1;
                            playerInfo[samePos].itemClaim = false;
                            playerInfo[samePos].enemyWin = false;
                            clickBattle = 0;
                            battleBegin = false;
                            battleDone = true;
                        }else{
                            tied = true;
                            clickBattle = 0;
                            player1Randnum = 0;
                            player2Randnum = 0;
                            *player1Randstr = "?";
                            *player2Randstr = "?";
                        }
                        //Make delayable after progress this frame.
                        battleMsgShow = 0;
                        delayable = true;
                    }
                    
                //NO Battle need to begin.
                }else{
                    //Draw dice roll button for player.
                    DrawTextureRec(rollBtn, rollBtnRec, (Vector2){rollBtnBound.x, rollBtnBound.y}, WHITE);
                    //Random number and check for button press when rollBtn is pressed.
                    if(IsClicked(mouseOn_rollBtn) == 1){
                        PlaySound(fxButton);
                        playerInfo[playerTurn].itemClaim = false;
                        playerInfo[playerTurn].healClaim = false;
                        rollBtnRec.y = 0;
                        randNum = GetRandomValue(1, 6);
                        playerInfo[playerTurn].playerPos += randNum;
                        if(playerInfo[playerTurn].bootsOn){
                            bootsNum = GetRandomValue(1, 3);
                            playerInfo[playerTurn].playerPos += bootsNum;
                            playerInfo[playerTurn].bootsOn = false;
                        }
                        sprintf(randStr, "%d", randNum);
                        playerRoll = true;
                        playerInfo[playerTurn].enemyWin = false;
                        //Draw number rolled
                        sprintf(playerTurnStr, "%d", playerTurn+1);
                        strcat(rollNumber, "Player ");
                        strcat(rollNumber, playerTurnStr);
                        strcat(rollNumber, " rolled ");
                        strcat(rollNumber, randStr);
                        DrawText(rollNumber, 1040, 660, 20, BLACK);
                        strcpy(rollNumber, "");
                        delayable = true;
                    }else if(IsClicked(mouseOn_rollBtn) == 2) rollBtnRec.y = rollFrameHeight;
                }
                
                
                //GameEnd Condition
                if(playerInfo[playerTurn].playerPos == 39){
                    gameEnd = true;
                    gameStart = false;
                    win = playerTurn;
                }
                //Check if player exceed board limit, player will revert back for each number exceed.
                if(playerInfo[playerTurn].playerPos > 39) playerInfo[playerTurn].playerPos = 39 - (playerInfo[playerTurn].playerPos % 39);
                //Check for enemy trap.
                if(playerInfo[playerTurn].playerPos == 11 || playerInfo[playerTurn].playerPos == 28 || playerInfo[playerTurn].playerPos == 35 || playerInfo[playerTurn].playerPos == 37){
                    trap = true;
                    DrawText("Get dunked on", 500, 30, 50, BLACK);
                }
                
                //Draw info topic
                DrawText("Pos", 1030, 150, 20, BLACK);
                DrawText("HP", 1080, 150, 20, BLACK);
                DrawText("Shield", 1120, 150, 20, BLACK);
                DrawText("Boots", 1200, 150, 20, BLACK);
                
                //Loop checking.
                for(int i=0; i<playerNum; i++){

                    //Check if player pos is negative and change back to 0
                    if(playerInfo[i].playerPos < 0) playerInfo[i].playerPos = 0;
                    
                    //Draw player character
                    //DrawRectanglePro(Char1, (Vector2){boardPosX[playerInfo[i].playerPos], boardPosY[playerInfo[i].playerPos]}, 0, playerInfo[i].playerColor);
                    DrawTextureV(characterTexture[i], (Vector2){-boardPosX[playerInfo[i].playerPos], -boardPosY[playerInfo[i].playerPos]}, WHITE);
                
                    //Buffer player position to string and Draw it.
                    sprintf(playerPosStr[i], "%d", playerInfo[i].playerPos);
                    sprintf(playerHPStr[i], "%d", playerInfo[i].playerHP);
                    DrawText(playerPosStr[i], 1030, 200+(i*100), 40, playerInfo[i].playerColor);
                    DrawText(playerHPStr[i], 1080, 200+(i*100), 40, GREEN);
                    
                    //Draw playerTurn outline
                    if(i == playerTurn) DrawRectangleLines(1025, 185+(i*100), 250, 65, GREEN);
                    
                    //Draw owned item
                    if(playerInfo[i].shieldOn) DrawText("ON", 1120, 210+(i*100), 25, BLACK);
                    else DrawText("OFF", 1120, 210+(i*100), 30, BLACK);
                    if(playerInfo[i].bootsOn) DrawText("ON", 1200, 210+(i*100), 25, BLACK);
                    else DrawText("OFF", 1200, 210+(i*100), 30, BLACK);
                
                    //HP Checking
                    if(playerInfo[i].playerHP == 0 && !trap){
                        playerInfo[i].playerHP = 2;
                        playerInfo[i].playerPos = (playerInfo[i].playerPos - 2) * (playerInfo[i].playerPos - 2 >= 0);
                    }
                    
                    //Check IF there's any battle need to begin between player and AI.
                    for(int j=0; j<4; j++){
                        if(playerInfo[i].playerPos == enemyPos[j] && !playerInfo[i].enemyWin){
                            samePos = i;
                            if(playerInfo[samePos].shieldOn){
                                playerInfo[samePos].playerPos += 1;
                                playerInfo[samePos].shieldOn = false;
                                continue;
                            }
                            battleBegin = true;
                            enemyFight = true;
                            playerRoll = false;
                            battleDone = false;
                            if(battleMsgShow == 0) battleMsgShow=1;
                        }
                    }
                    
                    //Check IF there's any player can claim item.
                    for(int j=0; j<3; j++){
                        if(playerInfo[i].playerPos == itemPos[j] && !playerInfo[i].itemClaim){
                            samePosItem = i;
                            itemEvent = true;
                            playerRoll = false;
                        }
                    }
                    
                    //Check IF there's any player step on heal tile.
                    for(int j=0; j<3; j++){
                        if(playerInfo[i].playerPos == healPos[j] && !playerInfo[i].healClaim){
                            samePosHeal = i;
                            healEvent = true;
                        }
                    }
                        
                    //Check IF there's any battle need to begin in game.
                    if(playerInfo[playerTurn].playerPos == playerInfo[i].playerPos && i != playerTurn && playerInfo[playerTurn].playerPos != 0 && !enemyFight){
                        samePos = i;
                        if(playerInfo[playerTurn].shieldOn){
                            playerInfo[playerTurn].playerPos += 1;
                            playerInfo[playerTurn].shieldOn = false;
                            delayable = true;
                            DrawText("*Sheild activated*", 500, 30, 50, YELLOW);
                            continue;
                        }else if(playerInfo[samePos].shieldOn){
                            playerInfo[samePos].playerPos += 1;
                            playerInfo[samePos].shieldOn = false;
                            delayable = true;
                            DrawText("*Sheild activated*", 500, 30, 50, YELLOW);
                            continue;
                        }
                        battleBegin = true;
                        playerRoll = false;
                        battleDone = false;
                        if(battleMsgShow == 0) battleMsgShow=1;
                    }
                    
                    //Making battleMsg.
                    sprintf(playerTurnStr, "%d", playerTurn+1);
                    sprintf(samePosStr, "%d", samePos+1);
                    strcpy(battleMsg, "Battle begin between ");
                    if(enemyFight){
                        strcat(battleMsg, "AI");
                    }else{
                        strcat(battleMsg, "Player ");
                        strcat(battleMsg, samePosStr);
                    }
                    strcat(battleMsg, " and Player ");
                    strcat(battleMsg, playerTurnStr);
                        
                }

                
            //Game didn't start yet.
            }else if(!gameStart && !gameEnd){
                
                //Draw start menu background.
                DrawTexture(menuBg, 0, 0, WHITE);
                //Draw playerNum
                sprintf(playerNumStr, "Play with %d player(s).", playerNum);
                DrawText(playerNumStr, 850, 75, 30, BLACK);
                //Draw startBtn.
                DrawTextureRec(startBtn, startBtnRec, (Vector2){startBtnBound.x, startBtnBound.y}, WHITE);
                for(int i=0; i<3; i++){
                   DrawTextureRec(selectBtn[i], selectBtnRec[i], (Vector2){selectBtnBound[i].x, selectBtnBound[i].y}, WHITE);
                   if(IsClicked(mouseOn_playerSelect[i]) == 1) {
                       PlaySound(fxButton);
                       playerNum = i+2;
                   }
                   else if(IsClicked(mouseOn_playerSelect[i]) == 2) selectBtnRec[i].y = selectBtn[i].height / 2;
                   else selectBtnRec[i].y = 0;
                }
                //Check if start button is pressed or not.
                if(IsClicked(mouseOn_startBtn) == 1){
                    PlaySound(fxButton);
                    gameStart = true;
                    startBtnRec.y = 0;
                }
                else if(IsClicked(mouseOn_startBtn) == 2) startBtnRec.y = rollFrameHeight;
                
            }else if(gameEnd){
                ClearBackground(WHITE);
                //BACKGROUND
                DrawTexture(endBg, 0, 0, WHITE);
                //TEXT
                sprintf(winStr, "P%d ", win+1);
                DrawText(winStr, screenWidth/2-100, screenHeight/2-100, 50, playerInfo[win].playerColor);
                DrawText("  Win!", screenWidth/2-50, screenHeight/2-100, 50, BLACK);
                //BUTTON
                DrawTextureRec(menuBtn, menuBtnRec, (Vector2){menuBtnBound.x, menuBtnBound.y}, WHITE);
                if(IsClicked(mouseOn_menuBtn) == 1){
                    PlaySound(fxButton);
                    menuBtnRec.y = 0;
                    gameStart = false;
                    gameEnd = false;
                    for(int i=0; i<4; i++){
                        playerInfo[i].playerPos = 0;
                        playerInfo[i].playerHP = 2;
                        playerInfo[i].enemyWin = false;
                        playerInfo[i].itemClaim = false;
                        playerInfo[i].shieldOn = false;
                        playerInfo[i].bootsOn = false;
                        playerInfo[i].healClaim = false;
                    }
                    player1Randstr[0] = '\0';
                    player2Randstr[0] = '\0';
                    playerTurn = 0;
                    randStr[0] = '\0';
                    battleBegin = false;
                    itemEvent = false;
                    healEvent = false;
                    battleDone = false;
                    playerRoll = false;
                    win = -1;
                }
                else if(IsClicked(mouseOn_menuBtn) == 2) menuBtnRec.y = rollFrameHeight;
            }

 
            
        //END Drawing progress.    
        EndDrawing();
        
        //Check if any player step on a trap(ladder).
        if(trap == true){
            if(playerInfo[playerTurn].playerPos == 11) playerInfo[playerTurn].playerPos = 4;
            else if(playerInfo[playerTurn].playerPos == 28) playerInfo[playerTurn].playerPos = 13;
            else if(playerInfo[playerTurn].playerPos == 35) playerInfo[playerTurn].playerPos = 26;
            else if(playerInfo[playerTurn].playerPos == 37) playerInfo[playerTurn].playerPos = 16;
            trap = false;
        }
        
        //Check again if any ppl trap down and place at same pos.
        for(int i=0; i<playerNum; i++){
            if(playerInfo[playerTurn].playerPos == playerInfo[i].playerPos && i != playerTurn && playerInfo[playerTurn].playerPos != 0){
                battleBegin = true;
                samePos = i;
                playerRoll = false;
                battleDone = false;
            }
        }
        
        //Check if need to delay.
        if(delayable) delay(1);
        delayable = false;
        wait = false;
        
        //Check for roll and battle state.
        if(playerRoll == true || battleDone == true){
            playerTurn += 1;
            playerRoll = false;
            battleDone = false;
        }
    }
    
    
    //Unload Texture, Image, etc out of memory.
    for(int i=0; i<3; i++){
        UnloadTexture(selectBtn[i]);
        
    }
    for(int i=0; i<4; i++){
        UnloadTexture(characterTexture[i]);
    }
    
    UnloadSound(fxButton);
    UnloadTexture(endBg);
    UnloadTexture(rollBtn);
    UnloadTexture(menuBg);
    UnloadTexture(menuBtn);
    UnloadTexture(startBtn);
    UnloadTexture(backGround);
    UnloadTexture(battleBtn);
    
    CloseAudioDevice();

    CloseWindow();

    return 0;
}
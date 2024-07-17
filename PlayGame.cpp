#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>
#include <stdlib.h> 
#include <string>
//#include <SDL.h>
//#include <SDL_image.h>
#include "Player.h"
#include "Brick.h"
#include "Enemy.h"
#include "PowerupBlock.h"
#include "Mushroom.h"
#include "Water.h"
#include "Acid.h"
#include "Wood.h"
#include "SourceContainer.h"
#include "Door.h"
#include "DestinationAcid.h"
#include "DestinationWater.h"
#include<iostream>
//#include"SDL_ttf.h"
#include "Button.h"
#include"SDL_mixer.h"
#include <vector>

using namespace std;

const int nScreenWidth = 900;
const int nScreenHeight = 700;

//Starting SDL, creating window, renderer etc
bool innit();

//Initializing Level 1
void InnitLevel1(vector<GameObject*>* LevelItems, vector<GameObject*>* Particles);

void InnitLevel2(vector<GameObject*>* LevelItems, vector<GameObject*>* Particles);

void EndScreen(bool LivesFinished, bool ObjectiveSuccessfull);

//Deallocation of memory and closing SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

TTF_Font* gFont = nullptr;


bool innit() {

    bool success = true;

    //Create window
    gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, nScreenWidth, nScreenHeight, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create renderer for window
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (gRenderer == nullptr)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 135, 136, 156, 0xFF);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }

            //Initialize SDL_ttf
            if (TTF_Init() == -1)
            {
                printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                success = false;
            }

            gFont = TTF_OpenFont("Antonio-Bold.ttf", 25);
            if (gFont == NULL)
            {
                printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
                success = false;
            }

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            }

        }

    }

    return success;

}

void close()
{
    //Destroy renderer and window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    TTF_CloseFont(gFont);
    gFont = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main() {

    if (!innit()) {

        printf("Failed to initialize!\n");

    }
    else {

        bool Selection = false;
        bool PlayGame = false;
        SDL_Event MenuEvent;

        Button* Button1 = new Button("Play Game", gRenderer, gFont);
        Button1->SetCoordinates((nScreenWidth - Button1->GetRectangle()->w) / 2, (nScreenHeight - (3 * Button1->GetRectangle()->h)) / 2);

        Button* Button2 = new Button("Exit Game", gRenderer, gFont);
        Button2->SetCoordinates((nScreenWidth - Button2->GetRectangle()->w) / 2, Button1->GetRectangle()->y + (2 * Button1->GetRectangle()->h));

        while (!Selection) {

            while (SDL_PollEvent(&MenuEvent) != 0)
            {
                //User requests quit
                if (MenuEvent.type == SDL_QUIT)
                {
                    PlayGame = false;
                    Selection = true;
                }
                else if (MenuEvent.type == SDL_MOUSEBUTTONUP)//Inc Dec rows or columns based on mouse presses
                {
                    //Get mouse position
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    if ((x >= Button1->GetRectangle()->x && x <= Button1->GetRectangle()->x + Button1->GetRectangle()->w) && (y >= Button1->GetRectangle()->y && y <= Button1->GetRectangle()->y + Button1->GetRectangle()->h)) {

                        PlayGame = true;
                        Selection = true;
                        break;


                    }
                    else if ((x >= Button2->GetRectangle()->x && x <= Button2->GetRectangle()->x + Button2->GetRectangle()->w) && (y >= Button2->GetRectangle()->y && y <= Button2->GetRectangle()->y + Button2->GetRectangle()->h)) {

                        PlayGame = false;
                        Selection = true;
                        break;


                    }

                }

            }

            SDL_RenderClear(gRenderer);

            Button1->Render(gRenderer);

            Button2->Render(gRenderer);

            SDL_RenderPresent(gRenderer);



        }

        delete Button1;
        Button1 = nullptr;

        delete Button2;
        Button2 = nullptr;


        if(PlayGame){

            bool GameRunning = true;
            long int nSpeedCount = 0;
            //Event handler
            SDL_Event e;
            vector<GameObject*> LevelItems;
            vector<GameObject*> Particles;
            bool Collission = false;

            SDL_Texture* BackgroundTexture = IMG_LoadTexture(gRenderer, "Background.png");
            SDL_Rect* BackgroundRect = new SDL_Rect();
            BackgroundRect->w = nScreenWidth;
            BackgroundRect->h = nScreenHeight;
            BackgroundRect->x = 0;
            BackgroundRect->y = 0;

            SDL_Texture* WaterTexture = IMG_LoadTexture(gRenderer, "Water.png");
            SDL_Rect* WaterRect = new SDL_Rect();
            WaterRect->w = 40;
            WaterRect->h = 20;
            WaterRect->x = 22;
            WaterRect->y = 52;

            SDL_Texture* AcidTexture = IMG_LoadTexture(gRenderer, "Acid.png");
            SDL_Rect* AcidRect = new SDL_Rect();
            AcidRect->w = 40;
            AcidRect->h = 20;
            AcidRect->x = 838;
            AcidRect->y = 52;

            SDL_Texture* HeartTexture = IMG_LoadTexture(gRenderer, "heart.png");
            SDL_Rect* HeartRect = new SDL_Rect();
            HeartRect->w = 16;
            HeartRect->h = 16;
            HeartRect->y = 10;

            Player* Player1 = Player::GetInstance(0, 668, gRenderer, "Player2.png");

            InnitLevel1(&LevelItems, &Particles);

            int frameStart = 0;
            int frameTime = 0;

            int frameDelay = 40;

            int DamageBoostCountDown = 0;

            bool MushroomSpawn = false;
            bool MushroomColission = false;

            bool Seepage = false;
            bool SeepageFinished = false;
            int SeepCounter = 0;
            int counter = 0;

            int DrainCounter = 0;
            int TranslateCounter = 2;
            bool ReachedMax = false;

            bool WaterAcquired = false;
            bool AcidAcquired = false;

            bool DestinationWater = false;
            bool DestinationAcid = false;

            int WaterStart = 0;
            int AcidStart = 0;

            string Level = "level1";
            bool PathShown = false;

            bool ObjectiveAchieved = false;
            bool LivesFinished = false;

            Mix_Chunk* JumpSound = Mix_LoadWAV("Jump.wav");
            Mix_Chunk* MushAcq = Mix_LoadWAV("Powerup.wav");
            Mix_Chunk* HurtSound = Mix_LoadWAV("Hurt.wav");
            Mix_Chunk* Pickup = Mix_LoadWAV("Pickup.wav");
            Mix_Chunk* KillSound = Mix_LoadWAV("Stomp.wav");
            Mix_Chunk* Decay = Mix_LoadWAV("Decay.wav");

            while (GameRunning) {

                frameStart = SDL_GetTicks();
                //this_thread::sleep_for(50ms);
                nSpeedCount++;

                if (Player1->GetDamageBoostStatus())
                    DamageBoostCountDown++;

                if (DamageBoostCountDown % 20 == 0) {

                    Player1->SetDamageBoostStatus(false);
                    Player1->SetAlphaValue(255);
                    DamageBoostCountDown = 0;

                }

                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        GameRunning = false;
                    }
                    //User presses a key
                    else if (e.type == SDL_KEYDOWN)
                    {
                        //Select surfaces based on key press
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            break;

                        case SDLK_DOWN:
                            //Player1->Translate(0, 20);
                            break;

                        case SDLK_LEFT:
                            if (Player1->GetJumpingStatus() && !Player1->GetJumpingDirectionStatus()) {
                                Player1->SetVelocity(-20.0, -50.0);
                                Player1->SetJumpingDirectionStatus(true);
                            }
                            
                            else
                                Player1->Translate(-10.0, 0);

                            Player1->SetLeftRight(true);

                            break;

                        case SDLK_RIGHT:
                            if (Player1->GetJumpingStatus() && !Player1->GetJumpingDirectionStatus()) {
                                Player1->SetVelocity(20.0, -50.0);
                                Player1->SetJumpingDirectionStatus(true);
                            } 
                            else
                                Player1->Translate(10.0, 0);

                            Player1->SetLeftRight(false);

                            break;

                        case SDLK_SPACE:
                        {
                            if (Player1->GetJumpingStatus() == false) {
                                Player1->SetJumpingStatus(true);
                                Player1->SetVelocity(0.0, -50.0);
                                Player1->Translate(0.0, 0.0);
                                Mix_PlayChannel(-1, JumpSound, 0);
                            }
                            break;

                        }
                        case SDLK_e:
                        {

                            if (Level == "level1") {

                                for (int i = 0; i < LevelItems.size(); i++) {

                                    if (LevelItems.at(i)->GetGameObjectType() == "SourceContainer" && LevelItems.at(i)->Alive()) {

                                        if (Player1->GetRectangle()->y == LevelItems.at(i)->GetRectangle()->y + 29) {
                                        
                                            if (Player1->GetRectangle()->x - 5 <= LevelItems.at(i)->GetRectangle()->x + 64 && Player1->GetRectangle()->x - 5 > LevelItems.at(i)->GetRectangle()->x) {

                                                WaterAcquired = true;
                                                LevelItems.at(i)->ChangeAliveStatus(false);
                                                SDL_DestroyTexture(WaterTexture);
                                                delete WaterRect;
                                                WaterRect = nullptr;
                                                Mix_PlayChannel(-1, Pickup, 0);

                                            }
                                            else if (Player1->GetRectangle()->x + 32 + 5 >= LevelItems.at(i)->GetRectangle()->x && Player1->GetRectangle()->x + 32 + 5 < LevelItems.at(i)->GetRectangle()->x + 64) {

                                                AcidAcquired = true;
                                                LevelItems.at(i)->ChangeAliveStatus(false);
                                                SDL_DestroyTexture(AcidTexture);
                                                delete AcidRect;
                                                AcidRect = nullptr;
                                                Mix_PlayChannel(-1, Pickup, 0);

                                            }

                                        }

                                    }

                                }


                            }

                            break;

                        }
                        case SDLK_n:
                        {

                            if (Level == "level1") {

                                for (int i = 0; i < LevelItems.size(); i++) {

                                    if (LevelItems.at(i)->GetGameObjectType() == "Door") {

                                        if (SDL_HasIntersection(LevelItems.at(i)->GetRectangle(), Player1->GetRectangle())) {

                                            Player1->SetCoordinates(0, 668);
                                            InnitLevel2(&LevelItems, &Particles);
                                            Level = "level2";
                                            break;

                                        }


                                    }


                                }

                            }
                            else {

                                if (DestinationAcid && DestinationWater) {

                                    for (int i = 0; i < LevelItems.size(); i++) {

                                        if (LevelItems.at(i)->GetGameObjectType() == "Door") {

                                            if (SDL_HasIntersection(LevelItems.at(i)->GetRectangle(), Player1->GetRectangle())) {

                                                Player1->SetCoordinates(0, 668);
                                                Level = "EndScreen";
                                                GameRunning = false;
                                                if (!Seepage)
                                                    ObjectiveAchieved = true;
                                                break;

                                            }


                                        }


                                    }

                                }

                            }

                            break;

                        }
                        case SDLK_w:
                        {

                            if (Level == "level2") {

                                if (!DestinationWater) {

                                    for (int i = 0; i < LevelItems.size(); i++) {

                                        if (LevelItems.at(i)->GetGameObjectType() == "DestinationContainer" && !LevelItems.at(i)->GetFillStatus()) {

                                            if (Player1->GetRectangle()->y == LevelItems.at(i)->GetRectangle()->y + 96) {

                                                if (Player1->GetRectangle()->x + 32 + 5 >= LevelItems.at(i)->GetRectangle()->x && Player1->GetRectangle()->x + 32 + 5 < LevelItems.at(i)->GetRectangle()->x + 128) {

                                                    LevelItems.at(i)->SetFillStatus(true);
                                                    DestinationWater = true;

                                                    if (!DestinationAcid) {

                                                        WaterStart = 320;
                                                        AcidStart = 720;

                                                    }

                                                    Mix_PlayChannel(-1, Pickup, 0);

                                                    for (int j = 0; j < 10; j++) {

                                                        for (int k = 0; k < 40; k++) {

                                                            Particles.emplace_back(new Water(LevelItems.at(i)->GetRectangle()->x + 24 + (k * 2), LevelItems.at(i)->GetRectangle()->y + 54 + (j * 2), gRenderer, "Water.png"));
                                                            //Particles.at(Particles.size() - 1)->SetDestinationStatus(true);

                                                        }

                                                    }


                                                }



                                            }


                                        }


                                    }

                                }
                            }

                            break;

                        }
                        case SDLK_a:
                        {

                            if (Level == "level2") {

                                if (!DestinationAcid) {

                                    for (int i = 0; i < LevelItems.size(); i++) {

                                        if (LevelItems.at(i)->GetGameObjectType() == "DestinationContainer" && !LevelItems.at(i)->GetFillStatus()) {

                                            if (Player1->GetRectangle()->y == LevelItems.at(i)->GetRectangle()->y + 96) {

                                                if (Player1->GetRectangle()->x + 32 + 5 >= LevelItems.at(i)->GetRectangle()->x && Player1->GetRectangle()->x + 32 + 5 < LevelItems.at(i)->GetRectangle()->x + 128) {

                                                    LevelItems.at(i)->SetFillStatus(true);
                                                    DestinationAcid = true;

                                                    if (!DestinationWater) {

                                                        AcidStart = 320;
                                                        WaterStart = 720;

                                                    }

                                                    Mix_PlayChannel(-1, Pickup, 0);

                                                    for (int j = 0; j < 10; j++) {

                                                        for (int k = 0; k < 40; k++) {

                                                            Particles.emplace_back(new Acid(LevelItems.at(i)->GetRectangle()->x + 24 + (k * 2), LevelItems.at(i)->GetRectangle()->y + 54 + (j * 2), gRenderer, "Acid.png"));
                                                            Particles.at(Particles.size() - 1)->SetDestinationStatus(true);

                                                        }

                                                    }


                                                }



                                            }


                                        }


                                    }

                                }
                            }

                            break;

                        }


                        }

                    }


                }

        
                //Collission Detection
                Collission = false;
                for (int i = 0; i < LevelItems.size(); i++) {

                    if (SDL_HasIntersection(LevelItems.at(i)->GetRectangle(), Player1->GetRectangle())) {

                        if (LevelItems.at(i)->GetGameObjectType() == "Platform") {

                            if (SDL_HasIntersection(LevelItems.at(i)->GetTopRect(), Player1->GetRectangle())) {

                                Collission = true;

                                if (!Player1->GetPlatformStatus()) {

                                    cout << "Top" << endl;
                                    Player1->SetJumpingStatus(false);
                                    Player1->SetJumpingDirectionStatus(false);
                                    Player1->SetPlatformStatus(true);
                                    Player1->Translate(0.0, 0.0);
                                    Player1->SetPlatform(LevelItems.at(i));
                                    Player1->SetCoordinates(Player1->GetRectangle()->x, LevelItems.at(i)->GetRectangle()->y - 31);

                                }

                            }
                            else if (SDL_HasIntersection(LevelItems.at(i)->GetLeftRect(), Player1->GetRectangle())) {

                                if (!Player1->GetPlatformStatus()) {

                                    cout << "Right" << endl;
                                    Player1->SetCollissionFlag(true);
                                    if (Player1->GetJumpingStatus())
                                        Player1->SetCollissionX(Player1->GetRectangle()->x);
                                    else
                                        Player1->SetCollissionX(Player1->GetRectangle()->x - 5);

                                }
                                else {

                                    if (Player1->GetPlatform()->GetRectangle()->y != LevelItems.at(i)->GetRectangle()->y) {


                                        cout << "Right" << endl;
                                        Player1->SetCollissionFlag(true);
                                        if (Player1->GetJumpingStatus())
                                            Player1->SetCollissionX(Player1->GetRectangle()->x);
                                        else
                                            Player1->SetCollissionX(Player1->GetRectangle()->x - 5);

                                    }

                                }

                            }
                            else if (SDL_HasIntersection(LevelItems.at(i)->GetRightRect(), Player1->GetRectangle())) {

                                if (!Player1->GetPlatformStatus()) {

                                    cout << "Right" << endl;
                                    Player1->SetCollissionFlag(true);
                                    if (Player1->GetJumpingStatus())
                                        Player1->SetCollissionX(Player1->GetRectangle()->x);
                                    else
                                        Player1->SetCollissionX(Player1->GetRectangle()->x + 5);

                                }
                                else {

                                    if (Player1->GetPlatform()->GetRectangle()->y != LevelItems.at(i)->GetRectangle()->y) {


                                        cout << "Right" << endl;
                                        Player1->SetCollissionFlag(true);
                                        if (Player1->GetJumpingStatus())
                                            Player1->SetCollissionX(Player1->GetRectangle()->x);
                                        else
                                            Player1->SetCollissionX(Player1->GetRectangle()->x + 5);

                                    }

                                }

                            }
                            else if (SDL_HasIntersection(LevelItems.at(i)->GetDownRect(), Player1->GetRectangle())) {

                                cout << "Down" << endl;
                                Player1->SetCollissionFlag(true);
                                Player1->SetCollissionY(Player1->GetRectangle()->y);

                            }

                        }
                        else if (LevelItems.at(i)->GetGameObjectType() == "Enemy" && !Player1->GetDamageBoostStatus() && !LevelItems.at(i)->GetStompedStatus()) {

                            cout << "Detection with Enemy" << endl;

                            if (SDL_HasIntersection(LevelItems.at(i)->GetLeftRect(), Player1->GetRectangle())) {

                                cout << "Left Enemy" << endl;

                                if (Player1->GetHealth() > 1) {

                                    Player1->DecHealth();
                                    Player1->SetDamageBoostStatus(true);
                                    Mix_PlayChannel(-1, HurtSound, 0);

                                }
                                else {

                                    Player1->DecHealth();
                                    GameRunning = false;
                                    LivesFinished = true;

                                }


                            }
                            else if (SDL_HasIntersection(LevelItems.at(i)->GetRightRect(), Player1->GetRectangle())) {

                                cout << "Right Enemy" << endl;

                                if (Player1->GetHealth() > 1) {

                                    Player1->DecHealth();
                                    Player1->SetDamageBoostStatus(true);
                                    Mix_PlayChannel(-1, HurtSound, 0);

                                }
                                else {

                                    Player1->DecHealth();
                                    GameRunning = false;
                                    LivesFinished = true;

                                }

                            }
                            else if (SDL_HasIntersection(LevelItems.at(i)->GetTopRect(), Player1->GetRectangle())) {


                                cout << "Top of Enemy" << endl;
                                LevelItems.at(i)->SetStomped(true);
                                Mix_PlayChannel(-1, KillSound, 0);


                            }

                        }
                        else if (LevelItems.at(i)->GetGameObjectType() == "PowerupBlock") {


                        if (SDL_HasIntersection(LevelItems.at(i)->GetTopRect(), Player1->GetRectangle())) {

                            Collission = true;

                            if (!Player1->GetPlatformStatus()) {

                                cout << "Top" << endl;
                                Player1->SetJumpingStatus(false);
                                Player1->SetJumpingDirectionStatus(false);
                                Player1->SetPlatformStatus(true);
                                Player1->Translate(0.0, 0.0);
                                Player1->SetPlatform(LevelItems.at(i));
                                //Player1->SetCoordinates(Player1->GetRectangle()->x, LevelItems.at(i)->GetRectangle()->y - 31);

                            }

                        }
                        else if (SDL_HasIntersection(LevelItems.at(i)->GetLeftRect(), Player1->GetRectangle())) {

                            if (!Player1->GetPlatformStatus()) {

                                cout << "Right" << endl;
                                Player1->SetCollissionFlag(true);
                                if (Player1->GetJumpingStatus())
                                    Player1->SetCollissionX(Player1->GetRectangle()->x);
                                else
                                    Player1->SetCollissionX(Player1->GetRectangle()->x - 5);

                            }
                            else {

                                if (Player1->GetPlatform()->GetRectangle()->y != LevelItems.at(i)->GetRectangle()->y) {


                                    cout << "Right" << endl;
                                    Player1->SetCollissionFlag(true);
                                    if (Player1->GetJumpingStatus())
                                        Player1->SetCollissionX(Player1->GetRectangle()->x);
                                    else
                                        Player1->SetCollissionX(Player1->GetRectangle()->x - 5);

                                }

                            }

                        }
                        else if (SDL_HasIntersection(LevelItems.at(i)->GetRightRect(), Player1->GetRectangle())) {

                            if (!Player1->GetPlatformStatus()) {

                                cout << "Right" << endl;
                                Player1->SetCollissionFlag(true);
                                if (Player1->GetJumpingStatus())
                                    Player1->SetCollissionX(Player1->GetRectangle()->x);
                                else
                                    Player1->SetCollissionX(Player1->GetRectangle()->x + 5);

                            }
                            else {

                                if (Player1->GetPlatform()->GetRectangle()->y != LevelItems.at(i)->GetRectangle()->y) {


                                    cout << "Right" << endl;
                                    Player1->SetCollissionFlag(true);
                                    if (Player1->GetJumpingStatus())
                                        Player1->SetCollissionX(Player1->GetRectangle()->x);
                                    else
                                        Player1->SetCollissionX(Player1->GetRectangle()->x + 5);

                                }

                            }

                        }
                        else if (SDL_HasIntersection(LevelItems.at(i)->GetDownRect(), Player1->GetRectangle())) {

                            cout << "Down" << endl;
                            Player1->SetCollissionFlag(true);
                            Player1->SetCollissionY(Player1->GetRectangle()->y);

                            if (!LevelItems.at(i)->GetPowerUpStatus()) {

                                LevelItems.emplace_back(new Mushroom(LevelItems.at(i)->GetRectangle()->x, LevelItems.at(i)->GetRectangle()->y, gRenderer, "mushroom.png"));
                                LevelItems.at(LevelItems.size() - 1)->Translate(10.0, -5.0);
                                MushroomSpawn = true;
                                LevelItems.at(i)->SetPowerUpStatus(true);

                            }

                        }

                        }
                        else if (LevelItems.at(i)->GetGameObjectType() == "Powerup" && LevelItems.at(i)->GetMushAppeared()) {

                            LevelItems.at(i)->ChangeAliveStatus(false);
                            MushroomSpawn = false;
                            Player1->IncHealth();
                            Mix_PlayChannel(-1, MushAcq, 0);

                        }
                        else if (LevelItems.at(i)->GetGameObjectType() == "SourceContainer"){

                            if (SDL_HasIntersection(LevelItems.at(i)->GetLeftRect(), Player1->GetRectangle())) {

                                Player1->SetCollissionFlag(true);
                                if (Player1->GetJumpingStatus())
                                    Player1->SetCollissionX(Player1->GetRectangle()->x);
                                else
                                    Player1->SetCollissionX(Player1->GetRectangle()->x - 5);

                            }
                            else {

                                Player1->SetCollissionFlag(true);
                                if (Player1->GetJumpingStatus())
                                    Player1->SetCollissionX(Player1->GetRectangle()->x);
                                else
                                    Player1->SetCollissionX(Player1->GetRectangle()->x + 5);

                            }
                        

                        }
                        else if (LevelItems.at(i)->GetGameObjectType() == "DestinationContainer") {

                            Player1->SetCollissionFlag(true);
                            if (Player1->GetJumpingStatus())
                                Player1->SetCollissionX(Player1->GetRectangle()->x);
                            else
                                Player1->SetCollissionX(Player1->GetRectangle()->x - 5);

                        }

                    }

                }

                if (!Collission) {
                    Player1->SetPlatformStatus(false);
                    Player1->SetPlatform(nullptr);
                }
                
                if (AcidAcquired && WaterAcquired && !PathShown) {

                    for (int i = 0; i < LevelItems.size(); i++) {

                        if (LevelItems.at(i)->GetSecret()) {
                            LevelItems.at(i)->ChangeAliveStatus(false);
                            PathShown = true;
                            break;
                        }
                   
                    }

                }

                if (MushroomSpawn && LevelItems.at(LevelItems.size() - 1)->GetMushAppeared()) {

                    MushroomColission = false;

                    for (int i = 0; i < LevelItems.size() - 1; i++) {

                        if (LevelItems.at(i)->GetGameObjectType() == "Platform" || LevelItems.at(i)->GetGameObjectType() == "PowerupBlock") {

                            if (SDL_HasIntersection(LevelItems.at(i)->GetRectangle(), LevelItems.at(LevelItems.size() - 1)->GetRectangle())) {

                                if (SDL_HasIntersection(LevelItems.at(i)->GetTopRect(), LevelItems.at(LevelItems.size() - 1)->GetRectangle())) {

                                    MushroomColission = true;

                                    if (!LevelItems.at(LevelItems.size() - 1)->GetPlatformStatus()) {

                                        cout << "Top" << endl;
                                        LevelItems.at(LevelItems.size() - 1)->SetPlatformStatus(true);
                                        LevelItems.at(LevelItems.size() - 1)->Translate(0.0, 0.0);
                                        LevelItems.at(LevelItems.size() - 1)->SetPlatform(LevelItems.at(i));
                                        //Player1->SetCoordinates(Player1->GetRectangle()->x, LevelItems.at(i)->GetRectangle()->y - 31);

                                    }

                                }
                                else if (SDL_HasIntersection(LevelItems.at(i)->GetLeftRect(), LevelItems.at(LevelItems.size() - 1)->GetRectangle())) {

                                    if (!LevelItems.at(LevelItems.size() - 1)->GetPlatform()) {

                                        cout << "Left" << endl;
                                        LevelItems.at(LevelItems.size() - 1)->SetCollissionFlag(true);
                                        LevelItems.at(LevelItems.size() - 1)->SetCollissionX(LevelItems.at(LevelItems.size() - 1)->GetRectangle()->x - 5);

                                    }
                                    else {

                                        if (LevelItems.at(LevelItems.size() - 1)->GetPlatform()->GetRectangle()->y != LevelItems.at(i)->GetRectangle()->y) {

                                            cout << "Left" << endl;
                                            LevelItems.at(LevelItems.size() - 1)->SetCollissionFlag(true);
                                            LevelItems.at(LevelItems.size() - 1)->SetCollissionX(LevelItems.at(LevelItems.size() - 1)->GetRectangle()->x - 5);

                                        }

                                    }

                                }
                                else if (SDL_HasIntersection(LevelItems.at(i)->GetRightRect(), LevelItems.at(LevelItems.size() - 1)->GetRectangle())) {

                                    if (!LevelItems.at(LevelItems.size() - 1)->GetPlatform()) {

                                        cout << "Left" << endl;
                                        LevelItems.at(LevelItems.size() - 1)->SetCollissionFlag(true);
                                        LevelItems.at(LevelItems.size() - 1)->SetCollissionX(LevelItems.at(LevelItems.size() - 1)->GetRectangle()->x + 5);

                                    }
                                    else {

                                        if (LevelItems.at(LevelItems.size() - 1)->GetPlatform()->GetRectangle()->y != LevelItems.at(i)->GetRectangle()->y) {

                                            cout << "Left" << endl;
                                            LevelItems.at(LevelItems.size() - 1)->SetCollissionFlag(true);
                                            LevelItems.at(LevelItems.size() - 1)->SetCollissionX(LevelItems.at(LevelItems.size() - 1)->GetRectangle()->x + 5);

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

                if (MushroomSpawn && !MushroomColission) {

                    LevelItems.at(LevelItems.size() - 1)->SetPlatformStatus(false);
                    LevelItems.at(LevelItems.size() - 1)->SetPlatform(nullptr);

                }



                if (Player1->GetJumpingStatus())
                    Player1->Jump();
                else
                    Player1->Move();

            

                if (nSpeedCount % 8 == 0) {

                    if (Level == "level1") {

                        for (int i = 0; i < 400; i++) {

                            if (!WaterAcquired)
                                Particles.at(i)->Move();

                        }

                        for (int i = 400; i < 800; i++) {

                            if (!AcidAcquired)
                                Particles.at(i)->Move();

                        }

                    }

                }

                for (int i = 0; i < LevelItems.size(); i++) {
                    LevelItems.at(i)->Move();
                }

                if (Level == "level2") {

                    if (DestinationAcid) {

                        if (!Seepage) {

                            if (Particles.at(AcidStart + 360)->GetRectangle()->x == Particles.at(0)->GetRectangle()->x) {

                                if (Particles.at(AcidStart + 360)->GetRectangle()->y + 2 == Particles.at(0)->GetRectangle()->y) {

                                    Seepage = true;
                                    cout << "Seepage" << endl;

                                }

                            }

                        }
                        else {

                            if (!SeepageFinished) {

                                Mix_PlayChannel(-1, Decay, 0);

                                SeepageFinished = true;

                                for (int i = 10 + ((SeepCounter * 40) + counter); i < (10 + (SeepCounter * 40)) + (20 - counter); i++) {

                                    if (Particles.at(i)->Alive()) {
                                        SeepageFinished = false;
                                        Particles.at(i)->DecAlphaValue(25);
                                    }

                                }

                                SeepCounter++;
                                counter = counter++;

                                if (SeepCounter == 8) {
                                    SeepCounter = 0;
                                    counter = 0;
                                }

                                if (SeepageFinished) {

                                    while (DrainCounter != 10) {

                                        for (int i = (AcidStart + 370) - (DrainCounter * 40); i < ((AcidStart + 370) - (DrainCounter * 40)) + 20; i++) {

                                            Particles.at(i)->Translate(0.0, TranslateCounter);
                                            if (TranslateCounter == 10)
                                                ReachedMax = true;

                                            if (!ReachedMax)
                                                TranslateCounter++;
                                            else
                                                TranslateCounter--;

                                            if (TranslateCounter == 0)
                                                TranslateCounter = 2;


                                        }

                                        ReachedMax = false;
                                        TranslateCounter = 2;

                                        for (int i = AcidStart + (DrainCounter * 40); i < (AcidStart + (DrainCounter * 40)) + 10; i++) {

                                            Particles.at(i)->Translate(2, TranslateCounter);
                                            if (TranslateCounter == 10)
                                                ReachedMax = true;

                                            if (!ReachedMax)
                                                TranslateCounter++;
                                            else
                                                TranslateCounter--;

                                            if (TranslateCounter == 0)
                                                TranslateCounter = 2;

                                        }

                                        ReachedMax = false;
                                        TranslateCounter = 2;

                                        for (int i = (AcidStart + 30) + (DrainCounter * 40); i < ((AcidStart + 30) + (DrainCounter * 40)) + 10; i++) {

                                            Particles.at(i)->Translate(-2, TranslateCounter);
                                            if (TranslateCounter == 10)
                                                ReachedMax = true;

                                            if (!ReachedMax)
                                                TranslateCounter++;
                                            else
                                                TranslateCounter--;

                                            if (TranslateCounter == 0)
                                                TranslateCounter = 2;


                                        }

                                        ReachedMax = false;
                                        TranslateCounter = 2;
                                        DrainCounter++;

                                    }

                                    DrainCounter = 0;


                                }

                            }

                        }

                        if (SeepageFinished) {

                            while (DrainCounter != 10) {

                                for (int i = (AcidStart + 370) - (DrainCounter * 40); i < ((AcidStart + 370) - (DrainCounter * 40)) + 20; i++) {

                                    Particles.at(i)->Move();

                                }

                                for (int i = AcidStart + (DrainCounter * 40); i < (AcidStart + (DrainCounter * 40)) + 10; i++) {

                                    Particles.at(i)->Move();


                                }

                                for (int i = (AcidStart + 30) + (DrainCounter * 40); i < (((AcidStart + 30)) + (DrainCounter * 40)) + 10; i++) {

                                    Particles.at(i)->Move();
                                }

                                DrainCounter++;

                            }

                            DrainCounter = 0;

                        }

                    }
                }


                SDL_RenderClear(gRenderer);

                SDL_RenderCopy(gRenderer, BackgroundTexture, nullptr, BackgroundRect);

                for (int i = 0; i < Player1->GetHealth(); i++) {

                    HeartRect->x = 362 + (i * 32);
                    SDL_RenderCopy(gRenderer, HeartTexture, nullptr, HeartRect);

                }

                if (WaterRect != nullptr) {

                    SDL_RenderCopy(gRenderer, WaterTexture, nullptr, WaterRect);

                }

                if (AcidRect != nullptr) {

                    SDL_RenderCopy(gRenderer, AcidTexture, nullptr, AcidRect);

                }

                if (Level == "level1") {


                    for (int i = 0; i < 400; i++) {

                        if (!WaterAcquired)
                            Particles.at(i)->Render(gRenderer);

                    }

                    for (int i = 400; i < 800; i++) {

                        if (!AcidAcquired)
                            Particles.at(i)->Render(gRenderer);

                    }

                }

                if (Level == "level2") {

                    for (int i = 0; i < 320; i++) {

                        Particles.at(i)->Render(gRenderer);


                    }

                    for (int i = WaterStart; i < WaterStart + 400; i++) {

                        if (DestinationWater)
                            Particles.at(i)->Render(gRenderer);

                    }

                    for (int i = AcidStart; i < AcidStart + 400; i++) {

                        if (DestinationAcid)
                            Particles.at(i)->Render(gRenderer);

                    }

                }

                for (int i = 0; i < LevelItems.size(); i++) {

                    if (LevelItems.at(i)->Alive())
                        LevelItems.at(i)->Render(gRenderer);

                }


                Player1->Render(gRenderer);

                //Update screen
                SDL_RenderPresent(gRenderer);  

                for (int i = 0; i < LevelItems.size(); i++) {
                    if (!LevelItems.at(i)->Alive()) {

                        if (LevelItems.at(i)->GetGameObjectType() == "Powerup")
                            MushroomSpawn = false;

                        delete LevelItems.at(i);
                        LevelItems.erase(LevelItems.begin() + i);

                    }
                }

                frameTime = SDL_GetTicks() - frameStart;

                if (frameDelay > frameTime) {
                    SDL_Delay(frameDelay - frameTime);
                }


            }

            for (int i = 0; i < LevelItems.size(); i++) {

                delete LevelItems.at(i);

            }

            LevelItems.clear();

            for (int i = 0; i < Particles.size(); i++) {

                delete Particles.at(i);

            }

            Particles.clear();

            delete Player1;
            Player1 = nullptr;

            SDL_DestroyTexture(BackgroundTexture);
            BackgroundTexture = nullptr;

            delete BackgroundRect;
            BackgroundRect = nullptr;

            SDL_DestroyTexture(HeartTexture);
            HeartTexture = nullptr;

            delete HeartRect;
            HeartRect = nullptr;

            Mix_FreeChunk(JumpSound);
            JumpSound = nullptr;

            Mix_FreeChunk(Pickup);
            Pickup = nullptr;

            Mix_FreeChunk(HurtSound);
            HurtSound = nullptr;

            Mix_FreeChunk(KillSound);
            KillSound = nullptr;

            Mix_FreeChunk(MushAcq);
            MushAcq = nullptr;

            Mix_FreeChunk(Decay);
            Decay = nullptr;

            EndScreen(LivesFinished, ObjectiveAchieved);

        }

        close();


    }

}

void InnitLevel1(vector<GameObject*>* LevelItems, vector<GameObject*>* Particles) {

    for (int i = 0; i < 3; i++)
        LevelItems->emplace_back(new Brick(70 + (i * 32), 668, gRenderer, "brick.png"));

    for (int i = 0; i < 3; i++)
        LevelItems->emplace_back(new Brick(166 + (i * 32), 620, gRenderer, "brick.png"));

    for (int i = 0; i < 4; i++)
        LevelItems->emplace_back(new Brick(230, 588 - (i * 32), gRenderer, "brick.png"));

    for (int i = 0; i < 4; i++)
        LevelItems->emplace_back(new Brick(102 - (i * 32), 540, gRenderer, "brick.png"));

  
    LevelItems->emplace_back(new PowerupBlock(40, 430, gRenderer, "QuestionBlock.png"));

    for (int i = 0; i < 10; i++)
        LevelItems->emplace_back(new Brick(166 + (i * 32), 444, gRenderer, "brick.png"));
    
    LevelItems->emplace_back(new Enemy(230, 412, gRenderer, "Goomba.png"));
    LevelItems->at(LevelItems->size() - 1)->SetDistance(192.0);

    for (int i = 0; i < 2; i++)
        LevelItems->emplace_back(new Brick(454, 476 + (i * 32), gRenderer, "brick.png"));

    for (int i = 0; i < 2; i++)
        LevelItems->emplace_back(new Brick(486, 476 + (i * 32), gRenderer, "brick.png"));

    for (int i = 0; i < 12; i++)
        LevelItems->emplace_back(new Brick(518 + (i * 32), 508, gRenderer, "brick.png"));

    LevelItems->at(LevelItems->size() - 1)->SetSecret(true);

    LevelItems->emplace_back(new Enemy(774, 476, gRenderer, "Goomba.png"));
    LevelItems->at(LevelItems->size() - 1)->SetDistance(-192.0);

    for (int i = 0; i < 10; i++)
        LevelItems->emplace_back(new Brick(390 - (i * 28), 368 - (i * 32), gRenderer, "brick.png"));

    for (int i = 0; i < 4; i++)
        LevelItems->emplace_back(new Brick(106 - (i * 32), 80, gRenderer, "brick.png"));

    LevelItems->emplace_back(new SourceContainer(10, 20, gRenderer, "SourceContainer.png"));

    for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++) {

            Particles->emplace_back(new Water(22 + (j * 2), 32 + (i * 2), gRenderer, "Water.png"));


        }

    }

    for (int i = 0; i < 8; i++)
        LevelItems->emplace_back(new Brick(454 + (i * 28), 304 - (i * 32), gRenderer, "brick.png"));

    for (int i = 0; i < 8; i++)
        LevelItems->emplace_back(new Brick(650 + (i * 32), 80, gRenderer, "brick.png"));

    LevelItems->emplace_back(new SourceContainer(826, 20, gRenderer, "SourceContainer.png"));

    for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++) {

            Particles->emplace_back(new Acid(838 + (j * 2), 32 + (i * 2), gRenderer, "Acid.png"));
            //Particles->at(Particles->size() - 1)->SetDestinationStatus(true);

        }

    }

    LevelItems->emplace_back(new Door(836, 636, gRenderer, "Door.png"));

    int Distcounter = 0;
    int counter = 0;

    for (int i = 0; i < 300; i++) {

        if (counter < 9) {

            Particles->at(i)->SetDistance(Distcounter);
            Particles->at(i)->Translate(0.0, -1 * Distcounter);
            if(i % 2 == 0)
                Distcounter = Distcounter++;

        }
        else {

            Particles->at(i)->SetDistance(Distcounter);
            Particles->at(i)->Translate(0.0, -1 * Distcounter);
            if(i % 2 == 0)
                Distcounter = Distcounter--;


        }

        counter++;

        if (counter > 19) {

            counter = 0;
            Distcounter = 0;

        }


    }

    for (int i = 400; i < 700; i++) {

        if (counter < 9) {

            Particles->at(i)->SetDistance(Distcounter);
            Particles->at(i)->Translate(0.0, -1 * Distcounter);
            if (i % 2 == 0)
                Distcounter = Distcounter++;

        }
        else {

            Particles->at(i)->SetDistance(Distcounter);
            Particles->at(i)->Translate(0.0, -1 * Distcounter);
            if (i % 2 == 0)
                Distcounter = Distcounter--;


        }

        counter++;

        if (counter > 19) {

            counter = 0;
            Distcounter = 0;

        }


    }


}

void InnitLevel2(vector<GameObject*>* LevelItems, vector<GameObject*>* Particles) {


    for (int i = 0; i < LevelItems->size(); i++) {
            
        delete LevelItems->at(i);

    }

    LevelItems->clear();

    for (int i = 0; i < Particles->size(); i++) {

        delete Particles->at(i);

    }

    Particles->clear();

    for (int i = 0; i < 2; i++)
        LevelItems->emplace_back(new Brick(70 - (i * 32), 620 - (i * 32), gRenderer, "brick.png"));

    for (int i = 0; i < 2; i++)
        LevelItems->emplace_back(new Brick(38 - (i * 32), 588, gRenderer, "brick.png"));

    for (int i = 0; i < 6; i++)
        LevelItems->emplace_back(new Brick(134 + (i * 32), 524 - (i * 32), gRenderer, "brick.png"));

    for (int i = 0; i < 5; i++)
        LevelItems->emplace_back(new Brick(326 + (i * 32), 396 + (i * 32), gRenderer, "brick.png"));

    for (int i = 0; i < 4; i++)
        LevelItems->emplace_back(new Brick(454, 556 + (i * 32), gRenderer, "brick.png"));

    for (int i = 0; i < 4; i++)
        LevelItems->emplace_back(new Brick(422 + (i * 32), 332 - (i * 32), gRenderer, "brick.png"));


    LevelItems->emplace_back(new Brick(486, 620, gRenderer, "brick.png"));

    for (int i = 0; i < 11; i++)
        LevelItems->emplace_back(new Brick(550 + (i * 32), 236, gRenderer, "brick.png"));

    LevelItems->emplace_back(new Enemy(614, 204, gRenderer, "Goomba.png"));
    LevelItems->at(LevelItems->size() - 1)->SetDistance(192.0);

    LevelItems->emplace_back(new Door(836, 172, gRenderer, "Door.png"));

    LevelItems->emplace_back(new DestinationWater(200, 572, gRenderer, "DestinationContainerWater.png"));

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 40; j++) {

            Particles->emplace_back(new Wood(224 + (j * 2), 646 + (i * 2), gRenderer, "Wood.png"));


        }

    }

    LevelItems->emplace_back(new DestinationAcid(586, 572, gRenderer, "DestinationContainerAcid.png"));


}

void EndScreen(bool LivesFinished, bool ObjectiveSuccessfull) {

    string Text;

    if (LivesFinished) {

        Text = "You Ran Out Of Lives! Better Luck Next Time.";

    }
    else {

        if (ObjectiveSuccessfull) {

            Text = "Objective Complete! There Was No Seepage.";


        }
        else {

            Text = "Objective Failed! There Was Seepage.";


        }


    }

    SDL_Rect* TextRect = new SDL_Rect();

    SDL_Surface* TextSurface = TTF_RenderText_Solid(gFont, Text.c_str(), {0,0,0});

    SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(gRenderer, TextSurface);

    SDL_FreeSurface(TextSurface);

    SDL_QueryTexture(TextTexture, nullptr, nullptr, &TextRect->w, &TextRect->h);
    TextRect->x = (nScreenWidth - TextRect->w) / 2;
    TextRect->y = (nScreenHeight - TextRect->h) / 2;

    bool Viewing = true;
    SDL_Event e;

    while (Viewing) {

        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                Viewing = false;
            }

        }

        SDL_RenderClear(gRenderer);

        SDL_RenderCopy(gRenderer, TextTexture, nullptr, TextRect);

        SDL_RenderPresent(gRenderer);

    }

    SDL_DestroyTexture(TextTexture);
    TextTexture = nullptr;

    delete TextRect;
    TextRect = nullptr;

}
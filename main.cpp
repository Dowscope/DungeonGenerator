/* Dungeon Generator
 * Created By Tim Dowling
 * Date: Aug 16, 2020
 */

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include "Screen.h"
#include "World.h"
#include "Player.h"

// Declare Functions
void update();
void render();
void renderWalls();
void renderRooms();
void updateCamera();

// Declare the width and height that the window will be also the 
// resolution of tile size.
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int WORLD_RESOLUTION = 512;
const int PLAYER_RESOLUTION = 64;

// Declare World Demensions
const int WORLD_WIDTH = 25;
const int WORLD_HEIGHT = 25;

// Frame Rate
const int FPS = 60;

// Declare the Screen object.
Screen* screen;

// Declare GLOBAL game objects.
World* world;
Player* player;
SDL_Rect mainCamera;
int playerSpeed = 5;

int main(int argc, char const *argv[])
{
    // Initialize the randomizer
    srand((unsigned int)time(0));
    //srand(1);

    // Set the title of the project
    char title[] = "Dungeon Generator";

    // Setup the camera
    mainCamera = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};

    // Initialize the screen
    screen = new Screen(WINDOW_WIDTH, WINDOW_HEIGHT, title, &mainCamera);
    screen->initializeTmpSurface(WORLD_WIDTH * WORLD_RESOLUTION, WORLD_HEIGHT * WORLD_RESOLUTION);

    // Declare a switch for the main game loop
    bool isRunning = true;

    // Game Timers
    Uint32 starting_tick;


    /* Setup game objects  */  
    world = new World(WORLD_WIDTH, WORLD_HEIGHT);
    player = new Player(0, 0);
    SDL_Event e;

    // Main Game Loop
    std::cout << "Game Starting!" << std::endl;
    while (isRunning){

        starting_tick = SDL_GetTicks();

        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                isRunning = false;
                break;
            }
            else if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_d){
                    int tmpX = player->getX() + 1 * playerSpeed;
                    if (tmpX >= WORLD_WIDTH*WORLD_RESOLUTION - 1 - WORLD_RESOLUTION) {tmpX = WORLD_WIDTH*WORLD_RESOLUTION - 1 - WORLD_RESOLUTION;}
                    player->setX(tmpX);
                }
                if (e.key.keysym.sym == SDLK_a){
                    int tmpX = player->getX() - 1 * playerSpeed;
                    if (tmpX < 0) {tmpX = 0;}
                    player->setX(tmpX);
                }
                if (e.key.keysym.sym == SDLK_w){
                    int tmpY = player->getY() - 1 * playerSpeed;
                    if (tmpY < 0) {tmpY = 0;}
                    player->setY(tmpY);
                }
                if (e.key.keysym.sym == SDLK_s){
                    int tmpY = player->getY() + 1 * playerSpeed;
                    if (tmpY >= WORLD_HEIGHT*WORLD_RESOLUTION - 1 - WORLD_RESOLUTION) {tmpY = WORLD_HEIGHT*WORLD_RESOLUTION - 1 - WORLD_RESOLUTION;}
                    player->setY(tmpY);
                }
            }
            
        }

        // Cap the frame rate
        if ((1000/FPS) > SDL_GetTicks() - starting_tick){
            SDL_Delay(1000/FPS - (SDL_GetTicks() - starting_tick));
        }

        update();

        screen->clear();
        render();
        screen->present();
    }

    std::cout << "Game Ended" << std::endl;
    screen->terminate();
    delete screen;

    std::cout << "Program Completed" << std::endl;
    return 0;
}

void update(){
    updateCamera();
}

void render() {
    screen->renderWorldFloor(world->getWorldWidth() * WORLD_RESOLUTION, world->getWorldHeight() * WORLD_RESOLUTION);
    renderWalls();
    //renderRooms();
    screen->drawPlayer(player->getX(), player->getY(), PLAYER_RESOLUTION);
}

void renderWalls(){
    for (int y = 0; y < WORLD_HEIGHT; y++)  
    {
        for (int x = 0; x < WORLD_WIDTH; x++)
        {
            Tile* t = world->getTileAt(x, y);
            if (&t){
                int pX = t->getX();
                int pY = t->getY();
                // TOP
                if (t->isWallAt(0))
                    screen->drawWall(pX * WORLD_RESOLUTION, pY * WORLD_RESOLUTION, WORLD_RESOLUTION, 2);
                // RIGHT
                if (t->isWallAt(1)) 
                    screen->drawWall(pX * WORLD_RESOLUTION + WORLD_RESOLUTION, pY * WORLD_RESOLUTION, 2, WORLD_RESOLUTION);
                // BOTTOM
                if (t->isWallAt(2))
                    screen->drawWall(pX * WORLD_RESOLUTION, pY * WORLD_RESOLUTION + WORLD_RESOLUTION, WORLD_RESOLUTION, 2);
                // LEFT
                if (t->isWallAt(3))
                    screen->drawWall(pX * WORLD_RESOLUTION, pY * WORLD_RESOLUTION, 2, WORLD_RESOLUTION);
            }
        }
    }
}

void renderRooms(){
    std::vector<Room*> rooms = world->getRooms();

    for (int i = 0; i < rooms.size(); i++)
    {
        //SDL_Rect r = {rooms[i]->x * WORLD_RESOLUTION, rooms[i]->y * WORLD_RESOLUTION, rooms[i]->w * WORLD_RESOLUTION, rooms[i]->h * WORLD_RESOLUTION};
        //screen->renderRoom(r);
        Room* r = rooms[i];
        screen->drawWall(r->doorLocation.x * WORLD_RESOLUTION, r->doorLocation.y * WORLD_RESOLUTION, WORLD_RESOLUTION, WORLD_RESOLUTION);
    }
}

void updateCamera(){
    mainCamera.x = player->getX() - mainCamera.w/2;
    mainCamera.y = player->getY() - mainCamera.h/2;

    if(mainCamera.x <= 0) { mainCamera.x = 0; }
    if(mainCamera.y <= 0) { mainCamera.y = 0; }
    if(mainCamera.x > WORLD_WIDTH*WORLD_RESOLUTION-mainCamera.w) { mainCamera.x = WORLD_WIDTH*WORLD_RESOLUTION-mainCamera.w; }
    if(mainCamera.y > WORLD_HEIGHT*WORLD_RESOLUTION-mainCamera.h) { mainCamera.y = WORLD_HEIGHT*WORLD_RESOLUTION-mainCamera.h; }     
}
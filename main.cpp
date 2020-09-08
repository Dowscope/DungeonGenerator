/* Dungeon Generator
 * Created By Tim Dowling
 * Date: Aug 16, 2020
 */

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.h"
#include "World.h"

// Declare Functions
void update();
void render();

// Declare the width and height that the window will be also the 
// resolution of tile size.
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;
const int RESOLUTION = 32;

// Declare World Demensions
const int WORLD_WIDTH = 100;
const int WORLD_HEIGHT = 100;

// Frame Rate
const int FPS = 60;

// Declare the Screen object.
Screen *screen;

// Declare GLOBAL game objects.
World *world;
SDL_Rect mainCamera;
int playerSpeed = 5;

int main(int argc, char const *argv[])
{
    // Initialize the randomizer
    srand(time(NULL));

    // Set the title of the project
    char title[] = "Dungeon Generator";

    // Setup the camera
    mainCamera = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};

    // Initialize the screen
    screen = new Screen(WINDOW_WIDTH, WINDOW_HEIGHT, title, &mainCamera);
    screen->initializeTmpSurface(WORLD_WIDTH * RESOLUTION, WORLD_HEIGHT * RESOLUTION);

    // Declare a switch for the main game loop
    bool isRunning = true;

    // Game Timers
    Uint32 starting_tick;


    /* Setup game objects  */  
    world = new World(WORLD_WIDTH, WORLD_HEIGHT);
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
                    mainCamera.x += 1 * playerSpeed;
                }
                if (e.key.keysym.sym == SDLK_a){
                    mainCamera.x -= 1 * playerSpeed;
                }
                if (e.key.keysym.sym == SDLK_w){
                    mainCamera.y -= 1 * playerSpeed;
                }
                if (e.key.keysym.sym == SDLK_s){
                    mainCamera.y += 1 * playerSpeed;
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

}

void render() {
    screen->renderWorldFloor(world->getWorldWidth() * RESOLUTION, world->getWorldHeight() * RESOLUTION);
    std::vector<Room*> rooms = world->getRooms();

    for (int i = 0; i < rooms.size(); i++)
    {
        SDL_Rect r = {rooms[i]->getX() * RESOLUTION, rooms[i]->getY() * RESOLUTION, rooms[i]->getW() * RESOLUTION, rooms[i]->getH() * RESOLUTION};
        screen->renderRoom(r);
    }

    screen->drawPlayer(RESOLUTION);
}
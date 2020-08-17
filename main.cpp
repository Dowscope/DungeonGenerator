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
#include "Room.h"

// Declare Functions
void update();
void render();

// Declare the width and height that the window will be.
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

// Declare the Screen object.
Screen *screen;

int main(int argc, char const *argv[])
{
    // Initialize the randomizer
    srand(time(NULL));

    // Set the title of the project
    char title[] = "Dungeon Generator";

    // Initialize the screen
    screen = new Screen(WINDOW_WIDTH, WINDOW_HEIGHT, title);

    // Declare a switch for the main game loop
    bool isRunning = true;

    /* Setup game objects  */    

    // Main Game Loop
    std::cout << "Game Starting!" << std::endl;
    while (isRunning){
        SDL_Event e;
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                isRunning = false;
            }
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
    
}
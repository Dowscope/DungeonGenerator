/************************************************************
 * Screen.h
 * Created by Tim Dowling
 * 
 * File used to display to a window.  Must include this file 
 * in your program
 * ***********************************************************/

#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <iostream>


class Screen
{
private:
    int _screenWidth, _screenHeight;
    char* _title;
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;

    bool _initialize();
public:
    Screen(int w, int h, char* aTitle);
    ~Screen();

    bool didInitialize = false;

    void clear();
    void present();
    void terminate();

    void renderStar(int x, int y);
};

Screen::Screen(int w, int h, char* aTitle)
{
    this->_screenWidth = w;
    this->_screenHeight = h;
    this->_title = aTitle;

    didInitialize = _initialize();
}

Screen::~Screen()
{
}

bool Screen::_initialize()
{
    // Initialize SDL
    std::cout << "Initializing SDL....";
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SCREEN_H: SDL did not initialize" << std::endl;
        return false;
    }
    std::cout << "OK!" << std::endl;

    // Create our game window
    std::cout << "Creating Window....";
    mainWindow = SDL_CreateWindow(_title,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    _screenWidth,
                                    _screenHeight,
                                    0);
    if (mainWindow == NULL) {
        std::cout << "SCREEN_H: Window was not created" << std::endl;
        return false;
    }
    std::cout << "OK!" << std::endl;

    // Create our renderer
    std::cout << "Creating Renderer....";
    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mainRenderer == NULL) {
        std::cout << "SCREEN_H: Renderer was not created" << std::endl;
        return false;
    }
    std::cout << "OK!" << std::endl;
    return true;
}

// Function that will call the SDL function to clear the renderer
void Screen::clear() {
    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mainRenderer);
}

// Function that will call the SDL function to present the renderer to the screen
void Screen::present() {
    SDL_RenderPresent(mainRenderer);
}

void Screen::terminate(){
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

void Screen::renderStar(int x, int y){
    SDL_Rect r = {x,y,4,4};
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(mainRenderer, &r);
}

#endif
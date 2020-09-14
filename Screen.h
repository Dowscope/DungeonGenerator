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
    SDL_Rect* _mainCamera;
    SDL_Window* _mainWindow;
    SDL_Renderer* _mainRenderer;
    SDL_Surface* _mainSurface;
    SDL_Surface* _groundSurface;

    bool _initialize();
public:
    Screen(int w, int h, char* aTitle, SDL_Rect* aCamera);
    ~Screen();

    bool didInitialize = false;

    void initializeTmpSurface(int width, int height);

    void clear();
    void present();
    void terminate();

    void renderRoom(SDL_Rect room);
    void renderWorldFloor(int width, int height);
    void drawPlayer(int x, int y, int resolution);
    void drawWall(int x1, int y1, int x2, int y2);
};

Screen::Screen(int w, int h, char* aTitle, SDL_Rect* aCamera):
    _screenWidth(w), _screenHeight(h), _title(aTitle), _mainCamera(aCamera)
{
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
    _mainWindow = SDL_CreateWindow(_title,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    _screenWidth,
                                    _screenHeight,
                                    0);
    if (_mainWindow == NULL) {
        std::cout << "SCREEN_H: Window was not created" << std::endl;
        return false;
    }
    std::cout << "OK!" << std::endl;

    // Create our renderer
    std::cout << "Creating Renderer....";
    _mainRenderer = SDL_CreateRenderer(_mainWindow, -1, SDL_RENDERER_SOFTWARE);
    if (_mainRenderer == NULL) {
        std::cout << "SCREEN_H: Renderer was not created" << std::endl;
        return false;
    }
    std::cout << "OK!" << std::endl;

    // Grab the screen surface
    std::cout << "Grabbing Surface from Screen....";
    _mainSurface = SDL_GetWindowSurface(_mainWindow);
    std::cout << "OK!" << std::endl;

    return true;
}

// Function to init the tmp surface to draw to.
void Screen::initializeTmpSurface(int width, int height){
    std::cout << "Creating Temp Surface....";
    _groundSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    std::cout << "OK!" << std::endl;
}

// Function that will call the SDL function to clear the renderer
void Screen::clear() {
    SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);
    SDL_RenderClear(_mainRenderer);
}

// Function that will call the SDL function to present the renderer to the screen
void Screen::present() {
    //SDL_RenderPresent(_mainRenderer);
    SDL_BlitSurface(_groundSurface, _mainCamera, _mainSurface, NULL);
    //SDL_BlitSurface(_playerSurface, NULL, _mainSurface, NULL);
    SDL_UpdateWindowSurface(_mainWindow);
}

void Screen::terminate(){
    SDL_FreeSurface(_groundSurface);
    SDL_DestroyRenderer(_mainRenderer);
    SDL_DestroyWindow(_mainWindow);
    SDL_Quit();
}

void Screen::renderRoom(SDL_Rect room){
    SDL_FillRect(_groundSurface, &room, SDL_MapRGB(_groundSurface->format, 255, 255, 255));
}

void Screen::renderWorldFloor(int width, int height){
    SDL_Rect r = {0,0,width,height};
    SDL_FillRect(_groundSurface, &r, SDL_MapRGB(_groundSurface->format, 0, 200, 0));
}

void Screen::drawPlayer(int x, int y, int resolution){
    SDL_Rect r = {x, y,resolution,resolution};
    SDL_FillRect(_groundSurface, &r, SDL_MapRGB(_groundSurface->format, 255, 0, 0));
}

void Screen::drawWall(int x, int y, int w, int h){
    SDL_Rect r = {x, y, w, h};
    SDL_FillRect(_groundSurface, &r, SDL_MapRGB(_groundSurface->format, 255, 255, 255));
}

#endif
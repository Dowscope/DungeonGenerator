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

#endif
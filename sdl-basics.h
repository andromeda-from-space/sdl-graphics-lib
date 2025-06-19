#ifndef SDL_BASICS_H
#define SDL_BASICS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

// TODO - pass strings by reference
// TODO - deep copying

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

class SDLWindowWrapper {
    public:
        //---------- CONSTRUCTORS & DESTRUCTOR ----------
        SDLWindowWrapper();
        SDLWindowWrapper(int width, int height, string title);
        SDLWindowWrapper(const SDLWindowWrapper & other);
        SDLWindowWrapper& operator=(const SDLWindowWrapper & other);
        ~SDLWindowWrapper();

        //---------- TUTORIAL CODE ----------
        // Lesson 1 - HelloWorld
        void lesson1();
    private:
        // Width of the screen
        int screenWidth;
        // Height of the screen
        int screenHeight;
        // Pointer for the SDL_Window
        SDL_Window* window;
        // Pointer for the SDL_Surface
        SDL_Surface* screenSurface;

        //---------- PRIVATE UTILITIES ----------
        // Initialize the SDL subsystems for use
        bool init(string title);
};

#endif
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

// Lesson 4 - Key Press Enumeration
//Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

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
        // Note - some of the lessons require adding additional code not represented here
        // Lesson 1 - HelloWorld
        void lesson1();
        // Lesson 2 - blitting a BMP
        void lesson2();
        // Lesson 3 - events
        void lesson3();
        // Lesson 4 - key presses
        void lesson4();
        // Lesson 5 - optimized loading
        void lesson5();
        // Lessonm 6 - extension libraries for SDL
        void lesson6();
        // Lesson 7 - texture loading and rendering
        void lesson7();
        // Lesson 8 - geometry rendering
        void lesson8();
        // Lesson 9 - view port
        void lesson9();
        // Lesson 10 - Color keying
        void lesson10();
        // Lesson 11 - Clipping and rendering sprite sheets
        void lesson11();
        // Lesson 12 - Color modulation
        void lesson12();
        // Lesson 13 - Alpha Blending
        void lesson13();

        //---------- UTILITIES ----------
        // Load function for bmp images
        SDL_Surface* loadSurface(string path);
    private:
        // Width of the screen
        int screenWidth;
        // Height of the screen
        int screenHeight;
        // Pointer for the SDL_Window
        SDL_Window* window;
        // Pointer for the SDL_Surface
        SDL_Surface* windowSurface;

        //---------- PRIVATE UTILITIES ----------
        // Initialize the SDL subsystems for use
        bool init(string title);
};

#endif
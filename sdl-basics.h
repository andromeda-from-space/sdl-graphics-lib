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
        // Lesson 14 - Animated Sprites and VSync
        void lesson14();
        // Lesson 15 - Rotation and Flipping
        void lesson15();
        // Lesson 16 - True Type Fonts
        void lesson16();
        // Lesson 17 - Mouse Events
        void lesson17();
        // Lesson 18 - Key States
        void lesson18();
        // Lesson 19 - Gamepads and Joysticks
        void lesson19();
        // Lesson 20 - Force Feedback
        void lesson20();
        // Lesson 21 - Sound eeffects and Music
        void lesson21();
        // Lesson 22 - Timing
        void lesson22();
        // Lesson 23 - Advanced Timers
        void lesson23();
        // Lesson 24 - Calculating Frame Rate
        void lesson24();
        // Lesson 25 - Capping Frame Rate
        void lesson25();
        // Lesson 26 - Motion
        void lesson26();
        // Lesson 27 - Collision detection
        void lesson27();
        // Lesson 28 - Per-pixel collision detection
        void lesson28();
        // Lesson 29 - Circular collision detection
        void lesson29();
        // Lesson 30 - Scrolling
        void lesson30();

        //---------- UTILITIES ----------
        // Load function for bmp images
        // --DEPRECATED--
        SDL_Surface* loadSurface(string path);
        // Load textures as opposed to surfaces for hardware rendering
        // --DEPRECATED--
        SDL_Texture* loadTexture(string path);
    private:
        // Width of the screen
        int screenWidth;
        // Height of the screen
        int screenHeight;
        // Pointer for the SDL_Window
        SDL_Window* window;
        // Renderer for the engine
        SDL_Renderer* renderer;
        // Pointer for the SDL_Surface
        // --DEPRECATED--
        SDL_Surface* windowSurface;

        //---------- PRIVATE UTILITIES ----------
        // Initialize the SDL subsystems for use
        bool init(string title);
};

class SDLTextureWrapper {
    public:
        //---------- CONSTRUCTORS & DESTRUCTOR ----------
        SDLTextureWrapper();
        SDLTextureWrapper(const SDLTextureWrapper& other);
        SDLTextureWrapper& operator=(const SDLTextureWrapper& other);
        ~SDLTextureWrapper();

        //---------- UTILITIES ----------
        // Loads an image from a file
        bool loadFromFile(SDL_Renderer* renderer, string path);
        // Deallocates the loaded image
        void free();
        // Renders the tecture ata given point with the provided renderer
        void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);
        // Performs color modulation which multiplies the colors in the texture by the fraction val / 255
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        //---------- ACCESSORS ----------
        int getWidth();
        int getHeight();
    private:
        // Texture pointer
        SDL_Texture* texture;
        // Image size
        int width;
        int height;
};

#endif
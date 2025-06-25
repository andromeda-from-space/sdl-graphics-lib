#ifndef SDL_BASICS_H
#define SDL_BASICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

// TODO - pass strings by reference
// TODO - deep copying
// TODO - shared pointers
// TODO - portability of fprintf
// TODO - more sophisticated text handling

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

// Lesson 17 - Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

class SDLWindowWrapper {
    public:
        //---------- CONSTRUCTORS & DESTRUCTOR ----------
        SDLWindowWrapper();
        SDLWindowWrapper(int width, int height, std::string title, bool useTTF = false);
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
        SDL_Surface* loadSurface(std::string path);
        // Load textures as opposed to surfaces for hardware rendering
        // --DEPRECATED--
        SDL_Texture* loadTexture(std::string path);
        // Saves what's currently in the window
        void saveImg(std::string path);
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
        // Boolean for whether or not the TTF subsystem is started
        bool useTTF;

        //---------- PRIVATE UTILITIES ----------
        // Initialize the SDL subsystems for use
        bool init(std::string title);
};

/*
SDLTextureWrapper

Intended as a support class for the SDLWindowWrapper Class. Performs very basic 2D texture rendering using the GPU accelerated rendering provided by SDL.
*/
class SDLTextureWrapper {
    public:
        //---------- CONSTRUCTORS & DESTRUCTOR ----------
        SDLTextureWrapper();
        SDLTextureWrapper(const SDLTextureWrapper& other);
        SDLTextureWrapper& operator=(const SDLTextureWrapper& other);
        ~SDLTextureWrapper();

        //---------- UTILITIES ----------
        // Loads an image from a file
        bool loadFromFile(SDL_Renderer* renderer, std::string path);
        // Deallocates the loaded image
        void free();
        // Renders the tecture at a given point with the provided renderer
        void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
        // Performs color modulation which multiplies the colors in the texture by the fraction val / 255
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        // Set the value of the alpha channel
        void setAlpha(Uint8 alpha);
        // Set the blend mode of the texture
        void setBlendMode(SDL_BlendMode blending);
        // Create a textuyre for some text
        bool createTextTexture(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color& color);

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

/*
SDLTextBox

Intended as a support class for the SDLWindowWrapper Class. Performs very basic 2D text rendering using the GPU accelerated rendering provided by SDL.
*/
class SDLTextBox{
    public:
        //---------- CONSTRUCTORS & DESTRUCTOR ----------
        SDLTextBox();
        SDLTextBox(const SDLTextureWrapper& other);
        SDLTextBox& operator=(const SDLTextureWrapper& other);
        ~SDLTextBox();

        //---------- UTILITIES ----------
        // Loads the font
        bool loadFromFile(std::string path, int size);
        // Deallocates the font
        void free();
        // Render the text box in the provided location
        void render(std::string text, SDL_Renderer* renderer, int x, int y);
    private:
        // Pointer to the font the text box will use
        TTF_Font* font;
        // Background Color - default is transparent
        SDL_Color backgroundColor;
        // Text Color - default is black
        SDL_Color textColor;
};

/*
SDLButton

A class to make buttons in SDL using mouse events. Code is a little difficult to use. Main take away is the mouse events.
*/
class SDLButton {
    public:
        //---------- CONSTRUCTORS & DESTRUCTOR ----------
        SDLButton();
        SDLButton(SDL_Renderer* renderer, std::string spriteSheet, SDL_Rect* spriteClips, int numSprites);
        SDLButton(const SDLButton& other);
        SDLButton& operator=(const SDLButton& other);
        ~SDLButton();

        //---------- UTILITIES ----------
        // Load the sprite sheet for the button
        bool loadFromFile(SDL_Renderer* renderer, std::string path);
        // Sets top left position
        void setPosition( int x, int y );
        // Handles mouse event and sets the sprite accordingly
        void handleEvent( SDL_Event* e );
        // Shows button sprite
        void render(SDL_Renderer* renderer);
    private:
        // Top left position
        SDL_Point position;
        // Currently used global sprite
        LButtonSprite currentSprite;
        // Texture wrapper 
        SDLTextureWrapper* buttonSpriteSheet;
        // Clips for the button
        SDL_Rect* spriteClips;
        // Number of different button sprites
        int numSprites;
};


/*
SDLTimer

Uses the SDL Library to create a timer that can be started stopped and paused. Since the SDL_GetTicks reads the time from the start of the program, this allows for the program to ignore time when paused.
*/
class SDLTimer {
    public:
        //---------- CONSTRUCTORS & DESTRUCTOR ----------
        SDLTimer();

        //---------- UTILITIES ----------
        // Start the timer - resets the timer
        void start();
        // Stop the timer - resest the timer in unstarted state
        void stop();
        // Pause the timer
        void pause();
        // Unpause the timer
        void unpause();
        // Gets the timer's time
        Uint32 getTicks();
        // Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        // The clock time when the timer started
        Uint32 startTicks;

        // The ticks stored when the timer was paused
        Uint32 pausedTicks;

        // Flag for the timer being paused
        bool paused;
        // Flag for the timer being started
        bool started;
};

#endif
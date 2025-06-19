#include "sdl-basics.h"

//---------- CONSTRUCTORS & DESTRUCTOR ----------
SDLWindowWrapper::SDLWindowWrapper() : screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), window(nullptr), screenSurface(nullptr){
    init("SDL Window");
}

SDLWindowWrapper::SDLWindowWrapper(int width, int height, string title) : screenWidth(width), screenHeight(height), window(nullptr), screenSurface(nullptr){
    init(title);
}

SDLWindowWrapper::SDLWindowWrapper(const SDLWindowWrapper & other){
    // TODO
}

SDLWindowWrapper& SDLWindowWrapper::operator=(const SDLWindowWrapper & other){
    // TODO
    return *this;
}

SDLWindowWrapper::~SDLWindowWrapper(){
    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL Subsystems
    SDL_Quit();
}

//---------- TUTORIAL CODE ----------
void SDLWindowWrapper::lesson1(){
    //Fill the surface white
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
    
    //Update the surface
    SDL_UpdateWindowSurface( window );
    
    //Hack to get window to stay up
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
}

//---------- PRIVATE UTILITIES ----------
bool SDLWindowWrapper::init(string title){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        // TODO - exceptions?
        return false;
    } else{
        // Create the window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if(!window){
            fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
            // TODO - exceptions?
            return false;
        } else {
            // Get the window surface
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return true;
}
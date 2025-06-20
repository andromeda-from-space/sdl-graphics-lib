#include <SDL2/SDL_image.h>

#include "sdl-basics.h"

//--------------------------------------------------------------------
//---------- SDLWindowWrapper ----------------------------------------
//--------------------------------------------------------------------
//---------- CONSTRUCTORS & DESTRUCTOR ----------
SDLWindowWrapper::SDLWindowWrapper() : screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), window(nullptr), windowSurface(nullptr){
    init("SDL Window");
}

SDLWindowWrapper::SDLWindowWrapper(int width, int height, string title) : screenWidth(width), screenHeight(height), window(nullptr), windowSurface(nullptr){
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
    // Destroy the surface
    SDL_FreeSurface(windowSurface);
    windowSurface = nullptr;

    // Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL Subsystems
    IMG_Quit();
    SDL_Quit();
}

//---------- TUTORIAL CODE ----------
void SDLWindowWrapper::lesson1(){
    //Fill the surface white
    SDL_FillRect( windowSurface, NULL, SDL_MapRGB( windowSurface->format, 0xFF, 0xFF, 0xFF ) );
    
    //Update the surface
    SDL_UpdateWindowSurface( window );
    
    //Hack to get window to stay up
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
}

void SDLWindowWrapper::lesson2(){
    // Nominally prt of init()
	// Load splash image
	SDL_Surface* gHelloWorld = nullptr;
    gHelloWorld = SDL_LoadBMP( "hello_world.bmp" );
	if(!gHelloWorld)
	{
		fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
	} else {
        // Main loop
        //Apply the image
        SDL_BlitSurface( gHelloWorld, NULL, windowSurface, NULL );
        
        //Update the surface
        SDL_UpdateWindowSurface(window);

        //Hack to get window to stay up
        SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
    }
    
    // Nominally part of close()
    // Deallocate surface
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;
}

void SDLWindowWrapper::lesson3(){
    // Nominally prt of init()
	// Load splash image
	SDL_Surface* gHelloWorld = nullptr;
    gHelloWorld = SDL_LoadBMP( "hello_world.bmp" );
	if(!gHelloWorld)
	{
		fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
	} else {
        // Main loop
        // The current event
        SDL_Event e;
        // Flag for quitting
        bool quit = false;
        while( quit == false ){
            // Remove all events from the queue
            while( SDL_PollEvent( &e ) ){
                // Here is where event processing goes
                if( e.type == SDL_QUIT ){
                    quit = true;
                }
                
                // Here is where building the image goes
                // Blit the image on each pass
                SDL_BlitSurface( gHelloWorld, NULL, windowSurface, NULL );

                // Update the surface of the window to display the new image
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    
    // Nominally part of close()
    // Deallocate surface
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;
}

void SDLWindowWrapper::lesson4(){
    // Load the data
    // Nominally prt of init()
    // Array of file names for loading
    string filenames[] = {
        "press.bmp",
        "up.bmp",
        "down.bmp",
        "left.bmp",
        "right.bmp"
    };
	// Loading flags
    bool allLoaded = true;
    // Load all images
	SDL_Surface* gImages[KEY_PRESS_SURFACE_TOTAL];
    int count = 0;
    while(allLoaded && count < KEY_PRESS_SURFACE_TOTAL){
        gImages[count] = loadSurface(filenames[count]);
        allLoaded = (gImages[count] != nullptr);
        count++;
    }

    // If all images loaded successfully
    if(allLoaded) {
        // Main loop
        SDL_Surface* gCurrentSurface = gImages[KEY_PRESS_SURFACE_DEFAULT];
        // The current event
        SDL_Event e;
        // Flag for quitting
        bool quit = false;
        while( quit == false ){
            // Remove all events from the queue
            while( SDL_PollEvent( &e ) ){
                // Here is where event processing goes
                if( e.type == SDL_QUIT ){
                    quit = true;
                } else if(e.type == SDL_KEYDOWN){
                    switch(e.key.keysym.sym){
                        case SDLK_UP:
                            gCurrentSurface = gImages[KEY_PRESS_SURFACE_UP];
                            break;
                        case SDLK_DOWN:
                            gCurrentSurface = gImages[KEY_PRESS_SURFACE_DOWN];
                            break;
                        case SDLK_LEFT:
                            gCurrentSurface = gImages[KEY_PRESS_SURFACE_LEFT];
                            break;
                        case SDLK_RIGHT:
                            gCurrentSurface = gImages[KEY_PRESS_SURFACE_RIGHT];
                            break;
                        default:
                            gCurrentSurface = gImages[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                    }
                }
                
                // Here is where building the image goes
                // Blit the image on each pass
                SDL_BlitSurface( gCurrentSurface, NULL, windowSurface, NULL );

                // Update the surface of the window to display the new image
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    // Clean up memory
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++){
        SDL_FreeSurface(gImages[i]);
        gImages[i] = nullptr;
    }
}

void SDLWindowWrapper::lesson5(){
        // Nominally prt of init()
	// Load splash image
	SDL_Surface* gImageStretch = nullptr;
    gImageStretch = loadSurface( "stretch.bmp" );
	if(gImageStretch){
        // Blit the image with the stretch
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = screenWidth;
        stretchRect.h = screenHeight;
        SDL_BlitScaled( gImageStretch, NULL, windowSurface, &stretchRect );

        // Update the surface of the window to display the new image
        SDL_UpdateWindowSurface(window);

        // Main loop
        // The current event
        SDL_Event e;
        // Flag for quitting
        bool quit = false;
        while( quit == false ){
            // Remove all events from the queue
            while( SDL_PollEvent( &e ) ){
                if( e.type == SDL_QUIT ){
                    quit = true;
                }
            }
        }
    }
    
    // Nominally part of close()
    // Deallocate surface
	SDL_FreeSurface( gImageStretch );
	gImageStretch = nullptr;
}

void SDLWindowWrapper::lesson6(){
    // Nominally part of init()
	// Load PNG
	SDL_Surface* gPNG = nullptr;
    gPNG = loadSurface( "loaded.png" );
    if(gPNG) {
        // Main loop
        //Apply the image
        SDL_BlitSurface( gPNG, NULL, windowSurface, NULL );
        
        //Update the surface
        SDL_UpdateWindowSurface(window);

        //Hack to get window to stay up
        SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
    }
    
    // Nominally part of close()
    // Deallocate surface
	SDL_FreeSurface( gPNG );
	gPNG = nullptr;
}

void SDLWindowWrapper::lesson7(){
    // TODO
}

void SDLWindowWrapper::lesson8(){
    // TODO
}

void SDLWindowWrapper::lesson9(){
    // TODO
}

void SDLWindowWrapper::lesson10(){
    // TODO
}

void SDLWindowWrapper::lesson11(){
    // TODO
}

void SDLWindowWrapper::lesson12(){
    // TODO
}

void SDLWindowWrapper::lesson13(){
    // TODO
}

//---------- UTILITIES ----------
SDL_Surface* SDLWindowWrapper::loadSurface(string path){
    // Optimized surface that matches the window surface format
    SDL_Surface* optimizedSurface = nullptr;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(!loadedSurface){
        fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        // Convert the loaded image to match the window surface format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, windowSurface->format, 0);
        if(!optimizedSurface){
            fprintf(stderr, "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }
    return optimizedSurface;
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
            // Initialize the SDL_image library
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)){
                fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                // TODO - exceptions?
                return false;
            } else {
                // Get the window surface
                windowSurface = SDL_GetWindowSurface(window);
            }
        }
    }
    return true;
}
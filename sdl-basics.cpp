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
        SDL_BlitSurface( gHelloWorld, NULL, screenSurface, NULL );
        
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
                SDL_BlitSurface( gHelloWorld, NULL, screenSurface, NULL );

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
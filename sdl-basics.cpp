#include <SDL2/SDL_image.h>

#include "sdl-basics.h"

//--------------------------------------------------------------------
//---------- SDLWindowWrapper ----------------------------------------
//--------------------------------------------------------------------
//---------- CONSTRUCTORS & DESTRUCTOR ----------
SDLWindowWrapper::SDLWindowWrapper() : screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), window(nullptr), renderer(nullptr), windowSurface(nullptr){
    init("SDL Window");
}

SDLWindowWrapper::SDLWindowWrapper(int width, int height, string title) : screenWidth(width), screenHeight(height), window(nullptr), renderer(nullptr), windowSurface(nullptr){
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

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
    // Nominally part of init()
    // Load splash image
    SDL_Texture* gTexture = nullptr;
    gTexture = loadTexture( "texture.png" );
    if(gTexture){
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
                
                // Clear screen
                SDL_RenderClear(renderer);

                // Render texture to screen
                SDL_RenderCopy(renderer, gTexture, NULL, NULL );

                // Update screen
                SDL_RenderPresent(renderer);
            }
        }
    }
    
    // Nominally part of close()
    // Deallocate surface
    SDL_DestroyTexture( gTexture );
    gTexture = nullptr;
}

void SDLWindowWrapper::lesson8(){
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
            
            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            // Draw a rectangle
            SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);        
            SDL_RenderFillRect(renderer, &fillRect);

            // Draw a 1 pixel outline of a rectangle
            SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);        
            SDL_RenderDrawRect(renderer, &outlineRect);

            // Draw blue horizontal line
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);        
            SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

            // Draw vertical line of black dots
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            for(int i = 0; i < SCREEN_HEIGHT; i += 4){
                SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
            }

            // Update screen
            SDL_RenderPresent(renderer);
        }
    }
}

void SDLWindowWrapper::lesson9(){
    // Nominally part of init()
    // Load splash image
    SDL_Texture* gTexture = nullptr;
    gTexture = loadTexture( "viewport.png" );
    if(gTexture){
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

                // Clear screen
                SDL_RenderClear(renderer);
                
                //Top left corner viewport
                SDL_Rect topLeftViewport;
                topLeftViewport.x = 0;
                topLeftViewport.y = 0;
                topLeftViewport.w = SCREEN_WIDTH / 2;
                topLeftViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(renderer, &topLeftViewport);
                
                //Render texture to screen
                SDL_RenderCopy(renderer, gTexture, NULL, NULL);
                
                //Top right viewport
                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH / 2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH / 2;
                topRightViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(renderer, &topRightViewport);
                
                //Render texture to screen
                SDL_RenderCopy(renderer, gTexture, NULL, NULL);

                //Bottom viewport
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = SCREEN_HEIGHT / 2;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(renderer, &bottomViewport);
                
                //Render texture to screen
                SDL_RenderCopy(renderer, gTexture, NULL, NULL);

                // Update screen
                SDL_RenderPresent(renderer);
            }
        }
    }
    
    // Nominally part of close()
    // Deallocate surface
    SDL_DestroyTexture( gTexture );
    gTexture = nullptr;
}

void SDLWindowWrapper::lesson10(){
    // Loading flag
    bool success = true;

    // Texture wrappers for images
    SDLTextureWrapper background;
    SDLTextureWrapper foo;

    // Load the images
    success = background.loadFromFile(renderer, "background.png");
    if(!success){
        return;
    }
    success = foo.loadFromFile(renderer, "foo.png");

    if(success){
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
                
                // Clear screen
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                // Render the two images
                background.render(renderer, 0, 0);
                foo.render(renderer, 240, 190);

                // Update screen
                SDL_RenderPresent(renderer);
            }
        }
    }

    // Texture data should automatically get cleaned up with the destructor
}

void SDLWindowWrapper::lesson11(){
    // Loading flag
    bool success = true;

    // Load the sprite sheet
    SDLTextureWrapper spriteSheet;

    // Load the images
    success = spriteSheet.loadFromFile(renderer, "dots.png");

    // If sucessfully loaded
    if(success){
        // Clipping rectangles for the sprite sheet
        SDL_Rect gSpriteClips[4];
        gSpriteClips[0] = {0, 0, 100, 100};
        gSpriteClips[1] = {100, 0, 100, 100};
        gSpriteClips[2] = {0, 100, 100, 100};
        gSpriteClips[3] = {100, 100, 100, 100};

        // The current event
        SDL_Event e;
        // Flag for quitting
        bool quit = false;

        // Main loop
        while( quit == false ){
            // Remove all events from the queue
            while( SDL_PollEvent( &e ) ){
                // Here is where event processing goes
                if( e.type == SDL_QUIT ){
                    quit = true;
                }
                
                // Clear screen
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                // Render the sprites in the corners
                spriteSheet.render(renderer, 0, 0, &gSpriteClips[0]);
                spriteSheet.render(renderer, screenWidth - gSpriteClips[1].w, 0, &gSpriteClips[1]);
                spriteSheet.render(renderer, 0, screenHeight - gSpriteClips[2].h, &gSpriteClips[2]);
                spriteSheet.render(renderer, screenWidth - gSpriteClips[1].w, screenHeight - gSpriteClips[2].h, &gSpriteClips[3]);

                // Update screen
                SDL_RenderPresent(renderer);
            }
        }
    }
}

void SDLWindowWrapper::lesson12(){
     // Loading flag
    bool success = true;

    // Load the sprite sheet
    SDLTextureWrapper colorMap;

    // Load the images
    success = colorMap.loadFromFile(renderer, "colors.png");

    // If sucessfully loaded
    if(success){
        // The current event
        SDL_Event e;
        // Flag for quitting
        bool quit = false;

        // Color modulation colors
        Uint8 r = 255;
        Uint8 g = 255;
        Uint8 b = 255;
        // Note: Uint8's will auto wrap, so 255 + 32 = 31

        // Main loop
        while( quit == false ){
            // Remove all events from the queue
            while( SDL_PollEvent( &e ) ){
                // Here is where event processing goes
                if( e.type == SDL_QUIT ){
                    quit = true;
                } else if(e.type == SDL_KEYDOWN){
                    switch(e.key.keysym.sym){
                        case SDLK_q:
                            r += 32;
                            break;
                        case SDLK_w:
                            g += 32;
                            break;
                        case SDLK_e:
                            b += 32;
                            break;
                        case SDLK_a:
                            r -= 32;
                            break;
                        case SDLK_s:
                            g -= 32;
                            break;
                        case SDLK_d:
                            b -= 32;
                            break;
                        default:
                            break;
                    }
                }
            }
                
            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            // Render
            colorMap.setColor(r, g, b);
            colorMap.render(renderer, 0, 0);

            // Update screen
            SDL_RenderPresent(renderer);
        }
    }
}

void SDLWindowWrapper::lesson13(){
    // TODO
}

void SDLWindowWrapper::lesson14(){
    // TODO
}

void SDLWindowWrapper::lesson15(){
    // TODO
}

void SDLWindowWrapper::lesson16(){
    // TODO
}

void SDLWindowWrapper::lesson17(){
    // TODO
}

void SDLWindowWrapper::lesson18(){
    // TODO
}

void SDLWindowWrapper::lesson19(){
    // TODO
}

void SDLWindowWrapper::lesson20(){
    // TODO
}

void SDLWindowWrapper::lesson21(){
    // TODO
}

void SDLWindowWrapper::lesson22(){
    // TODO
}

void SDLWindowWrapper::lesson23(){
    // TODO
}

void SDLWindowWrapper::lesson24(){
    // TODO
}

void SDLWindowWrapper::lesson25(){
    // TODO
}

void SDLWindowWrapper::lesson26(){
    // TODO
}

void SDLWindowWrapper::lesson27(){
    // TODO
}

void SDLWindowWrapper::lesson28(){
    // TODO
}

void SDLWindowWrapper::lesson29(){
    // TODO
}

void SDLWindowWrapper::lesson30(){
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

SDL_Texture* SDLWindowWrapper::loadTexture(string path){
    // Texture to load the image into
    SDL_Texture* newTexture = nullptr;
    // Load image at specified path as a surface
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(!loadedSurface){
        fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        // Convert the loaded image to into a texture
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(!newTexture){
            fprintf(stderr, "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
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
            //Create renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if(!renderer)
            {
                fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                return false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

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
    }
    return true;
}

//--------------------------------------------------------------------
//---------- SDLTextureWrapper ---------------------------------------
//--------------------------------------------------------------------
//---------- CONSTRUCTORS & DESTRUCTOR ----------
SDLTextureWrapper::SDLTextureWrapper() : texture(nullptr), width(-1), height(-1){}

SDLTextureWrapper::SDLTextureWrapper(const SDLTextureWrapper& other) : texture(nullptr), width(-1), height(-1){
    // TODO
}

SDLTextureWrapper& SDLTextureWrapper::operator=(const SDLTextureWrapper& other) {
    // TODO
    return *this;
}

SDLTextureWrapper::~SDLTextureWrapper(){
    free();
}

//---------- UTILITIES ----------
bool SDLTextureWrapper::loadFromFile(SDL_Renderer* renderer, string path){
    // Remove anything that has already been loaded in
    free();

    // Flag for loading success
    bool success = true;

    // Load image at specified path as a surface
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(!loadedSurface){
        fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
        // TODO - exception handling
        success = false;
    } else {
        // Set the color key
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // Convert the loaded image to into a texture
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(!texture){
            fprintf(stderr, "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            // TODO - exception handling
            success = false;
        } else {
            // Get the image dimensions
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }

    return success;
}

void SDLTextureWrapper::free(){
    if(texture){
        // Destroy the texture
        SDL_DestroyTexture(texture);
        texture = nullptr;

        // Set the width and the height to nonsense values
        width = -1;
        height = -1;
    }
}

void SDLTextureWrapper::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip){
    // Render the image into the correct location
    SDL_Rect renderQuad = {x, y, width, height};

    // Use the clipping rectangle to extract the sprite
    if(clip){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to the screen
    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

void SDLTextureWrapper::setColor(Uint8 red, Uint8 green, Uint8 blue){
    //Modulate texture
    SDL_SetTextureColorMod(texture, red, green, blue);
}

//---------- ACCESSORS ----------
int SDLTextureWrapper::getWidth(){
    return height;
}

int SDLTextureWrapper::getHeight(){
    return width;
}
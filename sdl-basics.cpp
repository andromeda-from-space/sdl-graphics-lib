#include <SDL2/SDL_image.h>

#include "sdl-basics.h"

//--------------------------------------------------------------------
//---------- SDLWindowWrapper ----------------------------------------
//--------------------------------------------------------------------
//---------- CONSTRUCTORS & DESTRUCTOR ----------
SDLWindowWrapper::SDLWindowWrapper() : screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), window(nullptr), renderer(nullptr), windowSurface(nullptr), useTTF(true) {
    init("SDL Window");
}

SDLWindowWrapper::SDLWindowWrapper(int width, int height, std::string title, bool useTTF) : screenWidth(width), screenHeight(height), window(nullptr), renderer(nullptr), windowSurface(nullptr), useTTF(useTTF){
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
    if(useTTF){
        TTF_Quit();
    }
}

//---------- TUTORIAL CODE ----------
void SDLWindowWrapper::lesson1(){
    //Fill the surface white
    SDL_FillRect( windowSurface, nullptr, SDL_MapRGB( windowSurface->format, 0xFF, 0xFF, 0xFF ) );
    
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
        SDL_BlitSurface( gHelloWorld, nullptr, windowSurface, nullptr );
        
        //Update the surface
        SDL_UpdateWindowSurface(window);

        //Hack to get window to stay up
        SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
    }
    
    // Nominally part of close()
    // Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = nullptr;
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
                SDL_BlitSurface( gHelloWorld, nullptr, windowSurface, nullptr );

                // Update the surface of the window to display the new image
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    
    // Nominally part of close()
    // Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = nullptr;
}

void SDLWindowWrapper::lesson4(){
    // Load the data
    // Nominally prt of init()
    // Array of file names for loading
    std::string filenames[] = {
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
                SDL_BlitSurface( gCurrentSurface, nullptr, windowSurface, nullptr );

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
        SDL_BlitScaled( gImageStretch, nullptr, windowSurface, &stretchRect );

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
        SDL_BlitSurface( gPNG, nullptr, windowSurface, nullptr );
        
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
                SDL_RenderCopy(renderer, gTexture, nullptr, nullptr );

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
                SDL_RenderCopy(renderer, gTexture, nullptr, nullptr);
                
                //Top right viewport
                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH / 2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH / 2;
                topRightViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(renderer, &topRightViewport);
                
                //Render texture to screen
                SDL_RenderCopy(renderer, gTexture, nullptr, nullptr);

                //Bottom viewport
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = SCREEN_HEIGHT / 2;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(renderer, &bottomViewport);
                
                //Render texture to screen
                SDL_RenderCopy(renderer, gTexture, nullptr, nullptr);

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
    // Loading flag
    bool success = true;

    // Load the sprite sheet
    SDLTextureWrapper fadein;
    SDLTextureWrapper fadeout;

    // Load the images
    success = fadein.loadFromFile(renderer, "fadein.png");
    if(success){
        success = fadeout.loadFromFile(renderer, "fadeout.png");
    }

    // If sucessfully loaded
    if(success){
        // Set the blend mode on the texture being faded out
        fadeout.setBlendMode( SDL_BLENDMODE_BLEND );

        // The current event
        SDL_Event e;
        // Flag for quitting
        bool quit = false;

        // Color modulation colors
        Uint8 alpha = 255;

        // Main loop
        while( quit == false ){
            // Remove all events from the queue
            while( SDL_PollEvent( &e ) ){
                // Here is where event processing goes
                if( e.type == SDL_QUIT ){
                    quit = true;
                } else if(e.type == SDL_KEYDOWN){
                    switch(e.key.keysym.sym){
                        case SDLK_w:
                            if(alpha + 32 > 255){
                                alpha = 255;
                            } else {
                                alpha += 32;
                            }
                            break;
                        case SDLK_s:
                            if(alpha - 32 < 0){
                                alpha = 0;
                            } else {
                                alpha -= 32;
                            }
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
            fadein.render(renderer, 0, 0);
            fadeout.setAlpha(alpha);
            fadeout.render(renderer, 0, 0);

            // Update screen
            SDL_RenderPresent(renderer);
        }
    }
}

void SDLWindowWrapper::lesson14(){
    // Loading flag
    bool success = true;

    // Load the sprite sheet
    SDLTextureWrapper gSpriteSheet;

    // Load the images
    success = gSpriteSheet.loadFromFile(renderer, "foo2.png");

    // If sucessfully loaded
    if(success){
        // Create the clips for the sprite sheet
        int frameCount = 4;
        SDL_Rect gSpriteClips[frameCount];

        //Set sprite clips
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w =  64;
        gSpriteClips[ 0 ].h = 205;

        gSpriteClips[ 1 ].x =  64;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w =  64;
        gSpriteClips[ 1 ].h = 205;
        
        gSpriteClips[ 2 ].x = 128;
        gSpriteClips[ 2 ].y =   0;
        gSpriteClips[ 2 ].w =  64;
        gSpriteClips[ 2 ].h = 205;

        gSpriteClips[ 3 ].x = 192;
        gSpriteClips[ 3 ].y =   0;
        gSpriteClips[ 3 ].w =  64;
        gSpriteClips[ 3 ].h = 205;

        // The current event
        SDL_Event e;
        // Flag for quitting
        bool quit = false;

        // Main loop
        int currFrame = 0;
        while( quit == false ){
            // Remove all events from the queue
            while( SDL_PollEvent( &e ) ){
                // Here is where event processing goes
                if( e.type == SDL_QUIT ){
                    quit = true;
                }
            }
                
            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            // Render
            gSpriteSheet.render(renderer, 0, 0, &gSpriteClips[currFrame]);

            // Update screen
            SDL_RenderPresent(renderer);
            
            // Increment the animation
            currFrame++;
            if(currFrame == frameCount){
                currFrame = 0;
            }
            // Needs a timer so it doesn't referesh so quickly
        }
    }
}

void SDLWindowWrapper::lesson15(){
        // Loading flag
    bool success = true;

    // Load the sprite sheet
    SDLTextureWrapper arrow;

    // Load the images
    success = arrow.loadFromFile(renderer, "arrow.png");

    // If sucessfully loaded
    if(success){
        //Angle of rotation
        double degrees = 0;

        //Flip type
        SDL_RendererFlip flipType = SDL_FLIP_NONE;

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
                } else if(e.type == SDL_KEYDOWN){
                    switch(e.key.keysym.sym){
                        case SDLK_a:
                            degrees -= 60;
                            break;
                            
                        case SDLK_d:
                            degrees += 60;
                            break;

                        case SDLK_q:
                            flipType = SDL_FLIP_HORIZONTAL;
                            break;

                        case SDLK_w:
                            flipType = SDL_FLIP_NONE;
                            break;

                        case SDLK_e:
                            flipType = SDL_FLIP_VERTICAL;
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
            arrow.render(renderer, (screenHeight - arrow.getWidth()) / 2, (screenHeight - arrow.getHeight()) / 2, nullptr, degrees, nullptr, flipType);
            // Note the center is the center of rotation, so if you choose something other than nullptr

            // Update screen
            SDL_RenderPresent(renderer);
        }
    }
}

void SDLWindowWrapper::lesson16(){
        // Loading flag
    bool success = true;

    // Texture wrappers for images
    SDLTextBox textBox;

    // Load the images
    success = textBox.loadFromFile("lazy.ttf", 28);

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
                textBox.render("Hello world!", renderer, 0, 0);

                // Update screen
                SDL_RenderPresent(renderer);
            }
        }
    }
}

void SDLWindowWrapper::lesson17(){
    // Make the button sprite clips
    SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];
    for(int i = 0; i < BUTTON_SPRITE_TOTAL; i++){
        spriteClips[i].x = 0;
        spriteClips[i].y = i * 200;
        spriteClips[i].w = BUTTON_WIDTH;
        spriteClips[i].h = BUTTON_HEIGHT;
    }

    // Make the button
    SDLButton theButton = SDLButton(renderer, "button.png", spriteClips, BUTTON_SPRITE_TOTAL);

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
            } else{
                theButton.handleEvent(&e);
            }
        }
            
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Render
        theButton.render(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
    }
    
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
SDL_Surface* SDLWindowWrapper::loadSurface(std::string path){
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

SDL_Texture* SDLWindowWrapper::loadTexture(std::string path){
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

void SDLWindowWrapper::saveImg(std::string path){
    // Get the window surface
    SDL_Surface* currSurface = SDL_GetWindowSurface(window);
    // Save
    IMG_SavePNG(currSurface, path.c_str());
}

//---------- PRIVATE UTILITIES ----------
bool SDLWindowWrapper::init(std::string title){
    // TODO - Make code more compact - early returns make else blocks unnecessary
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        // TODO - exceptions?
        return false;
    } else {
        // Create the window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if(!window){
            fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
            // TODO - exceptions?
            return false;
        } else {
            //Create renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
                    if(useTTF && TTF_Init() == -1){
                        fprintf(stderr, "SDL_TTF could not initialize ! TTF_Error: %s\n", TTF_GetError());
                        // TODO - exceptions?
                        return false;
                    } else {
                        // Get the window surface
                        windowSurface = SDL_GetWindowSurface(window);
                    }
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
bool SDLTextureWrapper::loadFromFile(SDL_Renderer* renderer, std::string path){
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

void SDLTextureWrapper::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    // Render the image into the correct location
    SDL_Rect renderQuad = {x, y, width, height};

    // Use the clipping rectangle to extract the sprite
    if(clip){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to the screen
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip );
}

void SDLTextureWrapper::setColor(Uint8 red, Uint8 green, Uint8 blue){
    SDL_SetTextureColorMod(texture, red, green, blue);
}

void SDLTextureWrapper::setAlpha(Uint8 alpha){
    SDL_SetTextureAlphaMod(texture, alpha);
}

void SDLTextureWrapper::setBlendMode(SDL_BlendMode blending){
    SDL_SetTextureBlendMode(texture, blending);
}

//---------- ACCESSORS ----------
int SDLTextureWrapper::getWidth(){
    return height;
}

int SDLTextureWrapper::getHeight(){
    return width;
}

//--------------------------------------------------------------------
//---------- SDLTextBox ----------------------------------------------
//--------------------------------------------------------------------
//---------- CONSTRUCTORS & DESTRUCTOR ----------
SDLTextBox::SDLTextBox() : font(nullptr), backgroundColor({255, 255, 255, 0}), textColor({0, 0, 0, 255}) {}

SDLTextBox::SDLTextBox(const SDLTextureWrapper& other) : font(nullptr), backgroundColor({255, 255, 255, 0}), textColor({0, 0, 0, 255}) {
    // TODO
}

SDLTextBox& SDLTextBox::operator=(const SDLTextureWrapper& other) {
    // TODO
    return *this;
}

SDLTextBox::~SDLTextBox() {
    free();
}

//---------- UTILITIES ----------
bool SDLTextBox::loadFromFile(std::string path, int size){
    // Free any previously loaded fonts
    free();

    // Loading success flag
    bool success = true;

    // Open the font
    font = TTF_OpenFont( path.c_str(), size );
    if( font == nullptr )
    {
        fprintf(stderr, "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        // TODO - exceptions?
        success = false;
    }
    return success;
}

void SDLTextBox::free(){
    // Delete the font
    TTF_CloseFont(font);
    font = nullptr;
}

void SDLTextBox::render(std::string text, SDL_Renderer* renderer, int x, int y) {
    // Create a surface from the text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if(!textSurface){
        fprintf(stderr, "Unable to render text to surface! SDL_TTF Error: %s\n", TTF_GetError());
    } else {
        // Create the texture
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(!textTexture){
            fprintf(stderr, "Unable to render texture from surface! SDL Error: %s\n", SDL_GetError());
        } else {
            // The rendering quad 
            SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};

            // Create background to text box
            SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.b, backgroundColor.g, backgroundColor.a);        
            SDL_RenderFillRect(renderer, &renderQuad);

            // Render the texture
            SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

            // Free the texture
            SDL_DestroyTexture(textTexture);
        }
        // Free the surface
        SDL_FreeSurface(textSurface);
    }
}

//--------------------------------------------------------------------
//---------- SDLTextBox ----------------------------------------------
//--------------------------------------------------------------------
//---------- CONSTRUCTORS & DESTRUCTOR ----------
SDLButton::SDLButton() {
    // TODO
}

SDLButton::SDLButton(SDL_Renderer* renderer, std::string spriteSheet, SDL_Rect* spriteClips, int numSprites) : position({0, 0}), currentSprite(BUTTON_SPRITE_MOUSE_OUT), 
buttonSpriteSheet(nullptr), spriteClips(spriteClips), numSprites(numSprites) {
    // Load the sprite sheet
    buttonSpriteSheet = new SDLTextureWrapper();
    loadFromFile(renderer, spriteSheet);

    // Copy the sprite clips
    this->spriteClips = new SDL_Rect[numSprites];
    for(int i = 0; i < numSprites; i++){
        this->spriteClips[i] = spriteClips[i];
    }
}

SDLButton::SDLButton(const SDLButton& other){
    // TODO
}

SDLButton& SDLButton::operator=(const SDLButton& other){
    // TODO
    return *this;
}

SDLButton::~SDLButton(){
    // Clean up the sprite sheet
    if(buttonSpriteSheet){
        delete(buttonSpriteSheet);
        buttonSpriteSheet = nullptr;
    }

    // Clean up the spriteClips
    if(spriteClips){
        delete[](spriteClips);
        spriteClips = nullptr;
    }
}

//---------- UTILITIES ----------
bool SDLButton::loadFromFile(SDL_Renderer* renderer, std::string path){
    return buttonSpriteSheet->loadFromFile(renderer, path);
}

void SDLButton::setPosition( int x, int y ){
    position.x = x;
    position.y = y;
}

void SDLButton::handleEvent( SDL_Event* e ){
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if( x < position.x )
        {
            inside = false;
        }
        // Mouse is right of the button
        else if( x > position.x + BUTTON_WIDTH )
        {
            inside = false;
        }
        // Mouse above the button
        else if( y < position.y )
        {
            inside = false;
        }
        // Mouse below the button
        else if( y > position.y + BUTTON_HEIGHT )
        {
            inside = false;
        }

        // TODO - fix constants
        // TODO - use short circuit ORs

        // Mouse is outside button
        if(!inside)
        {
            currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                    currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
            
                case SDL_MOUSEBUTTONDOWN:
                    currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                
                case SDL_MOUSEBUTTONUP:
                    currentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;

                default:
                    break;
            }
        }
    }
}

void SDLButton::render(SDL_Renderer* renderer){
    buttonSpriteSheet->render(renderer, position.x, position.y, &spriteClips[currentSprite]);
}
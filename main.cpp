/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "Personaje.h"

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *upMessage = NULL;
SDL_Surface *downMessage = NULL;
SDL_Surface *leftMessage = NULL;
SDL_Surface *rightMessage = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename )
{
    return IMG_Load( filename.c_str() );
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Press an Arrow Key", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "background.png" );

    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 72 );

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( upMessage );
    SDL_FreeSurface( downMessage );
    SDL_FreeSurface( leftMessage );
    SDL_FreeSurface( rightMessage );

    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Generate the message surfaces
    upMessage = TTF_RenderText_Solid( font, "Up was pressed.", textColor );
    downMessage = TTF_RenderText_Solid( font, "Down was pressed.", textColor );
    leftMessage = TTF_RenderText_Solid( font, "Left was pressed", textColor );
    rightMessage = TTF_RenderText_Solid( font, "Right was pressed", textColor );

    //Apply the background
    apply_surface( 0, 0, background, screen );

    SDL_Surface* entrada = load_image("tablero/entrada.png");
    SDL_Surface* salida = load_image("tablero/salida.png");
    SDL_Surface* llave = load_image("tablero/llave.png");
    SDL_Surface* pasillo = load_image("tablero/pasillo.png");
    SDL_Surface* muro = load_image("tablero/muro.png");
    SDL_Surface* cursor = load_image("tablero/cursor.png");

    char tablero[5][5]={{' ','#',' ',' ',' '},
                        {'E','#',' ','#','S'},
                        {' ','#',' ','#',' '},
                        {' ','#',' ','#','#'},
                        {' ',' ',' ',' ','L'}};

    SDL_Surface* personaje_surface = load_image("personaje.png");
    Personaje personaje(2,3);

    //While the user hasn't quit
    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP: message = upMessage; break;
                    case SDLK_DOWN: message = downMessage; break;
                    case SDLK_LEFT: message = leftMessage; break;
                    case SDLK_RIGHT: message = rightMessage; break;
                }
            }

            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //If a message needs to be displayed
        if( message != NULL )
        {
            //Apply the background to the screen
            apply_surface( 0, 0, background, screen );

            //Apply the message centered on the screen
            apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );

            //Null the surface pointer
            message = NULL;
        }

        for(int x=0;x<5;x++)
            for(int y=0;y<5;y++)
            {
                if(tablero[y][x]=='E')
                    apply_surface(x*75,y*75,entrada,screen);
                if(tablero[y][x]=='S')
                    apply_surface(x*75,y*75,salida,screen);
                if(tablero[y][x]=='L')
                    apply_surface(x*75,y*75,llave,screen);
                if(tablero[y][x]==' ')
                    apply_surface(x*75,y*75,pasillo,screen);
                if(tablero[y][x]=='#')
                    apply_surface(x*75,y*75,muro,screen);
            }

        apply_surface(personaje.x*75,personaje.y*75,personaje_surface,screen);

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }

    //Clean up
    clean_up();

    return 0;
}

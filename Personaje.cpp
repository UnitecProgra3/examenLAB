#include "Personaje.h"

Personaje::Personaje(int x,int y,SDL_Surface*imagen)
{
    this->x=x;
    this->y=y;
    this->imagen=imagen;
    this->sprites.push_back(IMG_Load("ThorO.png"));
    this->sprites.push_back(IMG_Load("ThorO1.png"));
    this->sprites.push_back(IMG_Load("ThorO2.png"));
    this->sprites.push_back(IMG_Load("ThorO3.png"));
    cuadro_actual=0;
}

void Personaje::dibujar(SDL_Surface*screen)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x*75;
    offset.y = y*75;

    //Blit
    SDL_BlitSurface(imagen, NULL, screen, &offset );
}

void Personaje::animacion(SDL_Surface*screen)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x*75;
    offset.y = y*75;
    //Blit
    SDL_BlitSurface( this->sprites[cuadro_actual], NULL, screen, &offset );
    iter++;
    if(iter==4)
    {
        cuadro_actual++;
        if(cuadro_actual>=4)
        {
            cuadro_actual=0;

        }

        iter=0;

    }

}


Personaje::~Personaje()
{
    //dtor
}

#include "CAP.h"

CAP::CAP(int x,int y,SDL_Surface*imagen)
{
    this->x=x;
    this->y=y;
    this->imagen=imagen;
    this->sprites.push_back(IMG_Load("CaO.png"));
    this->sprites.push_back(IMG_Load("CaO1.png"));
    this->sprites.push_back(IMG_Load("CaO2.png"));
    this->sprites.push_back(IMG_Load("CaO3.png"));
    cuadro_actual=0;
}

void CAP::dibujar(SDL_Surface*screen)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x*75;
    offset.y = y*75;

    //Blit
    SDL_BlitSurface(imagen, NULL, screen, &offset );
}

void CAP::animacion(SDL_Surface*screen)
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




CAP::~CAP()
{
    //dtor
}

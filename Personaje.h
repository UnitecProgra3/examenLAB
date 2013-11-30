#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Personaje
{
    public:
        int x,y, cuadro_actual,iter=0;
        SDL_Surface*imagen;
        std::vector <SDL_Surface*> sprites;
        Personaje(int x,int y,SDL_Surface*personaje);
        void dibujar(SDL_Surface *screen);
        void animacion(SDL_Surface *screen);
        virtual ~Personaje();
    protected:
    private:
};

#endif // PERSONAJE_H

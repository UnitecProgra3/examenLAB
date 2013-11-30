#ifndef CAP_H
#define CAP_H
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class CAP
{
    public:
        int x,y, cuadro_actual,iter=0;
        SDL_Surface*imagen;
        std::vector <SDL_Surface*> sprites;
        CAP(int x,int y,SDL_Surface*personaje);
        void dibujar(SDL_Surface *screen);
        void animacion(SDL_Surface *screen);
        virtual ~CAP();
    protected:
    private:
};

#endif // CAP_H

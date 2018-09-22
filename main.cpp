#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#define nbcare 3
#define c 400


SDL_Surface *affichage;
void echangerEntiers(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

void setPixel(int x, int y, Uint8 coul)
{
  *((Uint32*)(affichage->pixels) + x + y * affichage->w) = coul;
}

void setPixelVerif(int x, int y, Uint32 coul)
{
  if (x >= 0 && x < affichage->w &&
      y >= 0 && y < affichage->h)
    setPixel(x, y, coul);
}


void lines(int x1, int y1, int x2, int y2, Uint32 coul)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */

    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;

    setPixelVerif(x, y, coul);

    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(x, y, coul);
    }

  } else {
    /* parcours par l'axe horizontal */

    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;

    setPixelVerif(x, y, coul);

    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(x, y, coul);
    }
  }
  SDL_Delay(1000);
    SDL_Flip(affichage);
}


void Dessin(int a,int o,int cote,int n)
{
    lines(a,o,a+cote/2,o,SDL_MapRGB(affichage->format, 13,43,76));
    lines(a+cote/2,o,a+cote/4,o+cote/4,SDL_MapRGB(affichage->format, 255,255,255));
    if(n>1)
    {
        Dessin(a+cote/4,o+cote/4,cote/2,n-1);
    }
       lines(a+cote/4,o+cote/4,a,o+cote/2,SDL_MapRGB(affichage->format, 255,255,255));
       lines(a,o+cote/2,a+cote/2,o+cote,SDL_MapRGB(affichage->format, 255,255,255));
       lines(a+cote/2,o+cote,a+cote,o+cote/2,SDL_MapRGB(affichage->format, 255,255,255));
       lines(a+cote,o+cote/2,a+cote/2,o,SDL_MapRGB(affichage->format, 255,255,255));
       lines(a+cote/2,o,a+cote,o,SDL_MapRGB(affichage->format, 13,43,76));
       lines(a+cote,o,a+cote,o+cote,SDL_MapRGB(affichage->format, 13,43,76));
       lines(a+cote,o+cote,a,o+cote,SDL_MapRGB(affichage->format, 13,43,76));
       lines(a,o+cote,a,o,SDL_MapRGB(affichage->format, 13,43,76));

}


void initSDL(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  atexit(SDL_Quit);
  affichage = SDL_SetVideoMode(600, 600, 32, SDL_SWSURFACE);

  if (affichage == NULL) {
    fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

      SDL_WM_SetCaption("Dessin en abymes", NULL);

}



void pause()
{
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
        }
    }
}


int main(int argc, char *argv[])
{
    int a=100;
    int o=100;
    initSDL();
   // SDL_Init(SDL_INIT_VIDEO);
   // SDL_FillRect(affichage, NULL, SDL_MapRGB(affichage->format, 0,0,0));
    Dessin(a,o,c,nbcare);
    SDL_Flip(affichage);
    pause();
    SDL_FreeSurface(affichage);
    SDL_Quit();
    return EXIT_SUCCESS;

}



#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 600

#define COLOUR_WHITE 0xffffffff

typedef struct
{
	double x, y, radius;
} Circle;

void FillCircle(SDL_Surface* surf, struct Circle circle)
{
	// calc distance between a point and the centre of the circle, fill all pixels withint that range. Limit checking to pixels within the circles width/height.
	// left/right sides = x +- radius
	// top/bottom sides = y +- radius
	
	float middle = surf->w / 2.0;
	for (int i = 0; i < surf->w ** 2; i++) {
		// for each pixel, check distance, draw in all four quadrants, maybe 8 if I can figure it out
	}
}

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Ray Tracer",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WINDOW_WIDTH, WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);
  if (!window) {
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

	SDL_Surface surf = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
	if (!surf) {
		fprintf(stderr, "Surface failed: %s\n", SDL_GetError());
	}
	SDL_FillRect(surf, NULL, SDL_MapRGBA(surf->format, 0, 0, 0, 0));

	struct Circle circle = {400.0, 400.0, 100.0};
	FillCircle(surf, circle);

	SDL_Texture *sphere = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
      else if (event.type == SDL_KEYDOWN &&
        event.key.keysym.sym == SDLK_ESCAPE)
        running = false;
      }

      SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
      SDL_RenderClear(renderer);

			FillCircle(surface, COLOUR_WHITE);
				
      SDL_RenderPresent(renderer);
  }

	SDL_DestroyTexture(sprite);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

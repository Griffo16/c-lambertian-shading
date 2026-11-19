#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define PI 3.141592

#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 600

#define COLOUR_WHITE 0xffffffff
#define COLOUR_BLACK 0xff000000

typedef struct
{
	double x, y, radius;
} Circle;

typedef struct
{
	double x, y;
} Vec2;

typedef struct
{
	double x, y, z;
} Vec3;

// for every pixel:
// - calculate angle between normal and light ray
// - calculate light intensity
// - calculate final colour

static void VecSub(Vec3* a, Vec3* b) { a->x -= b->x; a->y -= b->y; a->z -= b->z; }
static void VecAdd(Vec3* a, Vec3* b) { a->x += b->x; a->y += b->y; a->z += b->z; }
static double VecDotProd(Vec3* a, Vec3* b) { return a->x*b->x + a->y*b->y + a->z*b->z; }

void ConvToUnitVec(Vec3* a) {
	double mag = sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
	a->x /= mag;
	a->y /= mag;
	a->z /= mag;
}

double CalcNormalAngle(Circle* circle, Vec3* point) {
	double dist_from_centre_squared = pow(circle->x - point->x, 2) + pow(circle->y - point->y,2); // adj in elev calculation
	double dist_from_centre = sqrt(dist_from_centre_squared);
	double point_elev = sqrt(pow(circle->radius, 2) - dist_from_centre_squared);
	point->z = point_elev;
	double cos_normal_angle = (dist_from_centre_squared + pow(circle->radius, 2) - pow(point_elev, 2)) / (2 * dist_from_centre * circle->radius);
	return acos(cos_normal_angle);
}

//double CalcLightIntensity(Vec3* point, Vec3* normalVec, Vec3* lightPos) {
	// calculate the angle the light would hit the surface
	// use light intensity formula
//}

Uint32 LightPoint(Circle* circle, Vec3* point, Vec3* lightSrc) {
	// full pipeline function, sets final colour value, holds values
	// 1. Create circle to point normal unit vec
	double normalAng = CalcNormalAngle(circle, point); // point now has an elevation
	Vec3 normal = *point;
	Vec3 radiusVec = (Vec3){circle->x,circle->y,0};
	VecSub(&normal, &radiusVec);
	ConvToUnitVec(&normal);
	// 2. Create light to point unit vec
	Vec3 ray = *lightSrc;
	VecSub(&ray, point);
	ConvToUnitVec(&ray);

	// 3. Calc light intensity (using function)
	double I = fmax(0, VecDotProd(&normal, &ray));

	// 4. determine final pixel colour (idk how to do this yet)
	Uint8 v = (Uint8)(255 * I + 0.5);
	if (point->x == 450 && point->y == 300) {
		//printf("x: %f, y: %f, z: %f\n", point->x, point->y, point->z);
	}

	return (0xff000000u | (Uint32)(v << 16) | (Uint32)(v << 8) | v);
}

void FillCircle(SDL_Surface* surf, Circle* circle, Vec3* lightSrc)
{
	double radius_squared = pow(circle->radius, 2);
	for (double y=circle->y - circle->radius; y<=circle->y + circle->radius; y++) {
		for (double x=circle->x - circle->radius; x<=circle->x + circle->radius; x++) {
			double dist_squared = pow(x - circle->x, 2) + pow(y - circle->y, 2);
			if (dist_squared <= radius_squared) {
				SDL_Rect pixel = (SDL_Rect){x,y,1,1};
				Vec3 point = (Vec3){x, y, 0};
				SDL_FillRect(surf, &pixel, LightPoint(circle, &point, lightSrc));
			}
		}
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

	SDL_Surface* surf = SDL_GetWindowSurface(window);
	if (!surf) {
		fprintf(stderr, "Surface failed: %s\n", SDL_GetError());
	}

	Circle circle = {450.0, 300.0, 100.0};
	Vec3 lightSrc = {450, 450, 300};

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
      else if (event.type == SDL_KEYDOWN &&
        event.key.keysym.sym == SDLK_ESCAPE)
        running = false;

			if (event.type == SDL_MOUSEMOTION && event.motion.state == SDL_BUTTON_LMASK) {
				//printf("%d\n", event.motion.state);
				lightSrc.x = event.motion.x;
				lightSrc.y = event.motion.y;
			}

			if (event.type == SDL_MOUSEWHEEL) {
				lightSrc.z -= event.wheel.y * 10;
				printf("light height: %.0f\n", lightSrc.z);
			}
    }

		SDL_FillRect(surf, NULL, COLOUR_BLACK);

		FillCircle(surf, &circle, &lightSrc);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>
#include <stdio.h>
#include <SDL2_gfxPrimitives.h>
#include "Vector.h"
#include "const.h"
#include "graphics.h"
#include "Particle.h"
#include "perlin.h"

int main() {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int quit = 0;
    SDL_Event e;

    int i = 0, y = 0, x = 0;
    float inc = 0.05;
    float yoff = 0, xoff = 0, zoff = 0;

	window = initVideo("Vectors");
	if(window == NULL) printf("Failed to initalize\n");
	else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			printf("Renderer could not be created ! SDL_Error: %s\n", SDL_GetError());
		} else {

            FPSmanager fps;
            SDL_initFramerate(&fps);
            SDL_setFramerate(&fps, 60);

            Vector* flowField[COLS*ROWS];

            Particle* particles[PARTSNB];
            i = 0;
            while(i < PARTSNB) {
                particles[i] = particle_create();
                ++i;
            }


            while(!quit){

                while(SDL_PollEvent(&e) !=0) {
                    if(e.type == SDL_QUIT) {
                        quit = 1;
                    }
                }


                SDL_SetRenderDrawColor(renderer, 10, 10, 10, 0);
                SDL_RenderClear(renderer);

                yoff = 0;
                y = 0;
                while(y < ROWS){
                    xoff = 0;
                    x = 0;
                    while(x < COLS) {
                        int idx = x + y * COLS;
                        float angle = octavePerlin(xoff,yoff,zoff,4,0.8) * 2*M_PI * 4;
                        Vector* v = vector_fromAngle(angle);
                        float mag = vector_getMag(v);
                        thickLineRGBA(renderer, x*SCALE, y*SCALE, x*SCALE + v->x*SCALE/2, y*SCALE + v->y*SCALE/2, 1,255,255,255,80);
                        vector_setMag(v,0.2);
                        flowField[idx] = v;

                        xoff += inc;
                        ++x;
                    }
                    yoff += inc;
                    ++y;
                }
                zoff += 0.005;
                zoff;
                i = 0;
                while(i < PARTSNB) {
                    particle_follow(particles[i], flowField);
                    particle_update(particles[i]);
                    particle_show(particles[i], renderer);
                    ++i;
                }


				SDL_RenderPresent(renderer);
                SDL_framerateDelay(&fps);
            }
            i = 0;
            while(i < PARTSNB) {
                particle_destroy(particles[i]);
                ++i;
            }
            i = 0;
            while(i < COLS * ROWS) {
                free(flowField[i]);
                flowField[i] = NULL;
                ++i;
            }
		}
	}
	closeVideo(renderer, window);
	return 0;
}

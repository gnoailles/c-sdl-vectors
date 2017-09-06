#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>
#include <stdio.h>
#include <SDL2_gfxPrimitives.h>
#include "Vector.h"
#include "const.h"
#include "graphics.h"
#include "Particle.h"
#include "perlin.h"
#include "flowField.h"

int main() {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int quit = 0;
    SDL_Event e;

    int i = 0;
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

            flowField_init(flowField, COLS*ROWS,particles,PARTSNB);


            while(!quit){

                while(SDL_PollEvent(&e) !=0) {
                    if(e.type == SDL_QUIT) {
                        quit = 1;
                    }
                }


                SDL_SetRenderDrawColor(renderer, 10, 10, 10, 0);
                SDL_RenderClear(renderer);

                flowField_update(flowField,particles,renderer,inc,&xoff,&yoff,&zoff);



				SDL_RenderPresent(renderer);
                SDL_framerateDelay(&fps);
            }

            flowField_destroy(flowField,particles);

		}
	}
	closeVideo(renderer, window);
	return 0;
}

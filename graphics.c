#include <SDL2/SDL.h>
#include <stdio.h>
#include "const.h"
#include "graphics.h"

SDL_Window* initVideo(char const * title) {
	SDL_Window* win = NULL;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize ! SDL_Error: %s\n", SDL_GetError() );
		return NULL;
	} else {
		win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if(win == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			return NULL;
		} else {
			return win;
		}
	}
}

void closeVideo(SDL_Renderer* rend, SDL_Window* win) {
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	rend = NULL;
	win = NULL;
	SDL_Quit();
}

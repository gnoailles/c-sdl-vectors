#ifndef VECTOR_SDL_FLOWFIELD_H
#define VECTOR_SDL_FLOWFIELD_H

#include <SDL_system.h>
#include "Vector.h"
#include "Particle.h"

void flowField_init(Vector** flowField,int size,Particle** particles, int partsNb);
void flowField_update(Vector** flowField, Particle** particles, SDL_Renderer* rend, float inc, float* xoff, float* yoff, float* zoff);
void flowField_destroy(Vector** flowField, Particle** particles);

#endif //VECTOR_SDL_FLOWFIELD_H

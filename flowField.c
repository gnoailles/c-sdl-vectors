#include <SDL2_gfxPrimitives.h>
#include "const.h"
#include "perlin.h"
#include "Vector.h"
#include "Particle.h"

void flowField_init(Vector** flowField,int size,Particle** particles, int partsNb) {
    int i = 0;
    while(i < size) {
        flowField[i] = NULL;
        ++i;
    }

    i = 0;
    while(i < partsNb) {
        particles[i] = particle_create();
        ++i;
    }

}

void flowField_update(Vector** flowField, Particle** particles, SDL_Renderer* rend, float inc, float* xoff, float* yoff, float* zoff) {

    if(flowField == NULL || particles == NULL || rend == NULL || xoff == NULL || yoff == NULL || zoff == NULL) return;

    int y = 0, x = 0;

    *yoff = 0;
    while (y < ROWS) {
        *xoff = 0;
        x = 0;
        while (x < COLS) {
            int idx = x + y * COLS;
            if(flowField[idx] != NULL) {
                free(flowField[idx]);
                flowField[idx] = NULL;
            }
            float angle = octavePerlin(*xoff, *yoff, *zoff, 4, 0.8) * 2 * M_PI * 4;
            Vector *v = vector_fromAngle(angle);
            float mag = vector_getMag(v);
            thickLineRGBA(rend, x * SCALE, y * SCALE, x * SCALE + v->x * SCALE / 2, y * SCALE + v->y * SCALE / 2, 1, 255, 255, 255, 80);
            vector_setMag(v, 0.3);
            flowField[idx] = v;

            *xoff += inc;
            ++x;
        }
        *yoff += inc;
        ++y;
    }
    *zoff += 0.005;

    int i = 0;
    while(i < PARTSNB) {
        particle_follow(particles[i], flowField);
        particle_update(particles[i]);
        particle_show(particles[i], rend);
        ++i;
    }
}

void flowField_destroy(Vector** flowField, Particle** particles) {
    if(particles == NULL || flowField == NULL) return;
    int i = 0;
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
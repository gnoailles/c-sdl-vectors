#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>
#include "Particle.h"
#include "Vector.h"
#include "const.h"

Particle* particle_create() {
    Particle* p = malloc(sizeof(*p));
    p->pos = vector_create(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
    p->vel = vector_create(0,0);
    p->acc = vector_create(0,0);
    p->prevPos = vector_copy(p->pos);
    p->maxSpeed = 2;
}

void particle_update(Particle* p) {
    p->prevPos->x = p->pos->x;
    p->prevPos->y = p->pos->y;
    vector_add(p->vel,p->acc);
    vector_limit(p->vel,p->maxSpeed);
    vector_add(p->pos,p->vel);

    if(p->pos->x >= SCREEN_WIDTH) p->pos->x = p->prevPos->x = 0;
    if(p->pos->x < 0) p->pos->x = p->prevPos->x = SCREEN_WIDTH-1;
    if(p->pos->y >= SCREEN_HEIGHT) p->pos->y = p->prevPos->y = 0;
    if(p->pos->y < 0) p->pos->y = p->prevPos->y = SCREEN_HEIGHT-1;

    vector_mult(p->acc,0);
}

void particle_follow(Particle* p, Vector* flowField[]) {
    int x = (int)floor(p->pos->x / SCALE);
    int y = (int)floor(p->pos->y / SCALE);
    int idx = x + y * COLS;

    particle_applyForce(p, flowField[idx]);
}

void particle_applyForce(Particle* p,Vector* force) {
    vector_add(p->acc, force);
}

void particle_show(Particle* p,SDL_Renderer* rend) {
    thickLineRGBA(rend, p->pos->x, p->pos->y, p->prevPos->x, p->prevPos->y, 1,255,255,255,255);
}

void particle_destroy(Particle* p) {
    free(p->pos);
    free(p->prevPos);
    free(p->acc);
    free(p->vel);
    free(p);
}
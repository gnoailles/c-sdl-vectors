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
    p->color[0] = (int)((p->pos->x/SCREEN_WIDTH)*255);
    p->color[1] = (int)((p->pos->y/SCREEN_HEIGHT)*255);
    p->color[2] = 255;
    p->color[3] = 255;
    p->maxSpeed = 3;
}

void particle_update(Particle* p) {
    if(p == NULL) return;
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
    if(p == NULL || flowField == NULL) return;
    int x = (int)floor(p->pos->x / SCALE);
    int y = (int)floor(p->pos->y / SCALE);
    int idx = x + y * COLS;

    if(flowField[idx] == NULL) return;

    particle_applyForce(p, flowField[idx]);
}

void particle_applyForce(Particle* p,Vector* force) {
    if(p == NULL || force == NULL) return;
    vector_add(p->acc, force);
}

void particle_show(Particle* p,SDL_Renderer* rend) {
    if(p == NULL || rend == NULL) return;
    thickLineRGBA(rend, p->pos->x, p->pos->y, p->prevPos->x, p->prevPos->y, 1,p->color[0],p->color[1],(vector_getMag(p->vel)/p->maxSpeed)*150,p->color[3]);
}

void particle_destroy(Particle* p) {
    if(p == NULL) return;
    free(p->pos);
    p->pos = NULL;
    free(p->prevPos);
    p->prevPos = NULL;
    free(p->acc);
    p->acc = NULL;
    free(p->vel);
    p->vel = NULL;
    free(p);
    p = NULL;
}
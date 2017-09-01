#ifndef PARTICLE_C
#define PARTICLE_C

#include "Vector.h"

typedef struct Particle {
    Vector* pos;
    Vector* vel;
    Vector* acc;
    Vector* prevPos;
    float maxSpeed;
    int color[4];
} Particle;

Particle* particle_create();

void particle_update(Particle* p);
void particle_follow(Particle* p, Vector* flowField[]);
void particle_applyForce(Particle* p,Vector* force);
void particle_show(Particle* p,SDL_Renderer* rend);
void particle_destroy(Particle* p);
#endif //PARTICLE_C

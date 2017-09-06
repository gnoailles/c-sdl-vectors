#include <stdlib.h>
#include <math.h>
#include "Vector.h"

Vector* vector_create(float x, float y) {
    Vector *vector = malloc(sizeof(*vector));
    vector->x = x;
    vector->y = y;
    return vector;
}
Vector* vector_copy(Vector* v) {
    if(v == NULL) return NULL;
    return vector_create(v->x,v->y);
}
Vector* vector_fromAngle(float a){
    return vector_create(cos(a),sin(a));
}



void vector_add(Vector* v1, Vector* v2) {
    if(v1 == NULL || v2 == NULL) return;
    v1->x += v2->x;
    v1->y += v2->y;
}
void vector_mult(Vector* v,float n) {
    if(v == NULL) return;
    v->x *= n;
    v->y *= n;
}



float vector_getMag(Vector *v){
    if(v == NULL) return 0;
    return sqrt(v->x*v->x + v->y*v->y);
}
float vector_getMagSq(Vector *v){
    if(v == NULL) return 0;
    return (v->x*v->x + v->y*v->y);
}

void vector_setMag(Vector* v, float len){
    if(v == NULL) return;
    vector_normalize(v);
    vector_mult(v,len);
}



void vector_limit(Vector* v, float max) {
    if(v == NULL) return;
    if (vector_getMagSq(v) > max*max) {
        vector_normalize(v);
        vector_mult(v,max);
    }
}
void vector_normalize(Vector *v){
    if(v == NULL) return;
    float m = vector_getMag(v);
    v->x = v->x/m;
    v->y = v->y/m;
}
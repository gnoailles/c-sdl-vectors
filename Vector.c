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
    return vector_create(v->x,v->y);
}
Vector* vector_fromAngle(float a){
    return vector_create(cos(a),sin(a));
}



void vector_add(Vector* v1, Vector* v2) {
    v1->x += v2->x;
    v1->y += v2->y;
}
void vector_mult(Vector* v1,float n) {
    v1->x *= n;
    v1->y *= n;
}



float vector_getMag(Vector *v){
    return sqrt(v->x*v->x + v->y*v->y);
}
float vector_getMagSq(Vector *v){
    return (v->x*v->x + v->y*v->y);
}

void vector_setMag(Vector* v, float len){
    vector_normalize(v);
    vector_mult(v,len);
}



void vector_limit(Vector* v, float max) {
    if (vector_getMagSq(v) > max*max) {
        vector_normalize(v);
        vector_mult(v,max);
    }
}
void vector_normalize(Vector *v){
    float m = vector_getMag(v);
    v->x = v->x/m;
    v->y = v->y/m;
}
#ifndef VECTOR_C
#define VECTOR_C

typedef struct Vector {
    float x;
    float y;
} Vector;

Vector* vector_create(float x, float y);
Vector* vector_copy(Vector* v);
Vector* vector_fromAngle(float a);

void vector_add(Vector* v1, Vector* v2);
void vector_mult(Vector* v1,float n);

float vector_getMag(Vector *v);
float vector_getMagSq(Vector *v);

void vector_setMag(Vector* v, float len);

void vector_normalize(Vector *v);
void vector_limit(Vector* v, float max);

#endif //VECTOR_C

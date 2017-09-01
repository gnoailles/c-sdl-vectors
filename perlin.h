#ifndef PERLIN_H
#define PERLIN_H

double octavePerlin(double x, double y, double z, int octaves, double persistence);
double perlin(double x, double y, double z);
static int inc(int num);
static double grad(int hash, double x, double y, double z);
static double fade(double t);
static double lerp(double a, double b, double x);

#endif //PERLIN_H
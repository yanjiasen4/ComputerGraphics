#pragma once
#include "math.h"

#define OCTAVES       3
#define PERLIN_RING   8
const float persistence = 0.45f;

float noise(int x, int y);
float smooth(int x, int y);
float cubicInterpolate(float v0, float v1, float v2, float v3, float x);
float noiseInterpolate(float x, float y);
float perlinNoise(float x, float y);

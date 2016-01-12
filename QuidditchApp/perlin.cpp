#include"perlin.h"

float noise(int x, int y)
{
	x = x % 25;
	y = y % 25;
	int n = x + y * 57;
	n = (n << 13) ^ n;
	return (1.0f + (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f)) / 2.0f;
}

float smooth(int x, int y)
{
	float corners = (noise(x - 1, y - 1) + noise(x + 1, y - 1) + noise(x - 1, y + 1) + noise(x + 1, y + 1)) / 16.0f;
	float sides = (noise(x - 1, y) + noise(x + 1, y) + noise(x, y - 1) + noise(x, y + 1)) / 8.0f;
	float center = noise(x, y) / 4.0f;
	return corners + sides + center;
}

float cosineInterpolate(float a, float b, float x)
{
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * 0.5f;

	return  a*(1 - f) + b*f;
}

float noiseInterpolate(float x, float y)
{
	int integerX = int(x);
	float fractionalX = x - integerX;
	int integerY = int(y);
	float fractionalY = y - integerY;

	// bilinear interpolation
	float v1 = smooth(integerX, integerY);
	float v2 = smooth(integerX + 1, integerY);
	float v3 = smooth(integerX, integerY + 1);
	float v4 = smooth(integerX + 1, integerY + 1);

	float i1 = cosineInterpolate(v1, v2, fractionalX);
	float i2 = cosineInterpolate(v3, v4, fractionalX);

	return cosineInterpolate(i1, i2, fractionalY);
}

float perlinNoise(float x, float y)
{
	float total = 0.0f;
	float p = persistence;
	int n = OCTAVES - 1;

	for (int i = 0; i <= n; i++)
	{
		float frequency = pow((float)2, i);
		float amplitude = pow(p, i);

		total = total + noiseInterpolate(x * frequency, y * frequency) * amplitude;
	}

	return total;
}
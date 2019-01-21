#ifndef STRUCTS_H
#define STRUCTS_H
#include <math.h>

struct fvector2D
{
	float x;
	float y;

	fvector2D()
	{
		x = 0.0;
		y = 0.0;
	}

	fvector2D(float nx, float ny) {
		x = nx;
		y = ny;
	}

	fvector2D operator+(fvector2D& n)
	{
		return fvector2D(n.x + x, n.y + y);
	}

	fvector2D operator-(fvector2D& n)
	{
		return fvector2D(n.x - x, n.y - y);
	}

	fvector2D operator*(float& n)
	{
		return fvector2D(n * x, n* y);
	}

	fvector2D operator/(float& n)
	{
		return fvector2D(x / n, y / n);
	}
};

struct fvector3D
{
	float x;
	float y;
	float z;

	fvector3D()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	fvector3D(float nx, float ny, float nz) {
		x = nx;
		y = ny;
		z = nz;
	}

	fvector3D operator+(fvector3D& n)
	{
		return fvector3D(n.x + x, n.y + y, n.z + z);
	}

	fvector3D operator-(fvector3D& n)
	{
		return fvector3D(n.x - x, n.y - y, n.z - z);
	}

	fvector3D operator*(float& n)
	{
		return fvector3D(n * x, n* y, n * z);
	}

	fvector3D operator/(float& n)
	{
		return fvector3D(x / n, y / n, z / n);
	}
};

const float magnitude2D(fvector2D orig);
const float magnitude3D(fvector3D orig);
const fvector2D normalize2D(fvector2D orig);
const fvector3D normalize3D(fvector3D orig);
const fvector3D cross(fvector3D vecA, fvector3D vecB);

#endif
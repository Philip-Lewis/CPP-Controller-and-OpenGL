#include "structs.h"

const float magnitude2D(fvector2D orig)
{
	return sqrtf((orig.x * orig.x) + (orig.y * orig.y));
}

const float magnitude3D(fvector3D orig)
{
	return sqrtf((orig.x * orig.x) + (orig.y * orig.y) + (orig.z * orig.z));
}

const fvector2D normalize2D(fvector2D orig)
{
	fvector2D finalVector;
	float mag = magnitude2D(orig);
	finalVector.x = orig.x / mag;
	finalVector.y = orig.y / mag;
	return finalVector;
}

const fvector3D normalize3D(fvector3D orig)
{
	fvector3D finalVector;
	float mag = magnitude3D(orig);
	finalVector.x = orig.x / mag;
	finalVector.y = orig.y / mag;
	finalVector.z = orig.z / mag;
	return finalVector;
}

const fvector3D cross(fvector3D vecA, fvector3D vecB)
{
	fvector3D finalVector;
	finalVector.x = (vecA.y * vecB.z) - (vecA.z * vecB.y);
	finalVector.y = (vecA.z * vecB.x) - (vecA.x * vecB.z);
	finalVector.z = (vecA.x * vecB.y) - (vecA.y * vecB.x);
	return finalVector;
}

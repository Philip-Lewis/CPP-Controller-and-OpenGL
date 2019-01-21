#ifndef ACTOR_H
#define ACTOR_H
#include "structs.h"
#include "Dependencies\GLEW\glew.h"
#include "Dependencies\FREEGLUT\glut.h"

class Actor
{
	private:
		fvector3D location;
	public:
		//constructors
		Actor() { location = fvector3D(0.0, 0.0, 0.0); }
		Actor(fvector3D newLoc) { location = newLoc; }
		Actor(float x, float y, float z) { location = fvector3D(x, y, z); }

		//abstract functions
		virtual void update(float deltaTime) = 0;
		virtual void render() = 0;

		//gets and sets
		void setLocation(float x, float y, float z)
		{
			location.x = x;
			location.y = y;
			location.z = z;
		}

		void setLocation(fvector3D newLoc)
		{
			location = newLoc;
		}

		fvector3D getLocation() { return location; }
};
#endif

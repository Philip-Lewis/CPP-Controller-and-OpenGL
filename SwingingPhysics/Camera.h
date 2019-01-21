#ifndef CAMERA_H
#define CAMERA_H
#include "Dependencies\GLEW\glew.h"
#include "Dependencies\FREEGLUT\glut.h"
//#include <math.h>
#include "structs.h"

class Camera
{
	private:
		fvector3D cameraPos;
		fvector3D cameraTarget;
		fvector3D cameraUpDirection;

	public:
		//constructors
		Camera()
		{ 
			cameraPos = fvector3D(0.0f, 0.0f, 3.0f);
			cameraTarget = fvector3D(0.0f, 0.0f, 3.0f);
		}

		Camera(fvector3D camPos, fvector3D camTarget) 
		{ 
			cameraPos = camPos;
			cameraTarget = camTarget;
		}

		Camera(float camPosX, float camPosY, float camPosZ, float camTargX, float camTargY, float camTargZ)
		{
			cameraPos = fvector3D(camPosX, camPosY, camPosZ);
			cameraTarget = fvector3D(camTargX, camTargY, camTargZ);
		}
		
		//functions
		void init(float winWidth, float winHeight);
		void render();

		//gets and sets
		fvector3D getCameraPos() { return cameraPos; }
		fvector3D getCameraTarget() { return cameraTarget; }
		void setCameraPos(float x, float y, float z) { cameraPos = fvector3D(x, y, z); }
		void setCameraTarget(float x, float y, float z) { cameraTarget = fvector3D(x, y, z); }
};
#endif
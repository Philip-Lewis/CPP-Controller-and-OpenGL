#include "Camera.h"

void Camera::init(float winWidth, float winHeight)
{
	float aspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//this works but does not take into consideration depth, suitable for 2D
	//glOrtho(-15.0f, 15.0f, -15.0f, 15.0f, -15.0f, 15.0f); 

	//this works for 3D as it allows for depth, however does not take into consideration aspect ratio in current form
	//glFrustum(-1.0f, 1.0f, -0.75f, 0.75f, 1.0f, 25.0f);

	//this allows for depth and almost takes into consideration aspect ratio, however it doesn't consider field of view correctly, leads to fish eye effect
	/*if (winWidth >= winHeight)
	{
		aspect = winHeight / winWidth;
		glFrustum(-1.0f, 1.0f, (-1.0f * aspect), aspect, 0.1f, 25.0f);
	}
	else
	{
		aspect = winWidth / winHeight;
		glFrustum((-1.0 * aspect), aspect, -1.0f, 1.0f, 0.1f, 25.0f);
	}*/

	//this allows for depth and takes into consideration both aspect ratio and FoV
	gluPerspective(45, (winWidth / winHeight), 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
}

void Camera::render()
{
	fvector3D cameraDirection;
	fvector3D up = fvector3D(0.0f, 1.0f, 0.0f);

	cameraDirection = normalize3D((cameraPos - cameraTarget));

	fvector3D camRight = normalize3D(cross(up, cameraDirection));

	cameraUpDirection = cross(cameraDirection, camRight);

	glLoadIdentity();
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
		cameraTarget.x, cameraTarget.y, cameraTarget.z,
		cameraUpDirection.x, cameraUpDirection.y, cameraUpDirection.z);
}
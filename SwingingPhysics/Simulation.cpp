#include "Simulation.h"

int Simulation::init(float winWidth, float winHeight, ControllerManager* mngr)
{
	player = new Player(fvector3D(0.0f, 1.0f, 0.0f), mngr, 4.0f);
	cam = new Camera(fvector3D(0.0f, 4.0f, 7.5f), fvector3D(0.0f, 0.0f, 0.0f));
	cam->init(winWidth, winHeight);
	elapsedTime = clock();

	//setting up lighting for simulation
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat direction[] = { 0.0f, 1.0f, 0.75f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, direction);
	//end of lighting

	return 0;
}

int Simulation::update()
{
	currentTime = clock();
	float deltaTime = float(currentTime - elapsedTime) / CLOCKS_PER_SEC;

	player->update(deltaTime);

	fvector3D newPlayerLoc = player->getLocation();
	cam->setCameraTarget(newPlayerLoc.x, newPlayerLoc.y + 1.0f, newPlayerLoc.z);
	cam->setCameraPos(newPlayerLoc.x, (newPlayerLoc.y + 2.5f), (newPlayerLoc.z + 5.0f));

	elapsedTime = currentTime;
	return 0;
}

int Simulation::render()
{
	cam->render();

	//render temporary floor
	//glColor3f(0.2f, 0.2f, 0.2f);
	GLfloat firstCorner[3] = { -10.0f, 0.0f, -10.0f };
	GLfloat secondCorner[3] = { 10.0f, 0.0f, 10.0f };
	GLfloat thirdCorner[3] = { -10.0f, 0.0f, 10.0f };
	GLfloat fourthCorner[3] = { 10.0f, 0.0f, -10.0f };

	glPushMatrix();
		GLfloat greyMaterial[] = { 0.9f, 0.9f, 0.9f, 1.0f };
		GLfloat greyDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		GLfloat greySpecular[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat  greyEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

		glBegin(GL_TRIANGLES);
		glMaterialfv(GL_FRONT, GL_AMBIENT, greyMaterial);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greyDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greySpecular);
		glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
		glMaterialfv(GL_FRONT, GL_EMISSION, greyEmission);
		glVertex3fv(&firstCorner[0]);
		glVertex3fv(&secondCorner[0]);
		glVertex3fv(&thirdCorner[0]);
		glEnd();

		glBegin(GL_TRIANGLES);
		glMaterialfv(GL_FRONT, GL_AMBIENT, greyMaterial);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greyDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greySpecular);
		glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
		glMaterialfv(GL_FRONT, GL_EMISSION, greyEmission);
		glVertex3fv(&fourthCorner[0]);
		glVertex3fv(&secondCorner[0]);
		glVertex3fv(&firstCorner[0]);
		glEnd();
	glPopMatrix();
	//end of rendering floor

	player->render();

	return 0;
}
//#include "Dependencies\GLEW\glew.h"
//#include "Dependencies\FREEGLUT\glut.h"
#include "Simulation.h"
//#include "ControllerManager.h"
#include <iostream>
using namespace std;

Simulation* sim;
ControllerManager* contManager;

void renderSim()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.53, 0.81, 0.98, 1.0);

	if (sim != nullptr)
	{
		contManager->refresh();
		sim->update();
		sim->render();
	}
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	int winWidth;
	int winHeight;

	winWidth = 800;
	winHeight = 600;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Swinging physics");

	glEnable(GL_DEPTH_TEST);

	contManager = new ControllerManager();
	contManager->refresh();

	sim = new Simulation();
	sim->init(winWidth, winHeight, contManager);

	glutDisplayFunc(renderSim);

	glutMainLoop();

	return 0;
}
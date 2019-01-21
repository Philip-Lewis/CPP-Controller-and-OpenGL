#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.h"
#include "ControllerManager.h"

class Player : public Actor
{
	private:
		ControllerManager* contManager;
		float mvmntSpeed;
	public:
		//constructors
		Player() : Actor() { contManager = nullptr; }
		Player(ControllerManager* mngr) : Actor() { contManager = mngr; }
		Player(fvector3D newLoc, ControllerManager* mngr) : Actor(newLoc) { contManager = mngr; mvmntSpeed = 1.0f; }
		Player(fvector3D newLoc, ControllerManager* mngr, float speed) : Actor(newLoc) { contManager = mngr;  mvmntSpeed = speed; }

		//override abstract functions
		void update(float deltaTime)
		{
			fvector3D tempLoc;
			fvector2D tempStick;

			tempLoc = getLocation();
			tempStick = contManager->checkLeftStick();
			
			tempLoc.x += (tempStick.x * (mvmntSpeed * deltaTime));
			tempLoc.z += ( -1 * (tempStick.y * (mvmntSpeed * deltaTime)));

			setLocation(tempLoc);
		}

		void render()
		{
			glPushMatrix();
			//glColor3f(1.0f, 0.0f, 0.0f);
			GLfloat redMaterial[] = { 0.2f, 0.2f, 0.2f, 1.0f };
			glMaterialfv(GL_FRONT, GL_AMBIENT, redMaterial);
			GLfloat redDiffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, redDiffuse);
			GLfloat redSpecular[] = { 0.1f, 0.0f, 0.0f, 1.0f };
			glMaterialfv(GL_FRONT, GL_SPECULAR, redSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
			GLfloat  redEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glMaterialfv(GL_FRONT, GL_EMISSION, redEmission);

			glTranslatef(getLocation().x, getLocation().y, getLocation().z);
			glutSolidSphere(1.0f, 25, 25);
			glPopMatrix();
		}
};
#endif 

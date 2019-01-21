#ifndef SIMULATION_H
#define SIMULATION_H
#include "Camera.h"
#include <time.h>
#include "Player.h"

class Simulation
{
	private:
		clock_t elapsedTime;
		clock_t currentTime;
		float accDueToGravity; //would usually put this in a physics manager but for in this case it feels like over complicating the issue.
		Camera* cam;
		Player* player;
	public:
		Simulation() { accDueToGravity = 0.0; }
		Simulation(float newGravityAcc) { accDueToGravity = newGravityAcc; }
		int init(float winWidth, float winHeight, ControllerManager* mngr);
		int update();
		int render();
};
#endif

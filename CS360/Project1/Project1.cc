#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
//#include <pthread.h>
#include <vector>
#include <string>
#include "Vector2D.h"
#include "Robot.h"
#include "Simulator.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#define SIZEX 10
#define SIZEY 40

int main(int argc, char **argv)
{
	Simulator* sim1; // your environment
	Robot*  r1; // your robot
	int id;     // the id of your robot
	int sx, sy; // the size of your environment
	int ix, iy; // the initial location of your robot
	int tx, ty; // the target location of your robot
	int steps;  // the steps before found the target
	int waitCounter = 100; // amount to wait between steps (milliseconds)
	Point2D pos; // a variable for 2D position
	
	srand(time(NULL)); // initialize random seed
	
	printf("\n\n*** CS360 Project 1 Begin *** \n\n");

	if (argc==3 && (sx=std::stoi(argv[1])) && (sy=std::stoi(argv[2]))) {
	printf("Project 1 environment size = [%d,%d]\n", sx, sy);
	} else {     
		sx = SIZEX;       // use SIZEX for your environment
		sy = SIZEY;       // use SIZEY for your environment
	}
	sim1 = new Simulator(sx,sy);    // create your environment
	printf("Simulator area [%d x %d] is created\n", sx, sy);

	tx = rand()%sx;     // random target x
	ty = rand()%sy;     // random target y
	sim1->setTarget(tx, ty);
	printf("Target is set at the location [%d,%d]\n", tx, ty);
	
	id = 1;             // robot id
	r1 = new Robot(id); // create your robot
	ix = rand()%sx;     // random initial x
	iy = rand()%sy;     // random initial y
	sim1->setRobot(r1, ix, iy); // place your robot in the environment
	pos = r1->getPosition();    // get the location of your robot
	printf("Robot %d is created at the location [%d,%d]\n\n", r1->getID(), (int)pos.x, (int)pos.y);
	steps = 0;
	//Illustration of how to get the target position
	std::cout<<"Target Position: ("<<sim1->getTarget().x<<","<<sim1->getTarget().y<<")"<<std::endl;
	//Illustration of how to get the target radiance. This will return -1 until you are sufficiently close to the target.
	std::cout<<"Target Radiance: "<<sim1->getTargetRadiance()<<std::endl;
	while (!sim1->robotFoundTarget()) {  // loop until your robot find the target
		
		/********************************************************************************/
		///TODO: Below is the code you must modify for your robot to find the target quickly
		// You move your robot by giving it an action
		// The robot must decide its actions intelligently to find the target quickly
		// Below is an example of random actions
		// r1->setRobotAction((RobotAction)(rand()%8));

		//Base case: We're at the goal!
		//This is done for us in the while loop

		//Case: Up-LEFT
		if (r1->getPosition().x > sim1->getTarget().x &&
			r1->getPosition().y > sim1->getTarget().y){
			r1->setRobotAction(MOVE_UP_LEFT);
		}
		//Case: Up-RIGHT
		else if (r1->getPosition().x > sim1->getTarget().x &&
				 r1->getPosition().y < sim1->getTarget().y){
			r1->setRobotAction(MOVE_UP_RIGHT);
		}
		//Case: Down-LEFT
		else if (r1->getPosition().x < sim1->getTarget().x &&
				 r1->getPosition().y > sim1->getTarget().y){
			r1->setRobotAction(MOVE_DOWN_LEFT);
		}
		//Case: Down-RIGHT
		else if (r1->getPosition().x < sim1->getTarget().x &&
				 r1->getPosition().y < sim1->getTarget().y){
			r1->setRobotAction(MOVE_DOWN_RIGHT);
		}
		//Case: Directly DOWN
		else if (r1->getPosition().x < sim1->getTarget().x &&
			r1->getPosition().y == sim1->getTarget().y){
			r1->setRobotAction(MOVE_DOWN);
		}
		//Case: Directly UP
		else if(r1->getPosition().x > sim1->getTarget().x &&
				r1->getPosition().y == sim1->getTarget().y){
			r1->setRobotAction(MOVE_UP);
		}
		//Case: Directly RIGHT
		else if(r1->getPosition().y < sim1->getTarget().y &&
				r1->getPosition().x == sim1->getTarget().x){
			r1->setRobotAction(MOVE_RIGHT);
		}
		//Case: Directly LEFT
		else if(r1->getPosition().y > sim1->getTarget().y &&
				r1->getPosition().x == sim1->getTarget().x){
			r1->setRobotAction(MOVE_LEFT);			
		}
		//Never happens
		else{

		}



		//r1->setForce(fx,fy);    // set the force for your robot
		///END TODO: No more editing after this point
		/********************************************************************************/
		
		// call the simulator to move your robot and count the steps
		
		sim1->moveRobot();
		sim1->display();
		steps++;
		#if defined(_WIN32) || defined(_WIN64)
		Sleep(waitCounter);
		#else
		usleep(1000*waitCounter);
		#endif
	}
	printf("My robot found the target in %d steps !!! \n\n", steps);
	//Illustration of how to get the target radiance. This will return -1 until you are sufficiently close to the target.
	std::cout<<"Target Radiance: "<<sim1->getTargetRadiance()<<std::endl;
	delete sim1;
	delete r1;
}


#include "Project3.h"


Project3::Project3(Simulator* sim) {
	// Here, you should construct the MDP and solve it using undiscounted value iteration.
}

RobotAction Project3::getOptimalAction(Point2D loc) {
	// Here, you should return the best action for Wheelbot, assuming it is currently at 'loc'.
    return (RobotAction) 3;//(rand()%4);
}

double Project3::getValue(Point2D loc) {
	// Here, you should return the value of the state corresponding to 'loc'.
    return 0;
}

#include "Project2.h"

/**
* @brief default constructor
*/
Project2::Project2(Simulator* sim1) {
	// Here, you should initialize the grid with all the known obstacles.
}

/**
 * @brief get optimal action
 * @param sim simulator pointer
 * @param r robot pointer
 * @return optimal action
 */
RobotAction Project2::getOptimalAction(Simulator* sim1, Robot* r1) {
	// Here, you should find the next step of the robot.
	// The robot should always follow a shortest path (wrt the known and sensed obstacles) to the goal.
    return (RobotAction)(rand()%8);
}

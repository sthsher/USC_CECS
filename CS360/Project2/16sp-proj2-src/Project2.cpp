#include "Project2.h"
#include <iostream>
#include <algorithm>
#include <cmath>
/**
* @brief default constructor
*/

Project2::Project2(Simulator* sim1) {
	// Here, you should initialize the grid with all the known obstacles.
	// Initialize entire grid to 0's


	for (int i = 0; i < sim1->SX; ++i){
		for (int j = 0; j < sim1->SY; ++j){
			AREA[i][j] = new AStarNode(this, Point2D(i,j));
		}
	}

	GenerateHeuristics(sim1);

	//Set all the obstacles to -1's
	std::vector<Point2D> obstacleVec = sim1->getKnownObstacleLocations();
	for (std::vector<Point2D>::iterator it = obstacleVec.begin(); it != obstacleVec.end(); it++){
		AREA[(int)(*it).x][(int)(*it).y]->SetAsObstacle();
	}

	GenerateNeighbors(sim1);

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
	
	//First, try to detect hidden objects
	std::vector<Point2D> localObstacles = r1->getLocalObstacleLocations();
	//go through the vector and add any new obstacles
	for (std::vector<Point2D>::iterator it = localObstacles.begin(); it != localObstacles.end(); it++){
		std::cout << "Obstacle: {" << (int)(*it).x << "," << (int)(*it).y << "}" << std::endl;

		//see if this is already marked as an obstacle
		if (AREA[(int)(*it).x][(int)(*it).y]->IsObstacle()){
			// AREA[(int)(*it).x][(int)(*it).y]->SetAsObstacle();
		} else{
			//it not an obstacle, update it
			std::cout << "Adding {" << (int)(*it).x << "," << (int)(*it).y << "}" << std::endl;
			AREA[(int)(*it).x][(int)(*it).y]->SetAsObstacle();
			//redo everyone's neighbors
			GenerateNeighbors(sim1);

		}
	}

	AStar( Point2D( (int)(sim1->getRobot()->X) ,(int)(sim1->getRobot()->Y) ), sim1);

	//Identify the next node to traverse
	AStarNode* nextNode = AREA[(int)sim1->getTarget().x][(int)sim1->getTarget().y];
	while (nextNode->GetParent() != AREA[(int)sim1->getRobot()->X][(int)sim1->getRobot()->Y]){
		nextNode = nextNode->GetParent();
	}

	int robotX = (int)sim1->getRobot()->X;
	int robotY = (int)sim1->getRobot()->Y;
	int nextX = (int)nextNode->GetX();
	int nextY = (int)nextNode->GetY();


/*
	//------- Print the path -------
	//stat from target
	
	AStarNode* node = AREA[(int)sim1->getTarget().x][(int)sim1->getTarget().y];
	while (node != NULL){
		node->print = true;
		node = node->GetParent();
	}

	AREA[(int)sim1->getRobot()->X][(int)sim1->getRobot()->Y]->print = true;
	
	for (int i = 0; i < sim1->SY; ++i){
		if (i / 10 == 0){
			std::cout << " " << i << " ";
		}else{
			std:: cout << " " << i;
		}
	}
	std::cout << std::endl;
	for (int i = 0; i < sim1->SX; ++i){
		for (int j = 0; j < sim1->SY; ++j){
			if (AREA[i][j]->print){
				std::cout << " x ";
			}
			else if (AREA[i][j]->GetFValue() != -1){
				std::cout << " . ";
			} else{
				std::cout << " # ";
			}
		}
		std::cout << " " << i << std::endl;
	}
	
	//------------------------------
*/

	//Case: Up-LEFT
	if (robotX > nextX &&
		robotY > nextY){
		return MOVE_UP_LEFT;
	}
	//Case: Up-RIGHT
	else if (robotX > nextX &&
			 robotY < nextY){
		return MOVE_UP_RIGHT;
	}
	//Case: Down-LEFT
	else if (robotX < nextX &&
			 robotY > nextY){
		return MOVE_DOWN_LEFT;
	}
	//Case: Down-RIGHT
	else if (robotX < nextX &&
			 robotY < nextY){
		return MOVE_DOWN_RIGHT;
	}
	//Case: Directly DOWN
	else if (robotX < nextX &&
		robotY == nextY){
		return MOVE_DOWN;
	}
	//Case: Directly UP
	else if(robotX > nextX &&
			robotY == nextY){
		return MOVE_UP;
	}
	//Case: Directly RIGHT
	else if(robotY < nextY &&
			robotX == nextX){
		return MOVE_RIGHT;
	}
	//Case: Directly LEFT
	// else if(robotY > nextY &&
	// 		robotX == nextX){
	else{
		return MOVE_LEFT;
	}







}

bool Project2::CompareNode (AStarNode* a, AStarNode* b) {
	if(a->GetFValue() > b->GetFValue()){
		return true;
	} else if (a->GetFValue() < b->GetFValue()){
		return false;
	} else{
		//equal
		if (a->GetGValue() > b->GetGValue()){
			return true;
		} else if (a->GetGValue() < b->GetGValue()){
			return false;
		} else{
			if(a->GetHValue() > b->GetHValue()){
				return true;
			} else{
				return false;
			}
		}
	}
}

bool Project2::IsDiagonal(Point2D a, Point2D b){
	//if any of the x or y value is the same
	return (a.x != b.x && a.y != b.y);
}


void Project2::AStar(Point2D point, Simulator* sim){

	std::vector<AStarNode*> openHeap;
	std::vector<AStarNode*> closeHeap;

	int robotPosX = (int)sim->getRobot()->X;
	int robotPosY = (int)sim->getRobot()->Y;
	AREA[robotPosX][robotPosY]->SetGValue(0);

	//initialize the visitQueue and starting node
	AREA[robotPosX][robotPosY]->SetParent(NULL);
	openHeap.push_back(AREA[robotPosX][robotPosY]);


	while(!openHeap.empty()){

		std::sort(openHeap.begin(), openHeap.end(), Project2::CompareNode);

		AStarNode* node = openHeap.back();

		openHeap.pop_back();

		std::vector<AStarNode*> neighbors = node->GetNeighborVector();

		for(std::vector<AStarNode*>::iterator it = neighbors.begin(); it != neighbors.end(); it++){
			bool add = true;

			float newFValue = 0;
				//successor's h value + current's g value + distance
				if (IsDiagonal((*it)->GetPoint(), node->GetPoint())){
					newFValue = (*it)->GetHValue() + (node->GetGValue() + 1.5);
				} else{
					newFValue = (*it)->GetHValue() + (node->GetGValue() + 1.0);
				}

			if (std::find(openHeap.begin(), openHeap.end(), (*it)) != openHeap.end()){
				//this successor is already on the open heap
				//if the one in the heap has a smaller f value, skip thi one
				if ((*std::find(openHeap.begin(), openHeap.end(), *it))->GetFValue() <= newFValue) {
					//the one on the heap has a lower f value, keep the on on the heap
					add = false;
				}
			}
			if (std::find(closeHeap.begin(), closeHeap.end(), (*it)) != closeHeap.end()){
				//this successor is already on the close heap
				//compare the f values
				if ((*std::find(closeHeap.begin(), closeHeap.end(), *it))->GetFValue() <= newFValue) {
					//the on in the heap has lower f value
					add = false;
				}
			}

			if (add){
				(*it)->SetParent(node);

				//Update the heuristics
				if (IsDiagonal((*it)->GetPoint(), node->GetPoint())){
					(*it)->SetGValue(node->GetGValue() + 1.5);				
				} else{
					(*it)->SetGValue(node->GetGValue() + 1.0);
				}
				//Base case, found target
				if ((*it)->GetX() == sim->getTarget().x && (*it)->GetY() == sim->getTarget().y){
					return;
				}
				openHeap.push_back(*it);
			}
		}
		closeHeap.push_back(node);
	}



}

bool Project2::CompareHeuristic(AStarNode* a, AStarNode* b){
	return (a->GetHValue() > b->GetHValue());
}

void Project2::GenerateNeighbors(Simulator* sim1){
	for (int i = 0; i < sim1->SX; ++i){
		for (int j = 0; j < sim1->SY; ++j){
			if (!AREA[i][j]->IsObstacle()){
				AREA[i][j]->GetNeighbors();
			}
		}
	}
}


void Project2::GenerateHeuristics(Simulator* sim1){

	//Going through walls
	float goalX = (float)sim1->getTarget().x;
	float goalY = (float)sim1->getTarget().y;
	//loop through all the tiles
	for (int i = 0; i < sim1->SX; ++i){
		for (int j = 0; j < sim1->SY; ++j){
			if (AREA[i][j]->GetHValue() == OBSTACLE_TILE){
				//this is a obstacle, skip it
			}else{
				float dx = std::abs((float)i - goalX);
				float dy = std::abs((float)j - goalY);
				// AREA[i][j]->SetHValue((1.5 * std::min(dx,dy)) + (std::max(dx, dy) - std::min(dx, dy)));
				AREA[i][j]->SetHValue(dx + dy - (0.5*std::min(dx,dy)));

			}
			
		}
	}
}
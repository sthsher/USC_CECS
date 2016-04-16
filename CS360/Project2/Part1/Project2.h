#ifndef Project2_hpp
#define Project2_hpp

#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include "Robot.h"
#include "Vector2D.h"
#include "Simulator.h"

#define OBSTACLE_TILE -1
#define UNEXPANDED_TILE -2

class Project2 {
private:

	class AStarNode{
	private:
		bool reverse;
		float hValue;
		float gValue;
		float fValue;
		Project2* project;
		Point2D point;
		AStarNode* parent;
		std::vector<AStarNode*> neighbors;

	public:

		bool print;

		AStarNode(Project2* project, Point2D point):
			project(project),
			point(point),
			parent(NULL)
		{
			hValue = gValue = fValue = UNEXPANDED_TILE;
			print = false;
		}

		// bool operator<(const AStarNode& rhs){
		// 	return this->GetFValue() > rhs.GetFValue();
		// }

		void SetAsObstacle(){
			hValue = gValue = fValue = OBSTACLE_TILE;
		}

		void SetHValue(float h){
			hValue = h;
		}
		
		void SetGValue(float g){
			gValue = g;
			//F value should already have been set, so also set f value
			fValue = gValue + hValue;
		}

		void SetFValue(float f){
			fValue = f;
		}

		void SetParent(AStarNode* p){
			parent = p;
		}

		Point2D GetPoint(){
			return point;
		}

		int GetX(){
			return (int)point.x;
		}

		int GetY(){
			return (int)point.y;
		}

		float GetHValue() const{
			return hValue;
		}

		float GetFValue() const{
			return fValue;
		}

		float GetGValue() const{
			return gValue;
		}

		AStarNode* GetParent(){
			return parent;
		}

		std::vector<AStarNode*> GetNeighborVector(){
			return neighbors;
		}

		bool IsObstacle(){
			return fValue == OBSTACLE_TILE;
		}

		bool IsUnexpandedNeighbors(){
			for (std::vector<AStarNode*>::iterator it = neighbors.begin(); it != neighbors.end(); it++){
				if ((*it)->GetFValue() == UNEXPANDED_TILE){
					return true;
				}
			}
			return false;
		}

		void GetNeighbors(){
			//clear the vector first
			neighbors.clear();

			int x = (int)point.x;
			int y = (int)point.y;
			//top left
			if (project->AREA[x-1][y-1]->GetHValue() != OBSTACLE_TILE){
				neighbors.push_back(project->AREA[x-1][y-1]);
			}
			//top
			if (project->AREA[x-1][y]->GetHValue() != OBSTACLE_TILE){
				neighbors.push_back(project->AREA[x-1][y]);
			}
			//top right
			if (project->AREA[x-1][y+1]->GetHValue() != OBSTACLE_TILE){
				neighbors.push_back(project->AREA[x-1][y+1]);
			}
			//left
			if (project->AREA[x][y-1]->GetHValue() != OBSTACLE_TILE){
				neighbors.push_back(project->AREA[x][y-1]);
			}
			//right
			if (project->AREA[x][y+1]->GetHValue() != OBSTACLE_TILE){
				neighbors.push_back(project->AREA[x][y+1]);
			}
			//bot left
			if (project->AREA[x+1][y-1]->GetHValue() != OBSTACLE_TILE){
				neighbors.push_back(project->AREA[x+1][y-1]);
			}
			//bot
			if (project->AREA[x+1][y]->GetHValue() != OBSTACLE_TILE){
				neighbors.push_back(project->AREA[x+1][y]);

			}
			//bot right
			if (project->AREA[x+1][y+1]->GetHValue() != OBSTACLE_TILE){
				neighbors.push_back(project->AREA[x+1][y+1]);
			}

		}
	};

	static bool CompareNode(AStarNode* a, AStarNode* b);
	static bool CompareHeuristic(AStarNode* a, AStarNode* b);
	AStarNode* AREA[MAX_X][MAX_Y];
	Simulator* sim;
	void GenerateHeuristics();
	std::vector<AStarNode*> heap;
	void AStar(Point2D point);
	bool IsDiagonal(Point2D a, Point2D b);
	void GenerateNeighbors();

public:
	/**
	 * @brief default constructor
	 */
	Project2(Simulator* sim1);
	~Project2();

	/**
	 * @brief get optimal action
	 * @param sim1 simulator pointer
	 * @param r robot pointer
	 * @return optimal action
	 */
	RobotAction getOptimalAction(Simulator* sim1, Robot* r1);
};

#endif

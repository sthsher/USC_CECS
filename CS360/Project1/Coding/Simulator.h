#ifndef Simulator_h
#define Simulator_h

#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include "Robot.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <stdlib.h>
#endif

#define EMPTY       0
#define OCCUPIED    1
#define TARGET      2
#define MAX_X       200
#define MAX_Y       200
/**
 * @class Simulator
 * @brief simulator object
 */
class Simulator
{
private:

    int TX, TY; /**< Target location */
    int targetRadiance; /**< radiance of target */
    float radianceArea; /**< how much radiance the target has (how far away it can be seen) */
public:
    
    int     SX, SY;  /**< environment size */
    int     AREA[MAX_X][MAX_Y];  /**< pre-allocated 2d array */
    Robot*  robot; /**< pointer to a robot */
    /**
     * @brief constructor
     * @param sx size of environment (x)
     * @param sy size of environment (y)
     */
    Simulator(int sx, int sy) {
        SX = sx>MAX_X ? MAX_X : sx;
        SY = sy>MAX_Y ? MAX_Y : sy;
        this->clean();
        targetRadiance = 30;
        radianceArea = 5.0;
    }
    /**
     * @brief clear the environment
     */
    void clean() {
        for (int x=0; x<SX; x++) {
            for (int y=0; y<SY; y++) {
                AREA[x][y] = EMPTY;
            }
        }
    }
    /**
     * @brief display the environment on the terminal
     */
    void display() {
        //printf("\033c"); // clear the terminal screen
        #if defined(_WIN32) || defined(_WIN64)
        system("cls");
        #else
        system("clear");
        #endif
        for (int x=0; x<SX; x++) {
            for (int y=0; y<SY; y++) {
                if (AREA[x][y]==EMPTY)
		   printf(".");
		else if (AREA[x][y]==TARGET)
		   printf("$");
		else printf("O");
            }
	    printf("\n");
        }
    }
    /**
     * @brief get the target
     * @return target position
     */
    Point2D getTarget() {
        return Point2D(TX,TY);
    }
    /**
     * @brief set target 
     * @param tx target x coordinate
     * @param ty target y coordinate
     */
    void setTarget(int tx, int ty) {
        TX = tx;
        TY = ty;
        AREA[tx][ty] = TARGET;
    }
    /**
     * @brief set robot
     * @param r robot
     * @param x x coord of robot
     * @param y y coord of robot
     */
    void setRobot(Robot* r, int x, int y) {
        r->movePosition(x,y);
        robot = r;
        AREA[r->X][r->Y] = OCCUPIED;
    }
    /**
     * @brief get radiance of the target
     * @return radiance of target
     */
    int getTargetRadiance() {
        int X1 = TX - robot->X;
        int Y1 = TY - robot->Y;
        if (X1 == 0 && Y1 == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    /**
     * @brief get radiance of the target
     * @return radiance of target
     */
    int getTargetDistance() {
        int X1 = TX - robot->X;
        int Y1 = TY - robot->Y;
        if (sqrt(X1*X1 + Y1*Y1) < radianceArea) {
            return sqrt(X1*X1 + Y1*Y1);
        } else {
            return -1;
        }
    }
    /**
     * @brief has robot found target?
     * @return true if yes, false otherwise
     */
    bool robotFoundTarget() {
        return (robot->X==TX && robot->Y==TY);
    }
    /**
     * @brief get the robot
     * @return pointer to robot
     */
    Robot* getRobot() {
        return this->robot;
    }
    /**
     * @brief is the environment occupied at (x,y)
     * @param x x coordinate of position
     * @param y y coordinate of position
     */
    bool isOccupied(int x, int y) {
        return (AREA[x][y]==OCCUPIED);
    }
    /**
     * @brief move the robot
     */
    void moveRobot()
    {
        Robot* r = this->getRobot();
        
        int x1 = r->X;
        int y1 = r->Y;
        
//        printf("Robot %d's current location = [%d,%d] \n", r->getID(), r->X, r->Y);
        
        int x2, y2;
        
        Vector2D d = r->getForce();  // get the force on robot
        double deg = d.getTheta();  // calculate the force direction
        if (deg>-22.5 && deg<=22.5)           { r->VX = 1;  r->VY = 0;
            } else if (deg>22.5 && deg<=67.5)     { r->VX = 1;  r->VY = 1;
            } else if (deg>67.5 && deg<=112.5)    { r->VX = 0;  r->VY = 1;
            } else if (deg>112.5 && deg<=157.5)   { r->VX = -1; r->VY = 1;
            } else if (deg<=-22.5 && deg>-67.5)   { r->VX = 1;  r->VY = -1;
            } else if (deg<=-67.5 && deg>-112.5)  { r->VX = 0;  r->VY = -1;
            } else if (deg<=-112.5 && deg>-157.5) { r->VX = -1; r->VY = -1;
            } else {                                r->VX = -1; r->VY = 0; }
        
//        printf("Robot %d's velocity = [%d,%d] \n", r->getID(), r->VX, r->VY);
    
        x2 = x1 + r->VX;
        x2 = x2 < 0 ? 0 : x2;
        x2 = x2 > SX ? SX : x2;
        y2 = y1 + r->VY;
        y2 = y2 < 0 ? 0 : y2;
        y2 = y2 > SY ? SY : y2;

        while (this->isOccupied(x2, y2) || x2>=this->SX || y2>=this->SY || x2<0 || y2<0) {
//            printf("Cell [%d,%d] is occupied, chooses a random direction [%d,%d]\n", x2, y2, r->VX, r->VY);
            r->VX = rand()%10 < 5 ? 1 : -1;
            r->VY = rand()%10 < 5 ? 1 : -1;
            r->FX = r->VX;  // change force as well
            r->FY = r->VY;  // change force as well
            x2 = x1 + r->VX;
            x2 = x2 < 0 ? 0 : x2;
            x2 = x2 > SX ? SX : x2;
            y2 = y1 + r->VY;
            y2 = y2 < 0 ? 0 : y2;
            y2 = y2 > SY ? SY : y2;
        }
        
        r->movePosition(x2, y2);
        AREA[x1][y1] = EMPTY;       // empty the last position
        AREA[x2][y2] = OCCUPIED;    // occupy the new position
//        printf("Robot %d moved to [%d,%d]\n", r->getID(), x2, y2);
    }
};


#endif /* Simulator_h */

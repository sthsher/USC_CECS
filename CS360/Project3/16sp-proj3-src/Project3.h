#ifndef Project3_hpp
#define Project3_hpp

#include <stdio.h>
#include <vector>
#include "Vector2D.h"
#include "Simulator.h"

class Project3 {
private:

public:
    Project3(Simulator* sim1);
    RobotAction getOptimalAction(Point2D position);
    double getValue(Point2D position);
};

#endif

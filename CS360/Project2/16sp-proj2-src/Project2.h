#ifndef Project2_hpp
#define Project2_hpp

#include <stdio.h>
#include <vector>
#include "Robot.h"
#include "Vector2D.h"
#include "Simulator.h"

class Project2 {
private:

public:
    /**
     * @brief default constructor
     */
    Project2(Simulator* sim1);

    /**
     * @brief get optimal action
     * @param sim1 simulator pointer
     * @param r robot pointer
     * @return optimal action
     */
    RobotAction getOptimalAction(Simulator* sim1, Robot* r1);
};

#endif

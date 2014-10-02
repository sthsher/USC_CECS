#ifndef user_H_
#define user_H_

#include "../LList/Set/LListSet.h"
#include "../wall/wall.h"

using namespace std;

class user
{
        public:
                user();
                user(string info[]);                                    //initializes with user's information
                ~user();

                void setUserInfo(string s, int n);              //n is the array position
                void setWall(wall *newWall);

                string returnUserInfoInt(int n);                //uses index of the userInformation array to return information
                string returnUserInfoString(string s);          //Uses string to return the user's information                                                                                                //eg "firstname" or "fname" will return the firstname field
                wall *returnWall();

                void printUserInfo();
                void printWall();


        private:
                string userInfo[5];
                wall *userWall;


};

#include "user.hpp"

#endif //user_H_
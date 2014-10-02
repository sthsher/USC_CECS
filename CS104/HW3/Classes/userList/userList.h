#ifndef userList_H_
#define userList_H_

#include "../LList/Set/LListSet.h"
#include "../user/user.h"

#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

class userList
{
        public:
                userList();
                ~userList();

                void addUser(user newUser);                                                                                                                                             //Adds user to the list
                void overwrite(user newUser, const string &fName, const string &lName, const string &password); //overwrites the user with the corresonding name and password with its updated information

                int returnTotalUsers();                                                                                                                                                 //returns the total number of users

                bool containsUser(const string &fName, const string &lName, const string &password);                    //returns true if user exists with given name and password

                user returnUser(const string &fName, const string &lName, const string &password);                              //returns user by its name and password
                user returnUserByIndex(int index);                                                                                                                              //returns user by its index
                
                void removeUserByIndex(int index);                                                                                                                              //removes user by its index

                void printAllUsers() const;                                                                                                                                             //prints all users and their information

        private:
                LListSet<user> *userListPtr;
                int totalUsers;


};

#include "userList.hpp"


#endif //userList_H_
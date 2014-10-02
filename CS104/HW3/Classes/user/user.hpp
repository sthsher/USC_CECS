#include <iostream>
using namespace std;

user::user()
{
        //set everything as empty string
        for (int i = 0; i < 5; ++i)
        {
                userInfo[i] = "";
        }

        userWall = NULL;

}


user::user(string info[])
{
        //goes through array and set the corresponding information as the userInfo's information
        for (int i = 0; i < 5; i++)
        {
                userInfo[i] = info[i];
        }

        userWall = NULL;

}

user::~user()
{

}

void user::setUserInfo(string s, int n)
{
        userInfo[n] = s;
}

void user::setWall(wall *newWall)
{
        userWall = newWall;
}

string user::returnUserInfoInt(int n)
{
        return userInfo[n];
}

//Checks for requested field by string input and returns that information
string user::returnUserInfoString(string s)
{
        if(s == "fName" || s == "firstName" || s == "firstname" || s == "FirstName" || s == "Firstname")
        {
                return userInfo[0];
        }
        if(s == "lName" || s == "lastName" || s == "lastname" || s == "LastName" || s == "Lastname")
        {
                return userInfo[1];
        }
        if(s == "Age" || s == "age")
        {
                return userInfo[2];
        }
        if(s == "Password" || s == "password" || s == "pwd" || s == "PWD")
        {
                return userInfo[3];
        }
        if(s == "numOfPosts" || s == "numberOfPosts")
        {
                return userInfo[4];
        }       

        //None of the keywords recognized, return empty string
        //cout debugging statement
        cout<<"ERROR: NO VALID KEYWORD FOR FUNCTION"<<endl;
        cout<<"returnUserInfoString in class user"<<endl;
        return "";
}



wall* user::returnWall()
{
        return userWall;
}

void user::printUserInfo()
{
        cout<<"--------------------------------------------------"<<endl;
        cout<<"Name:            "<<userInfo[0]<<" "<<userInfo[1]<<endl;
        cout<<"Age:             "<<userInfo[2]<<endl;
        cout<<"Password:        "<<userInfo[3]<<endl;
        cout<<"Number of Posts: "<<userInfo[4]<<endl;
        cout<<"--------------------------------------------------"<<endl;

        return;
}



void user::printWall()
{
        cout<<"Printing all posts by user "<<userInfo[0]<<" "<<userInfo[1]<<endl<<endl;

        userWall->printAllPosts();
}

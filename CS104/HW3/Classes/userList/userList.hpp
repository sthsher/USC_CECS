#include <iostream>
using namespace std;

//Constructor: reads the file and initializes all data
userList::userList()
{
        ifstream fin;
        bool isEnd = false;                                     //check if it is at the end of file
        userListPtr = new LListSet<user>;       //makes new list
        totalUsers = 0;                                         //Keeps track of total users

        string userInfo[5];                                     //Stores user information
        string temp;                                            //used for dump or checking markers

        fin.open("user_info_file.txt");

        //gets the first line <<<NEWUSER>>, get rid of it
        fin>>temp;
        temp = "";

        if(fin == NULL)
        {
                cout<<"Error: File not found, please check directory for info file"<<endl<<endl;
                cout<<"---Program End---"<<endl;
                exit(1);
        }

        while (isEnd == false)
        {
                if(fin.eof())
                {
                        fin.close();
                        break;
                }
                else
                {

                        //gets the user info line
                        for (int i = 0; i < 5; i++)
                        {
                                fin>>userInfo[i];
                        }

                        //Make a new user and initialize with the information
                        user newUser(userInfo);

                        //Make a new wall for the user
                        wall *newWall = new wall;

                        //Debuging statement
                        //newUser.printUserInfo();

                        //get the next line
                        getline(fin,temp);

                        //loops until all posts have been added to the user's wall
                        while (true)
                        {
                                //make new wallpost
                                wallPost newPost;

                                //get the author's information
                                getline(fin,temp);
                                //cout<<"temp: "<<temp<<endl;
                                if(temp == "<<<NEWUSER>>>") 
                                {
                                        //getline(fin,temp);
                                        break;
                                }
                                if(temp == "<<<END>>>")
                                {
                                        isEnd = true;
                                        break;
                                }

                                //set the author, get the post, and set the post
                                newPost.setAuthor(temp);
                                getline(fin,temp);
                                newPost.setPost(temp);

                                //debugging statement
                                //newPost.printPost(1);

                                //Add the new post to the wall
                                newWall->addPost(newPost);
                        }

                        //Wall created, add to user
                        newUser.setWall(newWall);

                        //user ready, add to list
                        userListPtr->add(newUser);
                        //incremenet total users
                        totalUsers++;

                        if (isEnd == true)
                        {
                                break;
                        }

                }
        }



}

//destructor, file output
userList::~userList()
{

        ofstream fout;

        //make a new file
        remove("user_info_file.txt");
        fout.open("user_info_file.txt");

        //makes a temp user to write their information
        LListElement<user> *temp;

        bool isLast = false;

        //this is the first line
        fout<<"<<<NEWUSER>>>"<<endl;

        //goes through all the users
        for (temp = userListPtr->returnStart(); temp != NULL; temp = temp->returnNext())
        {

                //test if this is last user
                if (temp->returnNext() == NULL) isLast = true;

                //write user information first
                user outUser = temp->returnData();

                for (int i = 0; i < 5; i++)
                {
                        fout<<outUser.returnUserInfoInt(i)<<" ";
                }
                fout<<endl;

                //Now output posts
                //Make a wall for the user
                wall *outWall = outUser.returnWall();

                //close the file so the wall destructor can write on it
                fout.close();

                //destructor of wall will write in the file
                delete outWall;

                //open the file again
                fout.open("user_info_file.txt", ios::app);

                //Last user reached, output the end marker, if not put new user marker
                if(isLast)fout<<"<<<END>>>";
                else fout<<"<<<NEWUSER>>>"<<endl;


        }

        fout.close();
}

void userList::addUser(user newUser)
{
        userListPtr->add(newUser);
}

void userList::overwrite(user newUser, const string &fName, const string &lName, const string &password)
{
        user oldUser;

        LListElement<user> *temp;

        //Goes through the users and finds the user with the corresponding name and password
        for (temp = userListPtr->returnStart(); temp != NULL; temp = temp->returnNext())
        {
                oldUser = temp->returnData();

                if( oldUser.returnUserInfoString("fName") == fName &&
                        oldUser.returnUserInfoString("lName") == lName &&
                        oldUser.returnUserInfoString("password") == password)
                {
                        temp->setData(newUser);
                }

        }

}

user userList::returnUser(const string &fName, const string &lName, const string &password)
{
        user checkUser;

        LListElement<user> *temp;

        //Goes through the users and finds the user with the corresponding name and password
        for (temp = userListPtr->returnStart(); temp != NULL; temp = temp->returnNext())
        {
                checkUser = temp->returnData();

                if( checkUser.returnUserInfoString("fName") == fName &&
                        checkUser.returnUserInfoString("lName") == lName &&
                        checkUser.returnUserInfoString("password") == password)
                {
                        return checkUser;
                }

        }
}


user userList::returnUserByIndex(int index)
{
        LListElement<user> *temp = userListPtr->returnStart();

        for (int i = 0; i < index; ++i)
        {
                temp = temp->returnNext();
        }

        return (temp->returnData());

}

void userList::removeUserByIndex(int index)
{       
        LListElement<user> *temp = userListPtr->returnStart();

        for (int i = 0; i < index; ++i)
        {
                temp = temp->returnNext();
        }

        userListPtr->removePtr(temp);
}

void userList::printAllUsers() const
{
        user tempUser;
        int counter = 1; //outputs the user number to keep track

        LListElement<user> *tempElement;

        for (tempElement = userListPtr->returnStart(); tempElement != NULL; tempElement = tempElement->returnNext(), counter++)
        {
                tempUser = tempElement->returnData();
                cout<<"User No. "<<counter<<endl;
                tempUser.printUserInfo();
                cout<<endl;
        }

}


int userList::returnTotalUsers()
{
        return totalUsers;
}

bool userList::containsUser(const string &fName, const string &lName, const string &password)
{

        user checkUser;

        LListElement<user> *temp;

        //Goes through the users and finds the user with the corresponding name and password
        for (temp = userListPtr->returnStart(); temp != NULL; temp = temp->returnNext())
        {
                checkUser = temp->returnData();

                if( checkUser.returnUserInfoString("fName") == fName &&
                        checkUser.returnUserInfoString("lName") == lName &&
                        checkUser.returnUserInfoString("password") == password)
                {       
                        //user exists, return true;
                        return true;
                }

        }

        return false;
}
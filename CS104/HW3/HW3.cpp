//Consol input/ouput functions
#include <iostream>
#include <iomanip>

//String functions
#include <string>
#include <sstream>

//File input/output functions
#include <fstream>

//Standard Library
#include <stdlib.h>

//Classes
#include "Classes/LList/Element/LListElement.h"
#include "Classes/LList/Set/LListSet.h"
#include "Classes/userList/userList.h"
#include "Classes/user/user.h"
#include "Classes/wall/wall.h"
#include "Classes/wallPost/wallPost.h"

using namespace std;

//Pass in first and last name, constructs both into one single string using stringstream
string constructName(string firstName, string lastName)
{
        string fullName;

        stringstream ss;
        ss.str(firstName + " " + lastName);
        fullName = ss.str();

        return fullName;
}

//Accesses the userInfo string array and converts the number of posts from a string to a int
//Returns an int
int getNumOfPosts(user newUser)
{
        int num;
        string posts = newUser.returnUserInfoString("numOfPosts");                      //number of posts in string format

        num = atoi(posts.c_str());

        return num;
}

//Checking for any of the key words. If so, return true
bool checkCancel(string s)
{
        if (s == "RESTART" || s == "restart" || s == "Restart" ||
                s == "EXIT" || s == "Exit" || s == "exit" ||
                s == "Back" || s == "BACK" || s == "back" ||
                s == "Logout" || s == "LOGOUT" || s == "logout" || s == "LogOut")
        {
                return true;
        }

        return false;
}

//Creates new account
void createAccount(userList *list)
{
        cout<<endl<<"Enter \"RESTART\" in any field to start over if you make a mistake"<<endl;

        //Stores new user information
        string newFName, newLName, newAge, newPassword, confirmPassword;

        bool repeat = true;
        bool requestRepeat = false;
        bool passwordIsGood = false;

        while (repeat == true)  //Keeps looping until user finishes. Allows user to redo fields
        {
                while (true)
                {
                        requestRepeat = false;
                        passwordIsGood = false;
                        cout<<"-----------------------------------------------------------------"<<endl;
                                                                                                                                                                        //These lines check if user requested to restart their data entry
                        cout<<"Please enter your first name:      ";cin>>newFName;                              requestRepeat = checkCancel(newFName); if (requestRepeat == true) break;
                        cout<<"Please enter your last name:       ";cin>>newLName;                              requestRepeat = checkCancel(newLName); if (requestRepeat == true) break;
                        cout<<"Please enter your age:             ";cin>>newAge;                                requestRepeat = checkCancel(newAge); if (requestRepeat == true) break;

                        while(passwordIsGood == false) //Makes sure passwords are the same
                        {
                                cout<<"Please enter your password:        ";cin>>newPassword;           requestRepeat = checkCancel(newPassword); if (requestRepeat == true) break;     
                                cout<<"Please confirm your password:      ";cin>>confirmPassword;       requestRepeat = checkCancel(confirmPassword); if (requestRepeat == true) break; 

                                if (newPassword == confirmPassword)     passwordIsGood = true;
                                else cout<<endl<<"Error: Passwords don't match."<<endl<<endl;
                        }

                        if (requestRepeat == true) break;

                        cout<<"-----------------------------------------------------------------"<<endl<<endl;

                        repeat = false;
                        break;
                }
        }

        //The user has inputted information


        //Check if user already exists: If they exist, output an error and return
        bool isUser;
        char dump;

        isUser = list->containsUser(newFName, newLName, newPassword);
        if (isUser == true)     
        {
                cout<<"Error: User already exists!"<<endl;
                cout<<"Enter any key to return to menu: ";cin>>dump;cout<<endl;
                return; 
        }
        //New user does not exist. Make a new user

        cout<<"creating new user"<<endl;

        //create the new user
        user newUser;

        //Fill in the user's information
        newUser.setUserInfo(newFName,0);
        newUser.setUserInfo(newLName,1);
        newUser.setUserInfo(newAge,2);
        newUser.setUserInfo(newPassword,3);
        newUser.setUserInfo("0",4);

        //Make a new wall for the user
        wall *newWall = new wall;

        //Wall is empty, so just add the wall to the user
        newUser.setWall(newWall);

        //Show the new user's info
        newUser.printUserInfo();

        //Add the user the the list
        list->addUser(newUser);

        //Pause before proceeding
        char proceed;
        cout<<"Congratulations! You have created your account!"<<endl;
        cout<<"Enter any key to return to the main menu: ";cin>>proceed;cin.ignore(256,'\n');cout<<endl<<endl;
}

//Takes in the cin of the first word of the post and the getline of the rest of the post and combines them together
//Solves the problem of messy getline bugs from only using getline by using stringstream
string constructPost(string dump, string post)
{
        string fullPost;

        stringstream ss;
        ss.str(dump + post);
        fullPost = ss.str();

        return fullPost;
}

//Converts integer to string using string stream
//itoa function does not work. Might as well make my own
string intToString(int n)
{
        string foo;

        stringstream ss;
        ss << n;
        foo = ss.str();

        return foo;
}

//Adds 1 to the field "number of posts" in the user information whenever user makes a post
user incrementPost(user currentUser)
{
        string sNum;                                            //number in string

        sNum = currentUser.returnUserInfoString("numOfPosts");

        int num = atoi(sNum.c_str());           //number in integer

        num++;

        sNum = intToString(num);                        //convert string back to number

        currentUser.setUserInfo(sNum, 4);       //put information back in user

        return currentUser;
}

//Subtracts 1. Same as "increment post" but decrements. Used when user deletes a post
user decrementPost(user currentUser)
{
        string sNum;

        sNum = currentUser.returnUserInfoString("numOfPosts");

        int num = atoi(sNum.c_str());

        num--;

        sNum = intToString(num);

        currentUser.setUserInfo(sNum, 4);

        return currentUser;
}

//Allows user to create a post
user createPost(user currentUser, string author)
{
        //Get the wall of the user
        wall *userWall = currentUser.returnWall();

        //Make a new wallpost
        wallPost newPost;

        //Used to store the post
        string dump;
        string post;

        //User input the post
        cout<<"*Remember, posts can only be 1 line long*"<<endl<<endl;
        cout<<"------------------"<<endl;
        cout<<"|Write a new post|"<<endl;
        cout<<"-----------------------------------------------------------------"<<endl<<endl;
        cout<<"New post: ";cin>>dump;getline(cin,post);
        cout<<endl;
        cout<<"-----------------------------------------------------------------"<<endl<<endl;

        //Construct the post from dump and post
        post = constructPost(dump, post);

        cout<<"--Post Successfully Created--"<<endl;

        //Set post author as current user author and set the post
        newPost.setAuthor(author);
        newPost.setPost(post);

        //Add the post to the user's wall
        userWall->addPost(newPost);

        //Incremement the field "number of posts"
        currentUser = incrementPost(currentUser);

        //Set new wall with the new post as the user's wall
        currentUser.setWall(userWall);

        //Show user all the posts, including the new post.
        currentUser.printWall();

        return currentUser;
}

//Allows user to delete post
user deletePost(user currentUser)
{
        //Show entire wall
        currentUser.printWall();

        //Get user's wall
        wall *userWall = currentUser.returnWall();

        //Get necessary information.
        int toDelete;

        //Get max number of posts to verify validity of user's input
        string sTotal = currentUser.returnUserInfoString("numOfPosts");
        int totalPosts = atoi(sTotal.c_str());


        cout<<endl<<"Please select which post to delete"<<endl;
        cout<<endl<<"Or enter '0' to go back to the menu: "<<endl;
        cout<<"Delete post ";cin>>toDelete;cout<<endl;

        if (toDelete == 0)
        {
                return currentUser;
        }
        else if (toDelete > totalPosts) //requested number does not exist
        {
                cout<<"Error: Post "<<toDelete<<" does not exist"<<endl;
                return currentUser;
        }

        //remove post and update wall
        userWall->removePostByIndex(toDelete-1);
        currentUser.setWall(userWall);

        //Decrement field "number of posts"
        currentUser = decrementPost(currentUser);

        cout<<"---Post "<<toDelete<<" Successfully Deleted---"<<endl;

        return currentUser;
}

//Edit requested field's information of user
//Name can always change (marriage, or when you get a passport you get the chance to change your name)
//Age can also change.
//Password can be changed to user's desired new password
//Number of posts is set, so that cannot change
user editField(user currentUser, string field, int fieldToEdit)
{
        //int fieldToEdit already stores the array position of the field that needs to be changed

        //Stores new information
        string newInfo;
        
        cout<<field<<" Edit: "<<endl;
        cout<<"-----------------------------------------------------------------"<<endl<<endl;
        cout<<"Please enter the new information for this field:"<<endl;
        cout<<"New "<<field;cout<<": ";cin>>newInfo;cout<<endl;
        cout<<"-----------------------------------------------------------------"<<endl<<endl;

        //Update user information
        currentUser.setUserInfo(newInfo, fieldToEdit);

        cout<<"---Changes Saved---"<<endl;

        return currentUser;

}

//Displays menu to edit user's information
user editInformation(user currentUser)
{
        cout<<endl;
        //Show user's information
        currentUser.printUserInfo();

        string choice;

        cout<<"----------------"<<endl;
        cout<<"| Edit Account |"<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;
        cout<<"Type \"EXIT\" or \"BACK\" anytime to return to the menu"<<endl<<endl;
        cout<<"Select which field you want to edit:"<<endl;
        cout<<"1) First Name"<<endl;
        cout<<"2) Last Name"<<endl;
        cout<<"3) Age"<<endl;
        cout<<"4) Password"<<endl;
        cout<<"-----------------------------------------------------------------"<<endl<<endl;

        while (true)
        {
                cout<<"Input: ";cin>>choice;cout<<endl;

                if(choice == "1")
                {
                        currentUser = editField(currentUser, "First Name", 0);
                        break;
                }
                else if (choice == "2")
                {
                        currentUser = editField(currentUser, "Last Name", 1);
                        break;
                }
                else if (choice == "3")
                {
                        currentUser = editField(currentUser, "Age", 2);
                        break;
                }
                else if (choice == "4")
                {
                        currentUser = editField(currentUser, "Password", 3);
                        break;
                }
                else if (choice == "EXIT" || choice == "exit" || choice == "Exit" ||
                                 choice == "BACK" || choice == "back" || choice == "Back")
                {
                        return currentUser;
                }
                else
                {
                        cout<<"Error: invalid input"<<endl<<endl;
                        cin.ignore(256, '\n');
                }

        }

        return currentUser;

}

//Account menu for when the user logs in
void accountMenu(userList *list, string name, string fName, string lName, string password)
{
        //Get current user
        user currentUser = list->returnUser(fName, lName, password);

        char dump;

        string choice;
        bool menuLoop = true;

        while (menuLoop == true)
        {
                cout<<left;
                cout<<"Current User: "<<name<<endl;
                cout<<"*---------------------------------------------------------*"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|               Welcome to your Account!                  |"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Please select an action to perform:"                                                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 1) View your wall"                                                                                               <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 2) View your account information"                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 3) Edit your account information"                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 4) Create a post"                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 5) Delete a post"                                                                                                <<"|"<<endl;            
                cout<<"|"<<setw(57)<<" Enter \"Logout\" to return to the menu"                                                  <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Please make sure that all your actions follow"                                   <<"|"<<endl;
                cout<<"|"<<setw(57)<<" the terms and conditions of Sherbook"                                                    <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"*---------------------------------------------------------*"                                             <<endl<<endl;
                
                while (true)
                {
                        cout<<"Input: ";cin>>choice;

                        if (choice == "1")
                        {
                                cout<<endl;
                                currentUser.printWall(); cout<<endl<<"Enter any key to return to the account menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
                                break;
                        }
                        else if (choice == "2")
                        {
                                cout<<endl;
                                currentUser.printUserInfo(); cout<<endl<<"Enter any key to return to the account menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
                                break;
                        }
                        else if (choice == "3")
                        {
                                currentUser = editInformation(currentUser); cout<<endl<<"Enter any key to return to the account menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
                                break;
                        }       
                        else if (choice == "4")
                        {
                                currentUser = createPost(currentUser, name); cout<<endl<<"Enter any key to return to the account menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
                                break;
                        }       

                        else if (choice == "5")
                        {
                                currentUser = deletePost(currentUser);
                                cout<<endl<<"Enter any key to return to the account menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
                                break;
                        }
                        else if (checkCancel(choice))
                        {
                                menuLoop = false;
                                break;
                        }
                        else
                        {
                                cout<<endl<<"Error: invalid input"<<endl<<endl;
                                cin.ignore(256,'\n');
                        }

                }

        }

        cout<<"---Logout Successful---"<<endl<<endl;

        list->overwrite(currentUser, fName, lName, password);
}

void displayAllUsers(userList *list)
{
        list->printAllUsers();
}

void deleteUser(userList *list)
{

        int toDelete;

        displayAllUsers(list);

        cout<<"Please select which user to delete"<<endl;
        cout<<"Or enter '0' to go back to the menu: "<<endl;
        cout<<"Delete user ";cin>>toDelete;cout<<endl;

        if (toDelete == 0)
        {
                return;
        }
        else if (toDelete > list->returnTotalUsers())
        {
                cout<<"Error: User "<<toDelete<<" does not exist"<<endl;
                return;
        }

        list->removeUserByIndex(toDelete-1);

        cout<<"---User "<<toDelete<<" Sucessfully Deleted---"<<endl;

        return;

}

//For fun only
void cookies()
{

                        cout<<"   ___  _____  _____  _  _  ____  ____  ___  /  "<<endl;
                        cout<<"  / __)(  _  )(  _  )( )/ )(_  _)( ___)/ __) )( "<<endl;
                        cout<<" ( (__  )(_)(  )(_)(  )  (  _)(_  )__)  __    / "<<endl;
                        cout<<"   ___)(_____)(_____)(_) _)(____)(____)(___/ () "<<endl;
                        cout<<"                                        .-'''''-.        "<<endl;
                        cout<<"                                |'-----'|        "<<endl;
                        cout<<"                                |-.....-|        "<<endl;
                        cout<<"                                |       |        "<<endl;
                        cout<<"                                |       |        "<<endl;
                        cout<<"               _,._             |       |        "<<endl;
                        cout<<"          __.o`   o`.-.         |       |        "<<endl;
                        cout<<"       .-O o `.-.o   O )_,._    |       |        "<<endl;
                        cout<<"      ( o   O  o )--.-`O   o.-. `'-----'`        "<<endl;
                        cout<<"      '--------'  (   o  O    o)                         "<<endl;
                        cout<<"                    `----------`                         "<<endl;

                        cout<<"Enjoy some cookies and milk!"<<endl;
                        char dump;
                        cout<<"Enter any key to finish your break";cin>>dump;cout<<endl;
                        cin.ignore(256,'\n');
 
}

//Menu for admin
void adminMenu(userList *list)
{

        bool menuLoop = true;
        string choice;
        char dump;


        while (menuLoop)
        {

                cout<<left;
                cout<<"*---------------------------------------------------------*"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|                 Administration Menu                     |"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" This is the administration menu"                                                                 <<"|"<<endl;
                cout<<"|"<<setw(57)<<" You can access and modify information for the "                                  <<"|"<<endl;
                cout<<"|"<<setw(57)<<" entire Sherbook"                                                                                                 <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" and password"                                                                                                    <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Please don't abuse this power"                                                                   <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Please select an action to perform:"                                                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 1) View all users"                                                                                               <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 2) Delete a user"                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 3) Cookies...?"                                                                                                  <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Enter \"Q\" to Quit and return to main menu"                                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"*---------------------------------------------------------*"                                             <<endl<<endl;

                while (true)
                {
                        cout<<"Input: ";cin>>choice;

                        if (choice == "1")
                        {
                                cout<<endl;
                                displayAllUsers(list); cout<<endl<<"Enter any key to return to the admin menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
                                break;
                        }
                        else if (choice == "2")
                        {
                                cout<<endl;
                                deleteUser(list); cout<<endl<<"Enter any key to return to the admin menu: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
                                break;
                        }
                        else if (choice == "3")
                        {
                                cookies();
                                break;
                        }       

                        else if (choice == "Q" || choice == "q" ||
                                         choice == "Quit" || choice == "QUIT" || choice == "quit")
                        {
                                menuLoop = false;
                                return;
                        }

                        else
                        {
                                cout<<endl<<"Error: invalid input"<<endl<<endl;
                                cin.ignore(256,'\n');
                        }

                }
        }
}

//Login function
void logIn(userList *list)
{

        bool isBack = false;

        bool isAdmin = false;

        bool isUser = false;

        string fName;
        string lName;
        string fullName;
        string password;

        char dump;

        while (true) //loop allows user to have multiple attempts to login
        {
                cout<<"----------"<<endl;
                cout<<"| Log In |"<<endl;
                cout<<"-----------------------------------------------------------------"<<endl<<endl;
                cout<<"Type \"EXIT\" or \"BACK\" anytime to return to the menu"<<endl;
                cout<<" "<<endl;                                                                                                //Checks if user wants to return back to menu
                cout<<"First Name:   ";cin>>fName;                                                              isBack = checkCancel(fName); if (isBack == true) break;
                cout<<"Last Name:    ";cin>>lName;                                                              isBack = checkCancel(lName); if (isBack == true) break;
                cout<<"Password:     ";cin>>password;                                                   isBack = checkCancel(password); if (isBack == true) break;

                //make full name
                fullName = constructName(fName, lName);

                //check if user exists
                isUser = list->containsUser(fName, lName, password);

                if (isUser == true)
                {
                        //If user exists, break from loop
                        break;
                }

                //checks for admin login
                if (fullName == "admin admin" || fullName == "Admin Admin" || fullName == "ADMIN ADMIN" ||
                        password == "admin" || password == "Admin" || password == "ADMIN")
                {
                        isAdmin = true;
                        break;
                }

                cout<<"-----------------------------------------------------------------"<<endl<<endl;

                cout<<"Error: Username and password do not match or user not found"<<endl;
                cout<<"       Please check you spelled the information correctly"<<endl;
                cout<<"       or return to the main menu and create a new account"<<endl<<endl;

                cout<<"Enter any key to continue: ";cin>>dump;cin.ignore(256,'\n');cout<<endl<<endl;

        }

        //If user wants to go back, return
        if (isBack == true) return;

        //If user is admin, go to admin menu
        if (isAdmin) adminMenu(list);
        else
        {
                cout<<endl<<"---Login Successful---"<<endl<<endl;
                cout<<"Enter any key to continue: ";cin>>dump;cin.ignore(256,'\n');cout<<endl;
                accountMenu(list, fullName, fName, lName, password);
        }
}

//For fun only
void termsAndConditions()
{
                cout<<"*---------------------------------------------------------*"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|                Terms and Conditions!                    |"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Profanities, assult, or other forms of"                                                  <<"|"<<endl;
                cout<<"|"<<setw(57)<<" harrassment are forbidden through post interactions"                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" No explicit material that may be offensive to others"                    <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" You will not user Sherbook to buy or sell animals"                               <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Mythical creatures such as dragons are also animals"                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Selling mythical creatures are also forbidden"                                   <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" By using Sherbook, you will be in constant pursuit"                              <<"|"<<endl;
                cout<<"|"<<setw(57)<<" for cookies"                                                                                                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Most importantly: Have fun!"                                                                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"*---------------------------------------------------------*"                                             <<endl<<endl;

                char dump;
                cout<<"Enter any key to return to the menu: ";cin>>dump;cout<<endl;
                cin.ignore(256,'\n');
                return;
}


int main()
{
        //Make a user list. Constructor will initialize the list
        userList *list = new userList;

        char choice;
        bool choiceLoop;
        bool menuLoop = true;

        while (menuLoop == true)
        {
                choiceLoop = true;

                cout<<left;
                cout<<"*---------------------------------------------------------*"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|              Welcome to Sherbook v.1.0!                 |"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" This is a social network program created by"                                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Stephen Tsung-Han Sher for CS104"                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" If you have already created an account, simply choose"                   <<"|"<<endl;
                cout<<"|"<<setw(57)<<" the login option and log in with your username"                                  <<"|"<<endl;
                cout<<"|"<<setw(57)<<" and password"                                                                                                    <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" If you are new, feel free to create an account!"                                 <<"|"<<endl;
                cout<<"|"<<setw(57)<<" It is completely free!"                                                                                  <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Donations in the form of good grades"                                                    <<"|"<<endl;
                cout<<"|"<<setw(57)<<" are always welcomed"                                                                                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Please select an action to perform:"                                                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 1) Log in"                                                                                                               <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 2) Create new account (FREE!)"                                                                   <<"|"<<endl;
                cout<<"|"<<setw(57)<<" 3) Read terms and conditions"                                                                    <<"|"<<endl;
                cout<<"|"<<setw(57)<<" Enter \"Q\" to Quit"                                                                                             <<"|"<<endl;
                cout<<"|"<<setw(57)<<" "                                                                                                                                <<"|"<<endl;
                cout<<"*---------------------------------------------------------*"                                             <<endl<<endl;

                choiceLoop = true;
                while (choiceLoop == true)
                {
                        cout<<"Input: ";cin>>choice;

                        if (choice == '1')
                        {
                                logIn(list);
                                choiceLoop = false;
                        }
                        else if (choice == '2')
                        {
                                createAccount(list);
                                choiceLoop = false;
                        }
                        else if (choice == '3')
                        {
                                termsAndConditions();
                                choiceLoop = false;
                        }
                        else if (choice == 'q' || choice == 'Q')
                        {
                                choiceLoop = false;
                                menuLoop = false;
                        }
                        else
                        {
                                cin.ignore(256,'\n');
                                cout<<endl<<"Error: Invalid input"<<endl<<endl;
                        }
                }

        }

        //Destructor will output userlist into a text file
        delete list;

        cout<<"---Program End---"<<endl;
        return 0;
}
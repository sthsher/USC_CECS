#include <iostream>
#include <fstream>
#include <string>
using namespace std;

wall::wall()
{
        postPtr = new LListSet<wallPost>;
}

//destructor: writes on the file
wall::~wall()
{
        //Makes a temp post to write with
        wallPost tempPost;

        ofstream fout;

        fout.open("user_info_file.txt", ios::app);
        
        LListElement<wallPost> *tempElement;

        //goes through all the elements of the wall and writes them
        for (tempElement = postPtr->returnStart(); tempElement != NULL; tempElement = tempElement->returnNext())
        {
                tempPost = tempElement->returnData();
                fout<<tempPost.returnAuthor()<<endl;
                fout<<tempPost.returnPost()<<endl;
        }

        fout.close();



}

void wall::addPost(wallPost newPost)
{
        //cout<<"Adding post"<<endl;
        postPtr->add(newPost);  
}

wallPost wall::returnPostByIndex(int index)
{
        LListElement<wallPost> *temp = postPtr->returnStart();

        for (int i = 0; i < index; ++i)
        {
                temp = temp->returnNext();
        }

        return (temp->returnData());
}

void wall::removePostByIndex(int index)
{
        LListElement<wallPost> *temp = postPtr->returnStart();

        for (int i = 0; i < index; ++i)
        {
                temp = temp->returnNext();
        }

        postPtr->removePtr(temp);
}

void wall::printAllPosts() const
{
        int counter = 1;
        wallPost tempPost;

        LListElement<wallPost> *tempElement;

        //Goes through the posts and prints them
        for (tempElement = postPtr->returnStart(); tempElement != NULL; tempElement = tempElement->returnNext(), counter++)
        {
                tempPost = tempElement->returnData();
                tempPost.printPost(counter);
                cout<<endl;
        }
}
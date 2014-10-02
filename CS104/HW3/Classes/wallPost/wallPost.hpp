#include <iostream>
using namespace std;

wallPost::wallPost()
{
        author = "";
        post = "";
}

wallPost::~wallPost()
{

}

void wallPost::setAuthor(const string &a)
{
        author = a;
}

void wallPost::setPost(const string &p)
{
        post = p;
}

string wallPost::returnAuthor()
{
        return author;
}

string wallPost::returnPost()
{
        return post;
}

void wallPost::printPost(int postNum) const
{

        cout<<"--------------------------------------------------"<<endl;
        cout<<"Post "<<postNum<<endl;
        cout<<"By:  "<<author<<endl<<endl;
        cout<<post<<endl;
        cout<<"--------------------------------------------------"<<endl;

        return;

}
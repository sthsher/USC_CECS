#ifndef wallPost_H_
#define wallPost_H_

using namespace std;

class wallPost
{
        public:
                wallPost();
                ~wallPost();

                void setAuthor(const string &a);                        //sets the author
                void setPost(const string &p);                          //sets the post

                string returnAuthor();
                string returnPost();

                void printPost(int postNum) const;              //postNum is just a temporary integer to show the progression of posts.


        private:
                string author;
                string post;


};

#include "wallPost.hpp"


#endif //wallPost_H_
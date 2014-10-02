#ifndef wall_H_
#define wall_H_

#include "../LList/Set/LListSet.h"
#include "../wallPost/wallPost.h"

using namespace std;

class wall
{
        public:
                wall();
                ~wall();

                void addPost(wallPost newPost);                         //adds a new post with class wallPost

                wallPost returnPostByIndex(int index);          //returns post by index
                void removePostByIndex(int index);                      //removes post by index

                void printAllPosts() const;

        private:
                LListSet<wallPost> *postPtr;

};

#include "wall.hpp"


#endif //wall_H_
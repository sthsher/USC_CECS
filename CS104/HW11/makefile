CC = g++-4.8
CFLAGS = -g
STUFF = postComment.o wallPost.o wall.o user.o userKey.o userList.o Sherbook.o

all: $(STUFF)
	$(CC) $(CFLAGS) $(STUFF) -o Sherbook

postComment.o: Classes/postComment/postComment.h Classes/postComment/postComment.cpp
	$(CC) $(CFLAGS) -c Classes/postComment/postComment.cpp

wallPost.o: Classes/wallPost/wallPost.h Classes/postComment/postComment.h Classes/wallPost/wallPost.cpp
	$(CC) $(CFLAGS) -c Classes/wallPost/wallPost.cpp

wall.o: Classes/wall/wall.h Classes/wallPost/wallPost.h Classes/postComment/postComment.h Classes/wall/wall.cpp
	$(CC) $(CFLAGS) -c Classes/wall/wall.cpp

user.o: Classes/user/user.h Classes/wall/wall.h Classes/wallPost/wallPost.h Classes/postComment/postComment.h Classes/user/user.cpp
	$(CC) $(CFLAGS) -c Classes/user/user.cpp

userKey.o: Classes/userKey/userKey.h
	$(CC) $(CFLAGS) -c Classes/userKey/userKey.cpp

userList.o: Classes/userList/userList.h Classes/user/user.h Classes/wall/wall.h Classes/wallPost/wallPost.h Classes/postComment/postComment.h Classes/userKey/userKey.h Classes/userList/userList.cpp
	$(CC) $(CFLAGS) -c Classes/userList/userList.cpp

Sherbook.o: Sherbook.cpp Classes/userList/userList.h Classes/user/user.h Classes/wall/wall.h Classes/wallPost/wallPost.h Classes/postComment/postComment.h
	$(CC) $(CFLAGS) -c Sherbook.cpp

.PHONY: clean

clean:
	rm -rf *o $(STUFF)

CC = g++-4.8
CFLAGS = -g
STUFF = student.o food.o word.o

all: $(STUFF)
	$(CC) $(CFLAGS) student.o Question3/Q3.cpp -o Q3
	$(CC) $(CFLAGS) food.o Question4/Q4.cpp -o Q4
	$(CC) $(CFLAGS) Question5/Q5.cpp -o Q5
	$(CC) $(CFLAGS) word.o Question6/Q6.cpp -o Q6


student.o: Question3/student.h Question3/student.cpp
	$(CC) $(CFLAGS) -c Question3/student.cpp

food.o: Question4/food.h Question4/food.cpp
	$(CC) $(CFLAGS) -c Question4/food.cpp

word.o: Question6/word.h Question6/word.cpp
	$(CC) $(CFLAGS) -c Question6/word.cpp

clean:
	rm -rf *o $(STUFF)

CC = g++-4.8
CFLAGS = -g
STUFF = stringAndFrequency.o

all: $(STUFF)
	$(CC) $(CFLAGS) stringAndFrequency.o Question3/Q3.cpp -o Q3
	$(CC) $(CFLAGS) Question4/Q4.cpp -o Q4
	$(CC) $(CFLAGS) Question5/Q5.cpp -o Q5

stringAndFrequency.o: Question3/stringAndFrequency.h Question3/stringAndFrequency.cpp
	$(CC) $(CFLAGS) -c Question3/stringAndFrequency.cpp

clean:
	rm -rf *o $(STUFF)

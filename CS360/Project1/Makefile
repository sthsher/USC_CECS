# To compile,  type “make all”
# To run,      type “make run”
# To clean up, type “make clean”

SOURCES=Project1.cc
EXECUTABLE=Project1

CC=g++
CFLAGS=-c -Wall -pthread
OBJECTS=$(SOURCES:.cc=.o)
DEPS=$(SOURCES:.cc=.h)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *~ *o $(EXECUTABLE)

run:
	./$(EXECUTABLE)


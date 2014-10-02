CC = g++-4.8

STUFF = calculator

all: $(STUFF)

HW: $(STUFF)
	$(CC) calculator.cpp -o $@

calculator: calculator.cpp
	$(CC) calculator.cpp classes/mathVector/mathVector.cpp classes/sherStack/Stack_Item/stackItem.cpp -o $@

clean:
	rm -rf *o $(STUFF)


CC = g++-4.8

STUFF = HW2Q3 HW2Q6

all: $(STUFF)

HW: $(STUFF)
	$(CC) HW2Q3.cpp -o $@
	$(CC) HW2Q6.cpp -o $@

HW2Q3: HW2Q3.cpp
	$(CC) HW2Q3.cpp -o $@

HW2Q6: HW2Q6.cpp stringLL.cpp
	$(CC) HW2Q6.cpp stringLL.cpp -o $@

clean:
	rm -rf *o $(STUFF)

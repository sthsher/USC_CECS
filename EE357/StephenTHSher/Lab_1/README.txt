Member 1:
Name:		Stephen Tsung-Han Sher
USC ID:		7555500940
USC Email:	tsher@usc.edu

Member 2:
Name:		Colin Cammarano
USC ID:		8085947576
USC Email:	cammaran@usc.edu

Submission for EE357 LAB1:	September 11, 2014

Submission Details:
INITAL, STOPS, LEAVING, ARRIVING are all as given in the skeleton code
There are two message: A welcome message and a message to indicate the final number of people on the bus

Subroutine welc:
	Display welcome message
	Has comments to indicate register and array values

Subroutine init:
	Initializes a1 with ARRIVING
	Initalizes a2 with LEAVING
	Initialzies d4 with STOPS
	subtracts d4 by 1 to take into consideration the last stop does not involve ARRIVING nor LEAVING
	Initializes d1 with INITIAL
	Clears d2

Subroutine loop:
	Moves first ARRIVING to d2, increments a1
	Performs add to d1
	Moves first LEAVING to d2, increments a2
	Performs subtraction to d1
	Decrement d4 (the loop counter / STOPS)
	Loops for remaining values in LEAVING and ARRIVING

	After loop, clears d2
	Adds d1 to d2 (resulting number of people after loop)
	Bit shift right twice (divide by 2 twice, in other words divide by 4) on d2
	Subtracts d2 from d1 to get 3/4ths of remaining people (1/4th leaving)

Subroutine final:
	Moves final message to a1
	Display message
	Display result


When in doubt, read the comments
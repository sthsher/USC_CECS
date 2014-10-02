Stephen Tsung-Han Sher
USC ID: 7555500940
CSCI201 Assignment 1
Professor Miller, M W 8:30AM
Due: Sep 7th, 2014

-----------------------
  Running the program
-----------------------
There are no command line arguments for this program, just run the program directly in eclipse

---------------------
  Using the program  
---------------------
As described in the assignment, inputting "A" when prompted if you are an admin will allow you to use admin mode.
This is case sensitive, therefore "a" will enter you in normal mode, as with any other inputs

When entering number of rows and columns, invalid inputs such as letters will not work and you will be reprompted

Entering anything that contains spaces will be considered invalid:
	eg. 	"4 5"	(space between numbers, only accept one number)
			"4 "	(space after number)
			" 4"	(space before number)

The only known bug is if you press enter multiple times without entering anything, the loop will stack up and output the error messages all at once

	If you press enter a bunch of times and input a valid input, the input will register through

When inputting the characters, you HAVE to follow the format:
	Only one character at a time, separated by spaces
	No leading spaces or trailing spaces

	eg.		"a b c"		This is OK
			"a b c "	NOT OK, trailing space
			" a b c"	NOT OK, leading space
			"abc"		NOT OK, no spaces

That's it. Have fun and enjoy the program!
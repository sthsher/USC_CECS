# This is Python code to solve the problem located at the following site:
# https://projecteuler.net/problem=1

#Get input
print("This program will find the sum of all the numbers between a desired range\nthat are divisible by 3 or 5")
num = raw_input("Entered desired range (exclusive): 0 to ")
# Initialize a variable name sum so that we can figure out the 
# total values at the end
sum = 0

# We're going to loop all the values from 0 all the way to 1000
# At each loop, the variable n will be 0, 1, 2, ...
# We will test to see if divisible by 3 or 5 
for n in range(0,int(num)):

	# At the following line, we're testing to see if n 
	# is divisible by 3. The % symbol represents modulus
	# It will take the number on the left and divide it by the number on the right
	# If there is a remainder, then the number is NOT divisible by the number of the right
	# So if we use the % (modules) and the answer becomes 0, we know that the
	# value on the left is divisible by the value on right
	if n % 3 == 0:
		sum = n + sum
		
	# We're going to do the same test by instead of 3 we use 5.
	# Notice we use an elif (else if) instead of a if. The reason
	# is because we want to test divisible by 3 or 5. If we choose to use
	# an if on the next line, the program could add the sum twice (which for this 
	# problem we don't want). For example, 15 would satisfy being divisible by 3 and 5
	elif n % 5 == 0:
		sum += n

# We have a print() function outside the for loop. This will print the value
# of the variable sum once. If we were to put this line inside the for loop
# it will cause the program to print out the sum at each loop. 
# Not exactly what we want.		
print(sum)
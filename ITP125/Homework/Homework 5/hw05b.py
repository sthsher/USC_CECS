#Generate all the fib numbers below 4000000
fib1 = 1
fib2 = 1

#Running sum
sum = 0

#Loop while less than 4000000
while(fib2 < 4000000):
	#Even case
	if (fib2 % 2 == 0):
		sum += fib2

	#Generate next fib sequence
	temp = fib2
	fib2 += fib1
	fib1 = temp

#Print result
print sum
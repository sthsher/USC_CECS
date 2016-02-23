def PrimeFactors(n):
	x = 2
	while (x * x <= n):
		if (n % x == 0):
			#print x
			n /= x
		else:
			x += 1
	if (n > 1):
		print n

PrimeFactors(600851475143)
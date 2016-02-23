def IsPalindrome(string):
	reverse = string[::-1]
	if (string == reverse):
		return True
	else:
		return False

def AllProducts():
	largest = 0
	#Local greedy: assumes that the two numbers are both within the 900 range
	for i in range(999, 900, -1):
		for j in range(999, 900, -1):
			product = i * j
			productStr = str(product)
			if (IsPalindrome(productStr)):
				largest = max(product, largest)
	if (largest != 0):
		print largest
		return

	#if greedy fails, brute force
	for i in range(999, 99, -1):
		for j in range(999, 99, -1):
			product = i * j
			productStr = str(product)
			if (IsPalindrome(productStr)):
				largest = max(product, largest)
	print largest

AllProducts()
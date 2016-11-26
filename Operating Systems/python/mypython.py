##############################
## Scott Cooper
## CS344 - python assignment
## fall 2016
###############################
import random
import string

##loop to create each file 
for i in range(1,4):
	## unique file names
	file = "fileName" + str(i)
	## open file for writing
	f = open(file, 'w')
	## initialize myString variable
	myString = ""

	## loop through myString adding a new lowercase letter
	## with each iteration
	for j in range(0,10):
		myString += random.choice(string.ascii_lowercase)
	##write string plus newline to file
	f.write(myString + "\n")
	##close file
	f.close()
	##prints the random string
	print(myString)

## 2 random numbers between 1 - 42
## print the numbers
num1 = random.randint(1,42)
num2 = random.randint(1,42)
print(num1)
print(num2)

##determine produt and print
product = num1 * num2
print(product)

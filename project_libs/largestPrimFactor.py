
"""
Problem statement:
The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143 ?

Relevant information:
1) Prime numbers all always odd numbers
2) Prime number cannot be even number because it can be divided by 2
3) Composite numbers are the numbers which are not prime numbers i.e. they have
more than 2 factors
4) 1 is neither prime not composite

Online solution link:
https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
"""

from helpers.helper_methods import *


def problem_3(input_num=None):
	input_number = input_num
	print('Finding largest prime factor for {}'.format(input_num))
	if not input_number:
		print('Please provide input number.')
		return

	largest_prime = 'Error'
	print('sqrt: {}'.format(int(get_sqrt(input_number=input_number))))
	# keep dividing input number until its no longer divisible by 2
	# this reduces the number to a point where it can only be divided by all
	# odd numbers
	print('Input number before: {}'.format(input_number))
	while input_number % 2 == 0:
		input_number = input_number/2

	print('Input number after: {}'.format(input_number))
	# since 1 is neither prime not composite ignore it
	# since we only want to divide the number with odd numbers start with 3
	# all odd numbers are separated by 2 from one another, hence run for loop
	# with hops of 2
	for i in range(3, int(get_sqrt(input_number=input_number))+1, 2):
		while input_number % i == 0:
			print 'Value of i: {}'.format(i)
			largest_prime = i
			input_number = input_number/i

	print('Largest prime factor for {} is {}'.format(input_num, largest_prime))


def main():
	problem_3(input_num=600851475143)


if __name__ == "__main__":
	main()

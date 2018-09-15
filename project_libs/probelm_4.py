# coding=utf-8
"""
Problem statement:
A palindromic number reads the same both ways.
The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
Find the largest palindrome made from the product of two 3-digit numbers

Relevant Information:

"""
from helpers.helper_methods import *


def problem_4():
	palindrome_list = [x*y for x in range(100, 1000) for y in range(100, 1000) if is_palindrome(input_number=str(x*y))]
	print('Palindrome list: {}'.format(palindrome_list))
	print('Length of Palindrome list: {}'.format(len(palindrome_list)))
	biggest_palindrome = find_biggest(input_list=palindrome_list)
	print('Largest palindrome made from product of two 3-digit numbers: {}'.format(biggest_palindrome))


if __name__ == "__main__":
	problem_4()

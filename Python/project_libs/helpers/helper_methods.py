"""
This file contains all the possible helper methods.
"""
import sorting_methods


def input_decorator(func):
	"""
	This is a decorator function for given function func.
	:param func: function to run
	:return: dec_wrapper function
	"""
	def dec_wrapper(*args, **kwargs):
		"""

		:param args: input arguments given to function func
		:arg [0] must be a list
		:arg [1] must be a string or an integer
		:return:
		"""
		input_list = kwargs.get('input_list', [])
		if type(input_list) != list:
			print('Please provide a list')
			return False

		return func(*args, **kwargs)

	return dec_wrapper


@input_decorator
def get_sqrt(input_number):
	"""
	This method returns square root of given number
	:param input_number: input number
	:return: False if nothing given else square root of number
	"""
	return input_number ** 0.5


@input_decorator
def is_palindrome(input_number):
	"""
	This method returns True if given number is a palindrome
	:param input_number: input number
	:return:
	False if nothing given True if given number is palindrome
	"""

	# compare given string against its reverse
	if str(input_number) == str(input_number[::-1]):
		return True

	return False


@input_decorator
def find_biggest(input_list):
	"""
	This method will return us the biggest integer in given input list
	:param input_list: list to find integer in
	:return: False if no integer found else biggest integer
	"""

	# remove duplicates from given list
	unique_input_list = remove_duplicates(input_list=input_list)
	# sort given list
	sorted_input_list = sorting_methods.selection_sort(input_list=unique_input_list)
	print(sorted_input_list)
	return sorted_input_list[-1]


@input_decorator
def remove_duplicates(input_list):
	"""
	This method will remove all the duplicate entries in given input_list
	:param input_list: list to remove duplicates from
	:return: List without duplicates
	"""
	unique_list = []
	print('length of input list: {}'.format(len(input_list)))
	[unique_list.append(x) for x in input_list if x not in unique_list]
	print('length of unique list: {}'.format(len(unique_list)))
	print(unique_list)
	return unique_list

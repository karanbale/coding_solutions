# coding=utf-8
"""
This file will contain all different types of sorting methods
"""

from helpers.sorting_methods import quick_sort
import time


def input_decorator(func):
	"""
	This is a decorator function for given function func.
	:param func: function to run
	:return: dec_wrapper function
	"""

	def dec_wrapper(*args, **kwargs):
		"""

		:param args: arguments given to function func
		:param kwargs: keyword arguments given to function func
		:return: function func
		"""
		input_list = kwargs.get('input_list', [])
		sorted_list = kwargs.get('sorted', True)
		if type(input_list) != list:
			print('Please provide a List')
			return False
		if not sorted_list:
			kwargs['input_list'] = quick_sort(input_list=input_list, low=0, high=len(input_list)-1)

		start_time = time.time()
		# add start time to kwargs to pass it to each func
		kwargs['start_time'] = start_time

		return func(*args, **kwargs)

	return dec_wrapper


def binary_search(input_list, target_element, sorted=True):
	"""

	:param input_list: list in which we would like to search target element
	:param target_element: element to be searched in input list
	:param sorted: input list is sorted or not, default is True (we expect the list to be sorted)
	:return: index of the target element in the input list
	"""


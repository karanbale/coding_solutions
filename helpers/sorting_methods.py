# coding=utf-8
"""
This file will contain all different types of sorting methods
"""

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
		if type(input_list) != list:
			print('Please provide a List')
			return False

		start_time = time.time()
		# add start time to kwargs to pass it to each func
		kwargs['start_time'] = start_time

		return func(*args, **kwargs)

	return dec_wrapper


@input_decorator
def selection_sort(input_list, **kwargs):
	"""
	Insertion sort compares first element against rest of the elements in one pass and moves the highest element towards
	the end, and this is done until all the elements are sorted.
	Insertion sort does not touch elements which were previously sorted.
	:param input_list: list to be sorted
	:param kwargs: keyword arguments, if any
	:return: sorted list
	"""
	for i in range(len(input_list)):
		min_index = i
		for j in range(i + 1, len(input_list)):
			if input_list[min_index] > input_list[j]:
				min_index = j
		# now swap actual values
		input_list[i], input_list[min_index] = input_list[min_index], input_list[i]

	print('func time: {}'.format(time.time() - kwargs.get('start_time')))
	return input_list


@input_decorator
def bubble_sort(input_list, **kwargs):
	"""
	Bubble Sort is the simplest sorting algorithm that works by repeatedly swapping the adjacent elements if they are
	in wrong order.

	Example:
	First Pass:
	( 5 1 4 2 8 ) –> ( 1 5 4 2 8 ), Here, algorithm compares the first two elements, and swaps since 5 > 1.
	( 1 5 4 2 8 ) –>  ( 1 4 5 2 8 ), Swap since 5 > 4
	( 1 4 5 2 8 ) –>  ( 1 4 2 5 8 ), Swap since 5 > 2
	( 1 4 2 5 8 ) –> ( 1 4 2 5 8 ), Now, since these elements are already in order (8 > 5), algorithm does not swap
	them.

	Second Pass:
	( 1 4 2 5 8 ) –> ( 1 4 2 5 8 )
	( 1 4 2 5 8 ) –> ( 1 2 4 5 8 ), Swap since 4 > 2
	( 1 2 4 5 8 ) –> ( 1 2 4 5 8 )
	( 1 2 4 5 8 ) –>  ( 1 2 4 5 8 )
	Now, the array is already sorted, but our algorithm does not know if it is completed. The algorithm needs one whole
	pass without any swap to know it is sorted.

	:param input_list: list to be sorted
	:param kwargs: keyword arguments, if any
	:return: sorted list
	"""

	# run for loop until end of the list
	for run_loop in range(0, len(input_list)):
		# start iterating using current index
		for current_index in range(0, len(input_list)):
			# if not end of the list, update next index
			if current_index+1 != len(input_list):
				next_index = current_index + 1
			# break when we reach end of the list, to go to next pass of the outer for loop
			else:
				break
			# if current value is > next value, swap them and go to next pair
			if input_list[current_index] > input_list[next_index]:
				input_list[current_index], input_list[next_index] = input_list[next_index], input_list[current_index]

	print('func time: {}'.format(time.time() - kwargs.get('start_time')))
	return input_list


@input_decorator
def insertion_sort(input_list, **kwargs):
	"""

	:param input_list: list to be sorted
	:param kwargs: keyword arguments, if any
	:return: sorted list
	"""
	max_length = len(input_list)
	for curr_index in range(1, max_length):
		key = input_list[curr_index]
		prev_index = curr_index - 1

		while prev_index >= 0 and key < input_list[prev_index]:
			# swap bigger element from prev index with current index element
			input_list[prev_index + 1] = input_list[prev_index]
			# start rolling backwards and comparing current index with all elements in sorted-sub list
			prev_index -= 1

		input_list[prev_index + 1] = key

	print('func time: {}'.format(time.time() - kwargs.get('start_time')))
	return input_list


@input_decorator
def merge_sort(input_list, left_index, right_index, charact='Error', **kwargs):
	"""
	#TODO: To complete
	:param input_list: list to be sorted
	:param kwargs: keyword arguments, if any
	:return:
	"""
	print('******************')
	print('Side: {}'.format(charact))
	print('input list: {}'.format(input_list))
	middle_index = ((left_index + right_index) / 2)
	print('LI: {} RI: {} MI: {}'.format(left_index, right_index, middle_index))

	def merge(input_list, left_index, middle_index, right_index):
		return

	print('Left list: {}'.format(input_list[left_index:middle_index]))
	print('Right list: {}'.format(input_list[middle_index:right_index]))
	print('******************')

	if left_index < right_index:
		merge_sort(input_list=input_list, left_index=left_index, right_index=middle_index, charact='Left')
		merge_sort(input_list=input_list, left_index=middle_index+1, right_index=right_index, charact='right')
		# merge(input_list=input_list, left_index=left_index, middle_index=middle_index, right_index=right_index)


@input_decorator
def partition(input_list, low_index, high_index, **kwargs):
	"""

	:param input_list: list to be sorted
	:param low_index: lowest index of input list
	:param high_index: highest index of input list
	:param kwargs: keyword arguments, if any
	:return: partitioned list index
	"""

	# point to the last element of the list i.e. -1
	i = (low_index - 1)
	# take last element of the list as pivot element to search against
	pivot = input_list[high_index]
	print('******************')
	print('Input list: {}'.format(input_list))
	print('low index: {}'.format(low_index))
	print('high index: {}'.format(high_index))
	print('Pivot: {}'.format(pivot))

	for j in range(low_index, high_index):
		# if pivot element is greater than or equal to current element, move on to next element comparison after
		# swapping these two elements
		if input_list[j] <= pivot:
			i += 1
			print('i: {} j: {}'.format(i, j))
			print('swapping {} and {}'.format(input_list[i], input_list[j]))
			print('******************')
			input_list[i], input_list[j] = input_list[j], input_list[i]
		# if pivot element is smaller than current element, do nothing

	# as a last step, swap input_list[i+1] with input_list[high_index] or pivot
	input_list[i+1], input_list[high_index] = input_list[high_index], input_list[i+1]

	return i+1


@input_decorator
def quick_sort(input_list, low, high, **kwargs):
	"""

	:param input_list: input list to be sorted
	:param low: lowest index of input list
	:param high: highest index of input list
	:param kwargs: keyword arguments if any
	:return: sorted list

	Relevant information:
	https://www.geeksforgeeks.org/quick-sort/
	"""
	if low < high:

		partition_index = partition(input_list=input_list, low_index=low, high_index=high)
		print('Partition index: {}'.format(partition_index))
		quick_sort(input_list=input_list, low=low, high=partition_index-1)
		quick_sort(input_list=input_list, low=partition_index+1, high=high)

	print(input_list)

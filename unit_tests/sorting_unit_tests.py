from helpers import sorting_methods
import time

input_list = [[1, 5, 3, 5, 6, 7, 99], [5, 1, 4, 3, 8, 99], [1, 1, 1, 1, 1, 1], [5, -1, 4, 3, 8, 99], [12, 11, 13, 5, 6],
              None, [], [1, 2, 3, 4, 5], [10, 7, 8, 9, 1, 5]]


def sorting_ut():
	for test_list in input_list:
		print('**********************************')
	# 	print('Input list before sorting:       {}'.format(test_list))
	# 	print('Input list after selection sort: {}'.format(sorting_methods.selection_sort(input_list=test_list)))
		print('Input list after bubble sort:    {}'.format(sorting_methods.bubble_sort(input_list=test_list)))
	# 	print('Input list after insertion sort: {}\n'.format(sorting_methods.insertion_sort(input_list=test_list)))
	#	print('Input list after merge sort:     {}'.format(sorting_methods.merge_sort(input_list=test_list)))
		print('**********************************\n\n')
	# input_list = [10, 7, 8, 9, 1, 5]
	# print('Merge sort: {}'.format(sorting_methods.quick_sort(input_list=input_list, low=0,
    #	                                                         high=len(input_list)-1)))


sorting_ut()

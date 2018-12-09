
def quick_sort(input_list, low, high):
	"""
	
	:param input_list: input list that needs to be sorted
	:return: sorted list
	"""
	if low < high:
		# take low and high indices of the input_list
		# partition the input_list and sort, assuming pivot element is highest element
		pivot_idex = partition(input_list=input_list, low_index=low, high_index=high)
		# get the index of pivot element run quick_sort on elements smaller than pivot element
		print('sorting items larger than pivot element. pivot index: {}'.format(pivot_idex))
		quick_sort(input_list=input_list, low=low, high=pivot_idex-1)
		# get the index of pivot element, run quick_sort on elements bigger than pivot element
		print('sorting items larger than pivot element. pivot index: {}'.format(pivot_idex))
		quick_sort(input_list=input_list, low=pivot_idex+1, high=high)
	
	return input_list
	
def partition(input_list, low_index, high_index):
	"""
	
	:param input_list:
	:param low_index:
	:param high_index:
	:return:
	"""
	# take pivot index as the last item
	pivot_index = low_index - 1
	# save pivot element
	pivot_element = input_list[pivot_index]
	
	# since nth element is the pivot element of input list,
	# we must iterate over input list from 0 to n-1
	for index in range(low_index, high_index-1):
		# compare input list elements with pivot element
		# if pivot element is bigger than input_list's element, swap them.
		if input_list[index] <= pivot_element:
			pivot_index += 1
			print('swapping: {} with {}'.format(input_list[index], input_list[pivot_index+1]))
			input_list[index], input_list[pivot_index] = input_list[pivot_index], input_list[index]
	print('pivot_index after: {}'.format(pivot_index))
	input_list[pivot_index+1], input_list[high_index] = input_list[high_index], input_list[pivot_index+1]
	#print 'input list: {}\n'.format(input_list)
	return pivot_index



#input_list = [[1, 5, 3, 5, 6, 7, 99], [5, 1, 4, 3, 8, 99], [1, 1, 1, 1, 1, 1], [5, -1, 4, 3, 8, 99], [12, 11, 13, 5, 6],
#              None, [], [1, 2, 3, 4, 5], [10, 7, 8, 9, 1, 5]]

input_list = [[10, 80, 30, 90, 40, 50, 70]]


def sorting_ut():
	for test_list in input_list:
		print('**********************************')
	# 	print('Input list before sorting:       {}'.format(test_list))
	# 	print('Input list after selection sort: {}'.format(sorting_methods.selection_sort(input_list=test_list)))
	# 	print('Input list after bubble sort:    {}'.format(sorting_methods.bubble_sort(input_list=test_list)))
	# 	print('Input list after insertion sort: {}\n'.format(sorting_methods.insertion_sort(input_list=test_list)))
	#	print('Input list after merge sort:     {}'.format(sorting_methods.merge_sort(input_list=test_list)))
	# input_list = [10, 7, 8, 9, 1, 5]
		print('Merge sort: {}'.format(quick_sort(input_list=test_list, low=0, high=len(test_list)-1)))
		print('**********************************\n\n')


sorting_ut()

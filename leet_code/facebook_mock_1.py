"""
Facebook logo stickers cost $2 each from the company store.
i have an idea.
I want to cut up the stickers and use the letters to make another words/phrases.
A facebook logo sticker contains only the word "facebook", in all lower-case letters.

Write a function that, given a string consisting of a word or words made
up of letters from the work 'facebook' outputs an integer with the number of
stickers I will need to buy.

e.g.
get_num_stickers('coffee kebab') => 3
get_num_stickers('book') => 1
get_num_stickers('ffacebook') => 2

You can assume the input you are passed is valid, that is, does not contain
any non-'facebook' letters and the only potential non-letter characters in
the string are spaces
"""


def get_num_stickers(input_phrase=None):
	if not input_phrase or not isinstance(input_phrase, str):
		return 0
	
	# remove all the spaces and join the word
	input_phrase = ''.join(input_phrase.split(' '))
	
	# it will over-write duplicate keys
	letter_count_dict = {x:0 for x in input_phrase}
	
	# take letter count of each letter
	for letter in input_phrase:
		letter_count_dict[letter] += 1
	
	temp_dict = letter_count_dict.pop('o')
	o_count = round(temp_dict/2)
	other_count = max(letter_count_dict.values())
	
	return o_count if o_count > other_count else other_count


print(get_num_stickers('coffee kebab'))
print(get_num_stickers('book'))
print(get_num_stickers('ffacebook'))
print(get_num_stickers('oooooooooo ffff'))
# coding=utf-8
"""
A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone.
The frog can jump on a stone, but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the
river by landing on the last stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.

If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog
can only jump in the forward direction.

Note:

The number of stones is ≥ 2 and is < 1,100.
Each stone's position will be a non-negative integer < 2**31.
The first stone's position is always 0.
Example 1:

[0,1,3,5,6,8,12,17]

There are a total of 8 stones.
The first stone at the 0th unit, second stone at the 1st unit,
third stone at the 3rd unit, and so on...
The last stone at the 17th unit.

Return true. The frog can jump to the last stone by jumping
1 unit to the 2nd stone, then 2 units to the 3rd stone, then
2 units to the 4th stone, then 3 units to the 6th stone,
4 units to the 7th stone, and 5 units to the 8th stone.
Example 2:

[0,1,2,3,4,8,9,11]

Return false. There is no way to jump to the last stone as
the gap between the 5th and 6th stone is too large.
"""

import json

class Solution(object):
	def canCross(self, stones):
		"""
		:type stones: List[int]
		:rtype: bool
		"""
		if not isinstance(stones, list) or len(stones) < 2 or len(stones) > 1100 or stones[0] != 0:
			return False
		jump_dict = {key:[] for key in stones}
		jump_dict[0] = [1]
		print('stones: {}'.format(stones))
		print('dict: {}'.format(jump_dict))
		for x in range(0, len(stones) - 1):
			current_difference = stones[x + 1] - stones[x]
			possible_jumpsizes = [current_difference-1, current_difference, current_difference+1]
			print('\nCurrent element: {}'.format(stones[x]))
			print('jumpsize: {}'.format(current_difference))
			print('possible jumps: {}'.format(possible_jumpsizes))
			for js in possible_jumpsizes:
				if js+stones[x] in jump_dict.keys() and current_difference > 0:
					jump_dict[js+stones[x]].append(js)
			print('new dict: {}'.format(jump_dict))
		return True if jump_dict[stones[-1]] > 0 else False


def stringToIntegerList(input):
	return json.loads(input)


def main():
	import sys
	def readlines():
		for line in sys.stdin:
			yield line.strip('\n')
	
	lines = readlines()
	while True:
		try:
			line = lines.next()
			stones = stringToIntegerList(line)
			
			ret = Solution().canCross(stones)
			
			out = (ret)
			print out
		except StopIteration:
			break


if __name__ == '__main__':
	main()
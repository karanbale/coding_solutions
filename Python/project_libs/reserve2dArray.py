# coding=utf-8
"""
Language: Python 3.5+

Create unit tests to test the function `reserve_2d_array`.

Assume `reserve_2d_array` will be implemented by another developer.

- Document any assumptions
- Write code that can be executed (i.e. no syntax, import, nor logical errors)
- The style of your code will also be evaluated
"""

from typing import List
import unittest

def reserve_2d_array(rows: int, columns: int) -> List[bytes]:
    """
    Create a list of bytes given a number of rows and a number of columns
    where each element of the 2D array is zero

    For example, given rows = 2, columns = 3:
    [
        [0x00, 0x00, 0x00],
        [0x00, 0x00, 0x00]
    ]

    :raise: ValueError if rows or columns is less than zero
    """

    if rows < 0 or columns < 0:
        raise ValueError
    
    if rows == 0 or columns == 0:
        raise IndexError

    # outputArray = [lambda y: [lambda x: 0 for x in columns] for y in rows]
    outputArray = [[ 0 for y in range(columns)] for x in range(rows)]

    return outputArray

    # Assume another developer will provide implementation

    # raise NotImplementedError


"""
Write unit tests for `reserve_2d_array`.

If needed, create any helper functions, classes, etc. to improve simplicity.
"""

class TestSum(unittest.TestCase):

    def setup(self, parameter_list):
        """
        docstring
        """
        self.rows = 0
        self.column = 0

    def test_list_int(self):
        """
        Test that it can sum a list of integers
        """
        self.row = 2
        self.column = 3
        outputArray = reserve_2d_array(rows=self.row, columns=self.column)
        self.assertListEqual(outputArray, [[0x0, 0x0, 0x0], [0x0, 0x0, 0x0]])

    def test_negative_inputs(self):
        """
        Test if we can send negative inputs
        """
        self.row = -1
        self.column = -3
        self.assertRaises(ValueError, reserve_2d_array, rows=self.row, columns=self.column)

    def test_zero_inputs(self):
        """
        Test if we can send inputs with 0 values
        """
        self.row = 0
        self.column = 0
        self.assertRaises(IndexError, reserve_2d_array, rows=self.row, columns=self.column)

if __name__ == '__main__':
    unittest.main()
    # print(reserve_2d_array(4,3))


"""
Language: Python 3.5+

Given a list of names, write functions to check constraints.

- Document any assumptions
- Write code that can be executed (i.e. no syntax, import, nor logical errors)
- The style of your code will also be evaluated
"""

NAMES = [
    "test_logger_2",
    "test_logger_1_optional_suffix",
    "test_logger_1_another_optional_suffix",
    "test_updater_4",
    "test_updater_1",
]

"""
You are given a list of names.

Implement a function for each problem:

    1. Ensure names follow the format: "test_<product name>_<integer ID>_<optional suffix>"
        - A product name only contains letters (no underscores)
        - An optional suffix may be optionally excluded from the name

    2. For all names, ensure integer ID is greater than 0

    3. Ensure there are no duplicate names

If there is a violation, then the function should return False, otherwise, return True.
If needed, create any helper functions, classes, etc. to improve simplicity.
"""


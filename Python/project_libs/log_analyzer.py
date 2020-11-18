# coding=utf-8
"""
Following assumptions are made while writing this code:
Assumptions:
1. Each line beings with a timestamp that looks like this: YYYY-MM-DD HR:MIN:SEC,
2. Find a pattern given as an input string in our log files with following conditions:
    1. If given pattern is present in current string AND current string starts with keywords “response” or “request”
        1. If current string contains additional string “severity’:’error”
    2. If a current line starts with keyword “Traceback”, then include all the lines, until next line that begins
    with a timestamp is found.
        1. The line that starts with keyword “Traceback” will not have any timestamp in it.
3. all the files to be searched are present in current working directory.
"""

from abc import ABCMeta, abstractmethod
import os
import re
from argparse import *



TIMESTAMP_PATTERN = '^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}'
OUTPUT_FILE = 'output_file.txt'

class LogAnalyzer(object):
	
	__metaclass__ = ABCMeta

	def __init__(self, *args, **kwargs):
		self.filename=kwargs.pop('filename')
		self.pattern=kwargs.pop('search_pattern')
		print 'filename: {}'.format(self.filename)
		print 'pattern: {}'.format(self.pattern)
		print 'filename: {}'.format(type(self.filename))
		print 'pattern: {}'.format(type(self.pattern))

	"""
	Method to get all the files matching with filename argument
	"""
	def get_all_matching_files(self):
		print 'Current working directory is: {}'.format(os.getcwd())
		print 'Files in current working directory: {}'.format(os.listdir(os.getcwd()))
		if self.filename == '*':
			print 'Going to search in all files.'
			return os.listdir(os.getcwd())
		print 'searching for filename: {}'.format(self.filename)
		matching_files = filter(lambda x: not x.find(self.filename.strip('*')), os.listdir(os.getcwd()))
		return matching_files
	
	@staticmethod
	def get_patterns_from_file(filename, input_pattern=[]):
		traceback_found = False
		if not filename or not input_pattern:
			print 'no file/pattern given. nothing to search for.'
			return
		
		with open(filename, 'r') as fp:
			for line in fp.readlines():
				# ignore any empty strings, next line characters etc
				if line in ('', '/n', 'r', ' '):
					continue
				if line.startswith('Traceback'):
					# we've found a traceback, and this is its first line
					traceback_found = True
					# save this line to output file and move on to next line
					with open(OUTPUT_FILE, 'a') as op_fp:
						op_fp.write(line)
						continue
				# if line does not beging with a timestamp and we have found a traceback, save the line to output file
				# this line is likely the continuation from traceback we recently found
				if not re.search(pattern=TIMESTAMP_PATTERN, string=line) and traceback_found:
					# save this line to output file and move on to next line
					with open(OUTPUT_FILE, 'a') as op_fp:
						op_fp.write(line)
						continue
				# if line begins with a timestamp means, traceback could have finished
				if re.search(pattern=TIMESTAMP_PATTERN, string=line):
					# stop traceback logging activity
					traceback_found = False
					temp_line = re.split(pattern=TIMESTAMP_PATTERN, string=line)
					# if timestamp is found, ignore it and pick up rest of the string
					if len(temp_line) > 1:
						line = ''.join(temp_line[1:])
						
				if line.startswith('request') or line.startswith('response'):
					if r"'severity':'error'" in line:
						# iterate over given input patterns and search them in current line
						for pattern in input_pattern:
							if pattern in line:
								# save this line to output file and move on to next line
								with open(OUTPUT_FILE, 'a') as op_fp:
									op_fp.write(line)
									# found a pattern once, break the loop and go to next line
									break
					continue

	"""
	This is main run function for the class
	"""
	def run(self):
		files_to_be_searched = self.get_all_matching_files()
		print 'files to be searched are: {}'.format(files_to_be_searched)
		for file in files_to_be_searched:
			self.get_patterns_from_file(filename=file, input_pattern=self.pattern)
		
		

if __name__ == "__main__":
	parser = ArgumentParser()
	parser.add_argument('--file', type=str, default=None, dest='filename')
	parser.add_argument('--pattern', type=str, nargs='*', default=[], dest='search_pattern')
	options, remaining_options = parser.parse_known_args()
	# save unknown arguments to a file
	with open('unknown_args', 'w') as fp:
		fp.write(str(remaining_options))
	log_analyzer = LogAnalyzer(**vars(options))
	log_analyzer.run()
	# actual function call to for your script
	exit()
	
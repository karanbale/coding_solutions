import os
from subprocess import *
import logging
from argparse import *

# Root results directory
RESULT_DIR = os.path.join(os.path.expanduser('~'), 'RESULTS')
# if results directory does not exist, create one
if not os.path.isdir(RESULT_DIR):
	os.mkdir(RESULT_DIR)

# save logs to debug files in datetime, logging level and message format
debug_filename = os.path.join(RESULT_DIR, 'debug.log')
logging.basicConfig(filename=debug_filename, level=logging.DEBUG, filemode='a',
					format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

sample_data= '+----+---------+-----+------+-----------+-------+-----------+\n' \
	'| ID | Name    | RAM | Disk | Ephemeral | VCPUs | Is Public |\n' \
	'+----+---------+-----+------+-----------+-------+-----------+\n' \
	'| 0  | m1.nano |  64 |    1 |         0 |     1 | True      |\n' \
	'+----+---------+-----+------+-----------+-------+-----------+\n' \
	'| 1  | m2.nano |  65 |    2 |         1 |     2 | False     |\n' \
	'+----+---------+-----+------+-----------+-------+-----------+\n' \
	'| 2  | m3.nano |  66 |    3 |         2 |     3 | True      |\n' \
	'+----+---------+-----+------+-----------+-------+-----------+\n'

sample_data_1 = '+--------------------------------------+----------------------+--------+\n' \
				'| ID                                   | Name                 | Status |\n' \
				'+--------------------------------------+----------------------+--------+\n' \
				'| fe4529ef-9409-4016-8b33-9160b02c97a2 | cirros               | active |\n' \
				'| 0fe2cc0e-c52d-4327-a300-73ec9130ff6c | manila-service-image | active |\n' \
				'+--------------------------------------+----------------------+--------+\n'\


def output_parser(data=None):
	"""
	This method is a wrapper to parse received open-stack output in a
	dictionary format. The dictionary can then be used to feed as input
	options to the user to select from.
	:param data: output for various open-stack commands to be parsed
	The data is expected to be in a list format.
	:return: parse output in a dictionary format and return dictionary
	"""
	if not data:
		logger.debug('Please provide data to parse output.')
		return
	
	if not isinstance(data, str):
		logger.debug('Please ensure data to parse is in a list format.')
		return
	
	ret_dict = {}
	i = 0
	for item in data.split('\n'):
		# All alternate lines of output begin with + operator, skip those
		if item.startswith('+'):
			i += 1
			continue
		# All alternate lines of output begin with | operator, we care about
		# those so lets pick those up and parse those
		if item.startswith('|'):
			# split output and strip it
			output = item.split('|')
			output = [item.strip() for item in output if item not in ('', '\n', '\r')]
			# first data obtained is actual dictionary
			if i == 1 :
				for index,key in enumerate(output):
					ret_dict[key] = [index]
			else:
				# enumerate dictionary, assign all data items in right fashion
				for out_index, out_value in enumerate(output):
					for k, v in ret_dict.items():
						if v[0] == out_index:
							ret_dict[k].append(out_value)
							break
			i += 1
	logger.debug('Dictionary is: {}'.format(ret_dict))
	logger.debug('Dictionary keys: {}'.format(ret_dict.keys()))
	

	# for item in data.split('\n'):
	# 	# skip items which are not relevant
	# 	if item.startswith('+'):
	# 		continue
	# 	# split output in a list, strip it
	# 	output = item.split('|')
	# 	output = [item.strip() for item in output if item not in ('', '\n', '\r')]
	# 	print(output)
	# 	print('keys: {}'.format(ret_dict.keys()))
	# 	if set(ret_dict.keys()) == set(output):
	# 		logger.debug('skipping details: {}'.format(output))
	# 		continue
	# 	# enumerate dictionary, assign all data items in right fashion
	# 	for out_index,out_value in enumerate(output):
	# 		for k,v in ret_dict.items():
	# 			if v[0] == out_index:
	# 				ret_dict[k].append(out_value)
	# 				break

	logger.debug('parsed output: {}'.format(ret_dict))
	print('parsed_output: {}'.format(ret_dict))


def run_command(command=None):
	if not command:
		logger.debug('Please provide a command to run.')
		return
	
	logger.debug('Command to be run: {}'.format(command))
	process = Popen(command, stdin=PIPE, stdout=PIPE, stderr=PIPE)
	output, error = process.communicate()
	logger.debug('returncode: {}'.format(process.returncode))
	logger.debug('output: {}'.format(output))
	logger.debug('error: {}'.format(error))
	
	return (output, error)
	
	
if __name__ == "__main__":
	
	output_parser(data=sample_data)
	output_parser(data=sample_data_1)
	exit(100)

import os
from subprocess import *
import logging
from argparse import *
import time

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

sample_data = '+----+---------+-----+------+-----------+-------+-----------+\n' \
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
				'+--------------------------------------+----------------------+--------+\n' \

class OpenstackInstanceLauncher(object):
	
	def __init__(self, *args, **kwargs):
		command = kwargs.pop('command')
		self.launch_instance_command = kwargs.pop('create_instance')
		self.delete_instance_command = kwargs.pop('delete_instance')
		self.command = command.split(' ')
		self._command_list = ['openstack flavor list', 'openstack image list',
							  'openstack network list', 'openstack security group list',
							  'openstack keypair list', 'openstack server list']
		self._backend_data = {'flavor': [], 'image': [], 'network': [], 'security': [], 'keypair': [],
							  'server': []}
		self._user_data = {'flavor': 'm1.nano', 'image': 'cirros', 'network': 'selfservice',
						   'security': 'default', 'keypair': 'mykey', 'instance_name': '',
						   'server_name': ''}
	
	# equip back-end with all the required data
	def data_gather(self):
		for command in self._command_list:
			logger.info('Command being ran: {}'.format(command))
			output, error, ret_code = self.execute_command(command=command.split(' '))
			if ret_code:
				logger.error('Oops something went wrong. Please check output and error !')
				exit(1)
			parsed_output = self.output_parser(data=output)
			logger.info('Parsed output: {}'.format(parsed_output))
			for key in self._backend_data.keys():
				if key in command:
					logger.debug('Updating backend.')
					self._backend_data[key] = parsed_output
					break
		
		logger.debug('Back end data is:\n{}'.format(self._backend_data))
		print('Back end data is:\n{}'.format(self._backend_data))
		
	def output_parser(self, data=None):
		"""
		This method is a wrapper to parse received open-stack output in a
		dictionary format. The dictionary can then be used to feed as input
		options to the user to select from.
		:param data: output for various open-stack commands to be parsed
		The data is expected to be in a string format.
		:return: parse output in a dictionary format and return dictionary
		"""
		if not data:
			logger.error('Please provide data to parse output.')
			return
		
		if not isinstance(data, str):
			logger.error('Please ensure data to parse is in a list format.')
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
				# first valid data obtained in the output is actual dictionary keys
				if i == 1:
					for index, key in enumerate(output):
						ret_dict[key] = [index]
				else:
					# enumerate dictionary, assign all data items in right fashion
					for out_index, out_value in enumerate(output):
						for k, v in ret_dict.items():
							if v[0] == out_index:
								ret_dict[k].append(out_value)
								break
				i += 1
		logger.debug('Dictionary keys: {}'.format(ret_dict.keys()))
		logger.debug('parsed output: {}'.format(ret_dict))
		print('parsed_output: {}'.format(ret_dict))
		
		return ret_dict
	
	@staticmethod
	def execute_command(command=None):
		logger.debug('Command being run {}'.format(''.join(command)))
		process = Popen(command, stdin=PIPE, stdout=PIPE, stderr=PIPE)
		output, error = process.communicate()
		returncode = process.returncode
		logger.debug('return-code: {}'.format(returncode))
		logger.debug('output: {}'.format(output))
		logger.debug('error: {}'.format(error))
		
		return (output, error, returncode)
	
	def get_user_inputs(self):
		# ask user to enter his choices and start saving them
		logger.info('Interacting with user to determine sequence of actions.')
		user_input = int(input('Please select a task number:\n '
							   '1) Launch an instance with default configurations.\n '
							   '2) Launch an instance by selecting configurations manually\n '
							   '3) Delete an instance\n '
							   '4) Exit\n '))
		while (user_input > 3 or user_input <= 0):
			logger.error('Please provide valid input.')
			print('Please provide valid input..')
			user_input = int(input('Please select a task number:\n 1) Launch an instance\n 2) Exit\n'))
			logger.debug('User input: {}', format(user_input))
		if user_input == 4:
			logger.info('User requested to exit. Stopping.')
			print('Exiting script.')
			exit(0)
		elif user_input == 3:
			self._command_list = ['openstack server delete']
			# print list of all servers, except index 0 (we dont save any useful value at index 0)
			print('Available options to choose servers to delete from:')
			for server_num in range(1, len(self._backend_data['server']['Name'])):
				print('{}. {}'.format(server_num, self._backend_data['server']['Name'][server_num]))
			user_server = int(input('Please select a server from above list:\n'))
			self._user_data['server_name'] = self._backend_data['server']['Name'][server_num]
		elif user_input == 2:
			logger.info('User would like to launch an instance.')
			# print list of all flavors, except index 0 (we dont save any useful value at index 0)
			print('Available options to choose flavor from:')
			for flavor_num in range(1, len(self._backend_data['flavor']['Name'])):
				print('{}. {}'.format(flavor_num, self._backend_data['flavor']['Name'][flavor_num]))
			user_flavor = int(input('Please select a flavor from above list:\n'))
			# print list of all image, except index 0 (we dont save any useful value at index 0)
			print('Available options to choose image from:')
			for image_num in range(1, len(self._backend_data['image']['Name'])):
				print('{}. {}'.format(image_num, self._backend_data['image']['Name'][image_num]))
			user_image = int(input('Please select a image from above list:\n'))
			# print list of all network, except index 0 (we dont save any useful value at index 0)
			print('Available options to choose network from:')
			for network_num in range(1, len(self._backend_data['network']['Name'])):
				print('{}. {}'.format(network_num, self._backend_data['network']['Name'][network_num]))
			user_network = int(input('Please select a network from above list:\n'))
			# print list of all security, except index 0 (we dont save any useful value at index 0)
			print('Available options to choose security from:')
			for security_num in range(1, len(self._backend_data['security']['Name'])):
				print('{}. {}'.format(security_num, self._backend_data['security']['Name'][security_num]))
			user_security = int(input('Please select a security from above list:\n'))
			# print list of all security, except index 0 (we dont save any useful value at index 0)
			print('Available options to know existing key-name pairs are:')
			for keypair_num in range(1, len(self._backend_data['keypair']['Name'])):
				print('{}. {}'.format(keypair_num, self._backend_data['keypair']['Name'][keypair_num]))
			print('Please enter a keyname pair different from above list:\n')
			# request user to input key, name pair
			user_key_name_pair = raw_input('Please enter a key name pair:\n')
			user_instance_name = raw_input('Please enter an instance name:\n')
			self._user_data['flavor'] = self._backend_data['flavor']['Name'][user_flavor]
			self._user_data['image'] = self._backend_data['image']['Name'][user_image]
			self._user_data['network'] = self._backend_data['network']['ID'][user_network]
			self._user_data['security'] = self._backend_data['security']['Name'][user_security]
			self._user_data['keypair'] = user_key_name_pair
			self._user_data['instance_name'] = user_instance_name
		elif user_input == 1:
			# print list of all security, except index 0 (we dont save any useful value at index 0)
			user_instance_name = raw_input('Please enter an instance name:\n')
			self._user_data['instance_name'] = user_instance_name
			print('Default configurations to create an instance are:')
			for k, v in self._user_data.items():
				print('{}: {}'.format(k, v))
			# value at first index is always the default network id, so just pick it up as is
			self._user_data['network'] = self._backend_data['network']['ID'][2]
			for k, v in self._user_data.items():
				print('{}: {}'.format(k, v))

	def launch_instance(self):
		command = ['openstack', 'server', 'create',
				   '--flavor', '{}'.format(self._user_data['flavor']),
				   '--image', '{}'.format(self._user_data['image']),
				   '--nic', 'net-id={}'.format(self._user_data['network']),
				   '--security-group', '{}'.format(self._user_data['security']),
				   '--key-name', '{}'.format(self._user_data['keypair']),
				   '{}'.format(self._user_data['instance_name'])]
		
		output, error, ret_code = self.execute_command(command=command)
		if ret_code:
			logger.error('Oops something went wrong. Please check output and error !')
			exit(1)
		parsed_output = self.output_parser(data=output)
		logger.info('Parsed output: {}'.format(parsed_output))
		instance_created = False
		start_time = time.time()
		timeout = 60
		while(not instance_created):
			command = 'openstack server list'
			output, error, ret_code = self.execute_command(command=command.split(' '))
			if ret_code:
				logger.error('Oops something went wrong. Please check output and error !')
				exit(1)
			parsed_output = self.output_parser(data=output)
			logger.info('Parsed output: {}'.format(parsed_output))
			
			if parsed_output['Name'] == self._user_data['instance_name'] and parsed_output['Status'] == 'ACTIVE':
				logger.info('Instance launch successfully.')
				instance_created = True
			else:
				if (time.time() - start_time) > timeout:
					instance_created = True
				logger.error('Failed to launch the instance.')
			logger.debug('sleeping for 10 seconds.')
			print('sleeping for 10 seconds.')
			time.sleep(10)
		
		return instance_created == True

	def delete_instance(self):
		command = ['openstack', 'server', 'delete', '{}'.format(self._user_data['server_name'])]
	
		output, error, ret_code = self.execute_command(command=command)
		if ret_code:
			logger.error('Oops something went wrong. Please check output and error !')
			exit(1)
		parsed_output = self.output_parser(data=output)
		logger.info('Parsed output: {}'.format(parsed_output))
		
		if self._user_data['server_name'] in parsed_output['server']['name']:
			logger.error('Failed to delete instance. Please investigate.')
			exit(1)
		
		logger.debug('Deleted instance successfully.')
		
		
	def run(self):
		# prepare back-end before doing anything
		logger.info('Updating backend...')
		self.data_gather()
		logger.info('back-end updated successfully.')
		logger.info('getting inputs from user...')
		self.get_user_inputs()
		logger.debug('Inputs given by user are: {}'.format(self._user_data))
		if self.launch_instance_command:
			self.launch_instance()
		if self.delete_instance_command:
			self.delete_instance()


if __name__ == "__main__":
	parser = ArgumentParser()
	parser.add_argument('-c', type=str, nargs='*', default='', dest='command')
	parser.add_argument('--launch_instance', default='False', dest='create_instance', action='store_true')
	parser.add_argument('--delete_instance', default='False', dest='delete_instance', action='store_true')
	options, remaining_options = parser.parse_known_args()
	print('additional unknown args: {}'.format(remaining_options))
	openstack_obj = OpenstackInstanceLauncher(**vars(options))
	openstack_obj.run()
	# output_parser(data=sample_data)
	# output_parser(data=sample_data_1)
	exit(100)

#! /usr/bin/env python2.7

import glob

constant_names = []
for filename in glob.glob('*.c') + glob.glob('*.h'):
	with open(filename) as f:
		for line in f.readlines():
			if '#define' in line:
				lst = line.split()
				assert '#define' in lst
				new_name = lst[lst.index('#define') + 1]
				if new_name != '_CRT_SECURE_NO_WARNINGS':
					if new_name in constant_names:
						print '%s seems to be defined twice. Please check.' % new_name
					constant_names.append(new_name)


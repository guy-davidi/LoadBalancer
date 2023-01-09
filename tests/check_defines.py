#! /usr/bin/env python2

import sys
import glob
import os

from externals_utils import *

DEFINE = '#define'

def is_constant_used_in_same_module(constant, filename):
    c_files_containing_constant = get_filenames_containing_string(constant, "*.c")
    c_file = corresponding_c_file(filename)
    return c_file in c_files_containing_constant

def check_constant(constant, filename):
    if num_of_occurrences(constant, filename) > 1:
        return

    c_file = corresponding_c_file(filename)
    if os.path.isfile(c_file) and not is_constant_used_in_same_module(constant, filename):
        print "%s defined in %s, but not used in %s - please check." % (constant, filename, c_file)

    if not is_string_external(constant, filename):
        print "%s seems internal, yet is declared in .h file %s - please check." % (constant, filename)

def check_file(filename):
    f = open(filename)
    lines = f.readlines()
    if (not lines[0].startswith('#ifndef')) or (not lines[1].startswith(DEFINE)):
        print "Did you forget the header guard in %s ?" % filename

    for line in lines[2:]:
        if line.startswith(DEFINE) and '(' not in line:
            constant = line.split()[1]
            check_constant(constant, filename)

def main():
    for filename in glob.glob("*.h"):
        check_file(filename)

if __name__ == '__main__':
    main()

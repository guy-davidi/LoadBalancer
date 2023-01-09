import glob
import sys
import subprocess

from externals_utils import *

def get_functions_list(filename):
    result = []
    nm_output = subprocess.check_output(["nm", filename])
    for line in nm_output.split('\n')[:-1]:
        type_and_name = line[line.index(' '):]
        obj_type, obj_name = type_and_name.split()
        if obj_type == 'T' and not obj_name.startswith("_"):
            result.append(obj_name)
    return result

def get_h_file_defining_function(function_name):
    h_files_containing_function = get_filenames_containing_string(function_name, '*.h')
    if len(h_files_containing_function) == 1:
        return h_files_containing_function[0]
    return None

def check_private_functions(filename):
    functions_list = get_functions_list(filename)
    for function in functions_list:
        h_file = get_h_file_defining_function(function)
        if h_file != None and not is_string_external(function, h_file):
            print 'Function %s appears internal to file %s but appears in .h file - is this correct?' % (function, h_file)

if __name__ == '__main__':
    check_private_functions(sys.argv[1])

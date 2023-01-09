import glob
import sys
import subprocess

def get_functions_list(filename):
    result = []
    nm_output = subprocess.check_output(["nm", filename])
    for line in nm_output.split('\n')[:-1]:
        type_and_name = line[line.index(' '):]
        obj_type, obj_name = type_and_name.split()
        if obj_type == 'T' and not obj_name.startswith("_"):
            result.append(obj_name)
    return result

def unique(l):
    return [l[i] for i in range(len(l)) if l[:i].count(l[i]) == 0]

def get_filenames_containing_string(s, filename_pattern):
    proc = subprocess.Popen("grep -H " + s + " " + filename_pattern,
        stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    out, err = proc.communicate()
    result = []
    for line in out.split('\n')[:-1]:
        result.append(line.split(':')[0])
    return unique(result)

def get_h_file_defining_function(function_name):
    h_files_containing_function = get_filenames_containing_string(function_name, '*.h')
    if len(h_files_containing_function) == 1:
        return h_files_containing_function[0]
    return None

def is_function_external(function, h_file):
    c_files_calling_function = get_filenames_containing_string(function, "*.c")
    c_file = h_file[:-2] + ".c"
    return len([filename for filename in c_files_calling_function if filename != c_file]) > 0

def check_private_functions(filename):
    functions_list = get_functions_list(filename)
    for function in functions_list:
        h_file = get_h_file_defining_function(function)
        if h_file != None and not is_function_external(function, h_file):
            print 'Function %s appears internal to file %s but appears in .h file - is this correct?' % (function, h_file)

if __name__ == '__main__':
    check_private_functions(sys.argv[1])

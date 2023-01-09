import glob
import sys
import subprocess

def unique(l):
    return [l[i] for i in range(len(l)) if l[:i].count(l[i]) == 0]

def run_process(command):
    proc = subprocess.Popen(command,
        stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    out, err = proc.communicate()
    return out

def get_filenames_containing_string(s, filename_pattern):
    out = run_process("grep -H " + s + " " + filename_pattern)
    result = []
    for line in out.split('\n')[:-1]:
        result.append(line.split(':')[0])
    return unique(result)

def corresponding_c_file(h_file):
    return h_file[:-2] + ".c"

def is_string_external(function, h_file):
    c_files_containing_string = get_filenames_containing_string(function, "*.c")
    c_file = corresponding_c_file(h_file)
    return len([filename for filename in c_files_containing_string if filename != c_file]) > 0

def num_of_occurrences(constant, filename):
    return int(run_process("grep -c %s %s" % (constant, filename)))

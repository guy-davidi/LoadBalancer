#! /usr/bin/env bash

~nimrodav/socket_ex/verify_readme.sh

make --silent clean
~nimrodav/grep_tests/test_permissions.sh
make --silent

~nimrodav/grep_tests/check_line_lengths.sh
python2.7 ~nimrodav/grep_tests/check_private_functions.py ./my_grep
~nimrodav/header_guards/check_header_guards.sh
~nimrodav/header_guards/check_unnecessary_includes.sh
~nimrodav/grep_tests/check_defines.py
~nimrodav/grep_tests/check_magic_constants.sh

~nimrodav/grep_tests/run1.sh
~nimrodav/grep_tests/run2.sh
~nimrodav/grep_tests/run3.sh
~nimrodav/grep_tests/run4.sh
~nimrodav/grep_tests/run5.sh
~nimrodav/grep_tests/run6.sh
~nimrodav/grep_tests/run7.sh
~nimrodav/grep_tests/run8.sh
~nimrodav/grep_tests/run9.sh
~nimrodav/grep_tests/run10.sh
~nimrodav/grep_tests/run11.sh
~nimrodav/grep_tests/run12.sh
~nimrodav/grep_tests/run13.sh
~nimrodav/grep_tests/run14.sh
~nimrodav/grep_tests/run15.sh
~nimrodav/grep_tests/run16.sh
~nimrodav/grep_tests/run17.sh
~nimrodav/grep_tests/run18.sh
~nimrodav/grep_tests/run19.sh
~nimrodav/grep_tests/run20.sh

~nimrodav/lint/lint.sh

cd ../beta1
~nimrodav/grep_tests/beta1.sh
cd ../final_version

cd ../beta2
~nimrodav/grep_tests/beta2.sh
cd ../final_version

cat SDP | grep -v -i SDP

cat COPYING_WILL_BE_REPORTED | grep -v -i COPYING_WILL_BE_REPORTED

cat UNIFORM_MATCHING | grep -v -i UNIFORM_MATCHING

if [ ! -f DESIGN ]; then
    echo "DESIGN File not found!"
fi

if [[ -f SVN ]]; then
    ~nimrodav/svn/svn_check.sh
fi

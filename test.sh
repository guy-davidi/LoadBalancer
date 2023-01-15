#! /usr/bin/env bash

if [[ -f ./server_port ]]; then
	rm ./server_port
fi
if [[ -f ./http_port ]]; then
	rm ./http_port
fi

ls -la | grep ' \.$' | grep -v "drwxrwxrwx"
ls -la | grep -v '\.$' | grep -v "rwxr-xr-x" | grep -v "total "

./tests/check_line_lengths.sh
python2.7 ./tests/check_private_functions.py ./ex3_lb
./tests/check_header_guards.sh
./tests/check_unnecessary_includes.sh
./tests/check_defines.py
./tests/check_magic_constants.sh


./ex3_lb &
disown

./tests/wait_for_file_to_be_created_or_timeout.py server_port 3 || exit 1

./ex3_server `cat server_port` &
disown
./ex3_server `cat server_port` &
disown
./ex3_server `cat server_port` &
disown

./tests/wait_for_file_to_be_created_or_timeout.py http_port 3 || exit 1



python2.7 ./tests/run_test.py `cat http_port` | diff ./tests/1 -
python2.7 ./tests/run_test.py `cat http_port` | diff ./tests/1 -
python2.7 ./tests/run_test.py `cat http_port` | diff ./tests/1 -

python2.7 ./tests/run_test.py `cat http_port` | diff ./tests/2 -
python2.7 ./tests/run_test.py `cat http_port` | diff ./tests/2 -
python2.7 ./tests/run_test.py `cat http_port` | diff ./tests/2 -

python2.7 ./tests/run_test.py `cat http_port` | diff ./tests/3 -
python2.7 ./tests/run_test.py `cat http_port` | diff ./tests/3 -
python2.7 ./tests/run_test.py `cat http_port` | diff ./tests/3 -

rm server_port
rm http_port
echo "DONE"

pkill -x -u `whoami` "ex3_lb"
pkill -x -u `whoami` "ex3_server"
pkill -f -u `whoami` "python2.7"
pkill -f -u `whoami` "python"

pkill -9 -x -u `whoami` "ex3_lb"
pkill -9 -x -u `whoami` "ex3_server"
pkill -9 -f -u `whoami` "python2.7"
pkill -9 -f -u `whoami` "python"
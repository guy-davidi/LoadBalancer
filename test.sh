
#! /usr/bin/env bash

if [[ -f ./server_port ]]; then
        rm ./server_port
fi
if [[ -f ./http_port ]]; then
        rm ./http_port
fi

ls -la | grep ' \.$' | grep -v "drwxrwxrwx"
ls -la | grep -v '\.$' | grep -v "rwxr-xr-x" | grep -v "total "



./ex3_lb &
disown


./ex3_server `cat server_port` &
disown
./ex3_server `cat server_port` &
disown
./ex3_server `cat server_port` &
disown


python2 ./tests/run_test.py `cat http_port` | diff /tests/1 -
python2 ./tests/run_test.py `cat http_port` | diff /tests/1 -
python2 ./tests/run_test.py `cat http_port` | diff /tests/1 -
python2 ./tests/run_test.py `cat http_port` | diff /tests/2 -
python2 ./tests/run_test.py `cat http_port` | diff /tests/2 -
python2 ./tests/run_test.py `cat http_port` | diff /tests/2 -
python2 ./tests/run_test.py `cat http_port` | diff /tests/3 -
python2 ./tests/run_test.py `cat http_port` | diff /tests/3 -
python2 ./tests/run_test.py `cat http_port` | diff /tests/3 -

rm server_port
rm http_port

pkill -x -u `whoami` "ex3_lb"
pkill -x -u `whoami` "ex3_server"
pkill -f -u `whoami` "python2.7"
pkill -f -u `whoami` "python"

pkill -9 -x -u `whoami` "ex3_lb"
pkill -9 -x -u `whoami` "ex3_server"
pkill -9 -f -u `whoami` "python2.7"
pkill -9 -f -u `whoami` "python
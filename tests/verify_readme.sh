#! /usr/bin/env bash

cat README | grep `whoami` | wc -l | diff ./tests/1 -
cat README | grep -E "[0-9]{9} [[:alnum:]]+ [[:alnum:]]+" | wc -l | grep -v -E "(2|3)"


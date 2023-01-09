#! /usr/bin/env bash

if ls *.h 1> /dev/null 2>&1; then
  grep '.\{122\}' *.h
fi

grep '.\{122\}' *.c

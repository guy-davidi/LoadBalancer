#! /usr/bin/env bash

if test -z "$(find . -maxdepth 1 -name '*.h' -print -quit)"
then
    exit 0
fi

for F in *.h; do
head --lines=1 $F | grep -v "^#ifndef"
head --lines=2 $F | tail --lines=1 | grep -v "^#define"
done


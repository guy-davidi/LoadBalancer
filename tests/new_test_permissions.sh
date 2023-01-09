#! /usr/bin/env bash

if [ -z "$1" ]; then
	PERMISSIONS_STRING="rwxr-xr-x"
else
	PERMISSIONS_STRING="$1"
fi

ls -la | tail -n +2 | grep -v '\.\.$' | grep -v $PERMISSIONS_STRING | grep -v '\.o$'

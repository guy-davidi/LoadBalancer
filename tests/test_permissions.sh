#! /usr/bin/env bash

ls -la | tail -n +2 | grep -v '\.\.$' | grep -v "rwxr-xr-x" | grep -v '\.o$' | grep -v beta

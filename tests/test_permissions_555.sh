#! /usr/bin/env bash

ls -la | tail -n +2 | grep -v '\.\.$' | grep -v "r-xr-xr-x" | grep -v '\.o$'

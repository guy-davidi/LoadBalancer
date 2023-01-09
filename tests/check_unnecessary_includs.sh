#! /usr/bin/env bash

if test -z "$(find . -maxdepth 1 -name '*.h' -print -quit)"
then
    exit 0
fi

for f in *.h; do
grep "stdio\.h" $f > /dev/null
RC=$?
if [[ $RC -eq 0 ]]; then
grep "FILE" $f > /dev/null
RC=$?
if [[ $RC -ne 0 ]]; then
echo "Suspicious include of stdio detected in $f. Please check."
fi
fi

        grep "stdlib\.h" $f > /dev/null
        RC=$?
        if [[ $RC -eq 0 ]]; then
                echo "Suspicious include of stdlib detected in $f. Please check."
        fi

        grep "string\.h" $f > /dev/null
        RC=$?
        if [[ $RC -eq 0 ]]; then
                echo "Suspicious include of string detected in $f. Please check."
        fi
done


#!/bin/bash

# NAME: Jordan Combitsis
# EMAIL: jcombitsis17@gmail.com
# ID: 004921527


# Bad Argument
`./lab4b --idk`

if [ $? -eq 1 ]
then
    echo "Bad Argument: passed"
else
    echo "Bad Argument: failed"
fi

# Normal Execution
`touch tmp.txt`

./lab4b --log=tmp.txt << EOF
PERIOD=3
SCALE=C
STOP
LOG hello
START
OFF
EOF

if [ $? -eq 0 ]
then
    echo "Normal Execution: passed (run successful)"
else
    echo "Normal Execution: failed"
fi

# search for each command in tmp.txt
grep "PERIOD=3" tmp.txt
if [ $? -eq 0 ]
then
    echo "PERIOD: passed"
else
    echo "PERIOD: failed"
fi

grep "SCALE=C" tmp.txt
if [ $? -eq 0 ]
then
    echo "SCALE: passed"
else
    echo "SCALE: failed"
fi

grep "STOP" tmp.txt
if [ $? -eq 0 ]
then
    echo "STOP: passed"
else
    echo "STOP: failed"
fi

grep "LOG hello" tmp.txt
if [ $? -eq 0 ]
then
    echo "LOG: passed"
else
    echo "LOG: failed"
fi

grep "START" tmp.txt
if [ $? -eq 0 ]
then
    echo "START: passed"
else
    echo "START: failed"
fi

grep "SHUTDOWN" tmp.txt
if [ $? -eq 0 ]
then
    echo "OFF: passed"
else
    echo "OFF: failed"
fi

`rm -f tmp.txt`

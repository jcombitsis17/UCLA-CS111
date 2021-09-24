#!/bin/bash

# NAME: Jordan Combitsis
# EMAIL: jcombitsis17@gmail.com
# ID: 004921527


# create input file
`touch in.txt`
`echo "this is a test input" > in.txt`


# Check basic in/out case
echo ""
echo "Case 1: Copy Input to Output"
`./lab0 --input=in.txt --output=out.txt`

if [ $? -eq 0 ]
then
    echo "  Program succeeded with exit code 0"
else
    echo "  Error: Program failed execution"
fi

`cmp in.txt out.txt`
if [ $? -eq 0 ]
then
    echo "  Successfully copied input to output"
else
    echo "  Error: input and output not equal"
fi

# Check bad argument
echo ""
echo "Case 2: Unrecognized Argument"
`./lab0 --bad`

if [ $? -eq 1 ]
then
    echo "  Task failed successfully with exit code 1"
else
    echo "  Error: incorrect exit code"
fi

# Check input error
echo ""
echo "Case 3: Unable to Open Input File"
`./lab0 --input=notinput --output=out.txt`

if [ $? -eq 2 ]
then
    echo "  Task failed successfully with exit code 2 (could not open input file)"
else
    echo "  Error: incorrect exit code"
fi

# Check output error
echo ""
echo "Case 4: Unable to Open Output File"
`touch badoutput.txt`
`chmod u-w badoutput.txt`
`./lab0 --input=in.txt --output=badoutput.txt`

if [ $? -eq 3 ]
then
    echo "  Task failed successfully with exit code 3 (could not write to output file)"
else
    echo "  Error: incorrect exit code"
fi

# Check catch segmentation fault
echo ""
echo "Case 5: Catch Segmentation Fault"
`./lab0 --segfault --catch`

if [ $? -eq 4 ]
then
    echo "  Task failed successfully with exit code 4 (segfault caught)"
else
    echo "  Error: incorrect exit code"
fi

# Check segfault
echo ""
echo "Case 6: Force Segmentation Fault"
`./lab0 --segfault`

if [ $? -eq 139 ]
then
    echo "  Task failed successfully with exit code 139 (forced segmentation fault)"
else
    echo "  Error: incorrect exit code"
fi

# delete input and output files
`rm -f in.txt out.txt badoutput.txt`

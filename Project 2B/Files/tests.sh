#!/bin/bash

# NAME: Jordan Combitsis
# EMAIL: jcombitsis17@gmail.com
# ID: 004921527


# 2.3.1 Tests
echo "Running 2.3.1 Tests..."

`./lab2_list --threads=1  --iterations=1000 --sync=m >  lab2b_list.csv`
`./lab2_list --threads=2  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --threads=4  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --threads=8  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2b_list.csv`

`./lab2_list --threads=1  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --threads=2  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --threads=4  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --threads=8  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2b_list.csv`

echo "Running 2.3.2 Tests..."

`./lab2_list --lists=4 --threads=1  --iterations=1  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=1  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=1  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=1  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=1  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=2  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=2  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=2  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=2  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=2  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=4  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=4  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=4  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=4  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=4  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=8  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=8  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=8  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=8  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=8  --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=16 --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=16 --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=16 --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=16 --yield=id >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=16 --yield=id >> lab2b_list.csv`

echo "Running 2.3.3 Tests..."

`./lab2_list --lists=4 --threads=1  --iterations=10  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=10  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=10  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=10  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=10  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=20  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=20  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=20  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=20  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=20  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=40  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=40  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=40  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=40  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=40  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=80  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=80  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=80  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=80  --yield=id --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=80  --yield=id --sync=m >> lab2b_list.csv`

`./lab2_list --lists=4 --threads=1  --iterations=10  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=10  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=10  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=10  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=10  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=20  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=20  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=20  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=20  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=20  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=40  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=40  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=40  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=40  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=40  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=1  --iterations=80  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=2  --iterations=80  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=4  --iterations=80  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=8  --iterations=80  --yield=id --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4 --threads=16 --iterations=80  --yield=id --sync=s >> lab2b_list.csv`

echo "Running 2.3.4 Tests..."

#`./lab2_list --lists=1  --threads=1  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=1  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=1  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=1  --iterations=1000 --sync=m >> lab2b_list.csv`
#`./lab2_list --lists=1  --threads=2  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=2  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=2  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=2  --iterations=1000 --sync=m >> lab2b_list.csv`
#`./lab2_list --lists=1  --threads=4  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=4  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=4  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=4  --iterations=1000 --sync=m >> lab2b_list.csv`
#`./lab2_list --lists=1  --threads=8  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=8  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=8  --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=8  --iterations=1000 --sync=m >> lab2b_list.csv`
#`./lab2_list --lists=1  --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv`

#`./lab2_list --lists=1  --threads=1  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=1  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=1  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=1  --iterations=1000 --sync=s >> lab2b_list.csv`
#`./lab2_list --lists=1  --threads=2  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=2  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=2  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=2  --iterations=1000 --sync=s >> lab2b_list.csv`
#`./lab2_list --lists=1  --threads=4  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=4  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=4  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=4  --iterations=1000 --sync=s >> lab2b_list.csv`
#`./lab2_list --lists=1  --threads=8  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=8  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=8  --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=8  --iterations=1000 --sync=s >> lab2b_list.csv`
#`./lab2_list --lists=1  --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=4  --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=8  --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv`
`./lab2_list --lists=16 --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv`


echo "Done."
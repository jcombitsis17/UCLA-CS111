#!/bin/bash

# NAME: Jordan Combitsis
# EMAIL: jcombitsis17@gmail.com
# ID: 004921527


# TESTS FOR LAB2_ADD

# 2.1.1 Tests
echo "Running 2.1.1 Tests..."

`./lab2_add --threads=2  --iterations=100 >  lab2_add.csv`
`./lab2_add --threads=4  --iterations=100 >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=100 >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=100 >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=1000 >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=1000 >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=1000 >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=1000 >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=10000 >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10000 >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10000 >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10000 >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=100000 >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=100000 >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=100000 >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=100000 >> lab2_add.csv`

# 2.1.2 Tests
echo "Running 2.1.2 Tests..."

`./lab2_add --threads=2  --iterations=10 --yield >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10 --yield >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10 --yield >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10 --yield >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=20 --yield >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=20 --yield >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=20 --yield >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=20 --yield >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=40 --yield >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=40 --yield >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=40 --yield >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=40 --yield >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=80 --yield >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=80 --yield >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=80 --yield >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=80 --yield >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=100 --yield >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=100 --yield >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=100 --yield >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=100 --yield >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=1000 --yield >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=1000 --yield >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=1000 --yield >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=1000 --yield >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=10000 --yield >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10000 --yield >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10000 --yield >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10000 --yield >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=100000 --yield >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=100000 --yield >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=100000 --yield >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=100000 --yield >> lab2_add.csv`

# 2.1.3 Tests
echo "Running 2.1.3 Tests..."

`./lab2_add --iterations=10     >> lab2_add.csv`
`./lab2_add --iterations=20     >> lab2_add.csv`
`./lab2_add --iterations=40     >> lab2_add.csv`
`./lab2_add --iterations=80     >> lab2_add.csv`
`./lab2_add --iterations=100    >> lab2_add.csv`
`./lab2_add --iterations=1000   >> lab2_add.csv`
`./lab2_add --iterations=10000  >> lab2_add.csv`
`./lab2_add --iterations=100000 >> lab2_add.csv`

# 2.1.4 Tests
echo "Running 2.1.4 Tests..."

`./lab2_add --threads=2  --iterations=10000 --yield >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10000 --yield >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10000 --yield >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10000 --yield >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=10000 --yield --sync=m >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10000 --yield --sync=m >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10000 --yield --sync=m >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10000 --yield --sync=m >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=1000 --yield --sync=s >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=1000 --yield --sync=s >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=1000 --yield --sync=s >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=1000 --yield --sync=s >> lab2_add.csv`

`./lab2_add --threads=2  --iterations=10000 --yield --sync=c >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10000 --yield --sync=c >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10000 --yield --sync=c >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10000 --yield --sync=c >> lab2_add.csv`

# 2.1.5 Tests
echo "Running 2.1.5 Tests..."

`./lab2_add --threads=1  --iterations=10000 >> lab2_add.csv`
`./lab2_add --threads=2  --iterations=10000 >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10000 >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10000 >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10000 >> lab2_add.csv`

`./lab2_add --threads=1  --iterations=10000 --sync=m >> lab2_add.csv`
`./lab2_add --threads=2  --iterations=10000 --sync=m >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10000 --sync=m >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10000 --sync=m >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10000 --sync=m >> lab2_add.csv`

`./lab2_add --threads=1  --iterations=10000 --sync=s >> lab2_add.csv`
`./lab2_add --threads=2  --iterations=10000 --sync=s >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10000 --sync=s >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10000 --sync=s >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10000 --sync=s >> lab2_add.csv`

`./lab2_add --threads=1  --iterations=10000 --sync=c >> lab2_add.csv`
`./lab2_add --threads=2  --iterations=10000 --sync=c >> lab2_add.csv`
`./lab2_add --threads=4  --iterations=10000 --sync=c >> lab2_add.csv`
`./lab2_add --threads=8  --iterations=10000 --sync=c >> lab2_add.csv`
`./lab2_add --threads=12 --iterations=10000 --sync=c >> lab2_add.csv`

echo "Completed Add Tests."

# TESTS FOR LAB2_LIST

# 2.2.1 Tests
echo "Running 2.2.1 Tests..."

`./lab2_list --iterations=10    >  lab2_list.csv`
`./lab2_list --iterations=100   >> lab2_list.csv`
`./lab2_list --iterations=1000  >> lab2_list.csv`
`./lab2_list --iterations=10000 >> lab2_list.csv`
`./lab2_list --iterations=20000 >> lab2_list.csv`

# 2.2.2 Tests
echo "Running 2.2.2 Tests..."

`./lab2_list --threads=2  --iterations=1 >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=1 >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=1 >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=1 >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=10 >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=10 >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=10 >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=10 >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=100 >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=100 >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=100 >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=100 >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=1000 >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=1000 >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=1000 >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=1000 >> lab2_list.csv`

echo "Running --yield=i Tests..."
`./lab2_list --threads=2  --iterations=1 --yield=i >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=1 --yield=i >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=1 --yield=i >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=1 --yield=i >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=2 --yield=i >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=2 --yield=i >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=2 --yield=i >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=2 --yield=i >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=4 --yield=i >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=4 --yield=i >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=4 --yield=i >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=4 --yield=i >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=8 --yield=i >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=8 --yield=i >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=8 --yield=i >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=8 --yield=i >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=16 --yield=i >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=16 --yield=i >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=16 --yield=i >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=16 --yield=i >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=32 --yield=i >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=32 --yield=i >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=32 --yield=i >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=i >> lab2_list.csv`

echo "Running --yield=d Tests..."
`./lab2_list --threads=2  --iterations=1 --yield=d >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=1 --yield=d >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=1 --yield=d >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=1 --yield=d >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=2 --yield=d >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=2 --yield=d >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=2 --yield=d >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=2 --yield=d >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=4 --yield=d >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=4 --yield=d >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=4 --yield=d >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=4 --yield=d >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=8 --yield=d >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=8 --yield=d >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=8 --yield=d >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=8 --yield=d >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=16 --yield=d >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=16 --yield=d >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=16 --yield=d >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=16 --yield=d >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=32 --yield=d >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=32 --yield=d >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=32 --yield=d >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=d >> lab2_list.csv`

echo "Running --yield=il Tests..."
`./lab2_list --threads=2  --iterations=1 --yield=il >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=1 --yield=il >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=1 --yield=il >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=1 --yield=il >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=2 --yield=il >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=2 --yield=il >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=2 --yield=il >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=2 --yield=il >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=4 --yield=il >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=4 --yield=il >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=4 --yield=il >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=4 --yield=il >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=8 --yield=il >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=8 --yield=il >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=8 --yield=il >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=8 --yield=il >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=16 --yield=il >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=16 --yield=il >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=16 --yield=il >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=16 --yield=il >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=32 --yield=il >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=32 --yield=il >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=32 --yield=il >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=il >> lab2_list.csv`

echo "Running --yield=dl Tests..."
`./lab2_list --threads=2  --iterations=1 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=1 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=1 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=1 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=2 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=2 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=2 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=2 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=4 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=4 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=4 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=4 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=8 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=8 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=8 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=8 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=16 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=16 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=16 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=16 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=2  --iterations=32 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=4  --iterations=32 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=8  --iterations=32 --yield=dl >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=dl >> lab2_list.csv`

# 2.2.3 Tests
echo "Running 2.2.3 Tests..."

`./lab2_list --threads=12 --iterations=32 --yield=i --sync=m >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=i --sync=s >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=d --sync=m >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=d --sync=s >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=il --sync=m >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=il --sync=s >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=dl --sync=m >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=32 --yield=dl --sync=s >> lab2_list.csv`

`./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2_list.csv`
`./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2_list.csv`
`./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2_list.csv`
`./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2_list.csv`
`./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2_list.csv`
`./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2_list.csv`
`./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2_list.csv`
`./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2_list.csv`
`./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2_list.csv`
`./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2_list.csv`
`./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2_list.csv`
`./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2_list.csv`
`./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2_list.csv`

echo "Completed List Tests."


echo "Done."

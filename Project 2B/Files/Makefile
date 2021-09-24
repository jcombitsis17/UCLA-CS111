# NAME: Jordan Combitsis
# EMAIL: jcombitsis17@gmail.com
# ID: 004921527

default:
	gcc -g -o lab2_list -pthread -lprofiler -Wall -Wextra lab2_list.c SortedList.c

tests: default
	./tests.sh && (echo -e "\nAll tests completed successfully!";)

profile: default
	rm -f profile.out ./raw.gperf
	LD_PRELOAD=/u/ee/ugrad/combitsi/CS111/lib/libprofiler.so.0
	CPUPROFILE=./raw.gperf ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof --text ./lab2_list ./raw.gperf > profile.out
	pprof --list=thread_func ./lab2_list ./raw.gperf >> profile.out
	rm -f ./raw.gperf

graphs: tests
	./lab2b_list.gp

dist: graphs profile 
	tar -zcvf lab2b-004921527.tar.gz lab2_list.c SortedList.c SortedList.h tests.sh profile.out \
	lab2b_list.csv lab2b_list.gp lab2b_1.png lab2b_2.png lab2b_3.png lab2b_4.png lab2b_5.png    \
	Makefile README
	
clean:
	rm -f lab2_list lab2b-004921527.tar.gz 
# NAME: Jordan Combitsis
# EMAIL: jcombitsis17@gmail.com
# ID: 004921527

default:
	gcc -g -o lab2_add -pthread -Wall -Wextra lab2_add.c
	gcc -g -o lab2_list -pthread -Wall -Wextra lab2_list.c SortedList.c

build: default

tests: build
	./tests.sh && (echo -e "\nAll tests completed successfully!";)

graphs: tests
	./lab2_add.gp
	./lab2_list.gp

dist: graphs
	tar -zcvf lab2a-004921527.tar.gz lab2_add.c lab2_list.c SortedList.c SortedList.h tests.sh \
	lab2_add.csv lab2_add-1.png lab2_add-2.png lab2_add-3.png lab2_add-4.png lab2_add-5.png    \
	lab2_list.csv lab2_list-1.png lab2_list-2.png lab2_list-3.png lab2_list-4.png              \
	Makefile README                                                                            \
	lab2_add.gp lab2_list.gp
	
clean:
	rm -f lab2_add lab2_list lab2a-004921527.tar.gz 
# NAME: Jordan Combitsis
# EMAIL: jcombitsis17@gmail.com
# ID: 004921527

default:
	gcc -g -o lab4b -Wall -Wextra lab4b.c -lm -lmraa

check: default
	./tests.sh && (echo -e "\nAll tests completed successfully!";)

dist:
	tar -zcvf lab4b-004921527.tar.gz lab4b.c tests.sh Makefile README
	
clean:
	rm -f lab4b lab4b-004921527.tar.gz 
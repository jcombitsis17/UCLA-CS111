# NAME: Jordan Combitsis
# EMAIL: jcombitsis17@gmail.com
# ID: 004921527

default:
	gcc -g -o lab0 -Wall -Wextra lab0.c

check:
	./check.sh && (echo -e "\nSmoke Check Complete!";)

clean:
	rm -f lab0 lab0-004921527.tar.gz in.txt out.txt badoutput.txt

dist:
	tar -zcvf lab0-004921527.tar.gz lab0.c Makefile README backtrace.png breakpoint.png check.sh
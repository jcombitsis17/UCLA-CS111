# NAME: Jordan Combitsis
# EMAIL: jcombitsis17@gmail.com
# ID: 004921527

default:
	gcc -g -o lab4c_tcp -Wall -Wextra lab4c_tcp.c -lm -lmraa
	gcc -g -o lab4c_tls -Wall -Wextra lab4c_tls.c -lm -lmraa -lssl -lcrypto

dist:
	tar -zcvf lab4c-004921527.tar.gz lab4c_tcp.c lab4c_tls.c Makefile README
	
clean:
	rm -f lab4c_tcp lab4c_tls lab4c-004921527.tar.gz 
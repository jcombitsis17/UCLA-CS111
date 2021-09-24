/*
NAME: Jordan Combitsis
EMAIL: jcombitsis17@gmail.com
ID: 004921527
*/

#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

void force_segfault()
{
    char *c = NULL;
    *c = 'c';
}

void catch_segfault()
{
    fprintf(stderr, "Segmentation Fault (caught)\n");
    exit(4);
}

int main(int argc, char *argv[])
{
    int opt;
    int sflag = 0;
    int input, output;

    static struct option long_options[] = 
    {
        {"input",    required_argument, 0,   'i'},
        {"output",   required_argument, 0,   'o'},
        {"segfault", no_argument,       0,   's'},
        {"catch",    no_argument,       0,   'c'},
        {0,          0,                 0,   0  }
    };

    while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1)
    {

        switch(opt)
        {
            case 'i':
                input = open(optarg, O_RDONLY);
                if (input >= 0) {
                    close(0);
                    dup(input);
                    close(input);
                } else {
                    fprintf(stderr, "Error: could not open input file %s\n%s\n", optarg, strerror(errno));
                    exit(2);
                }
                break;
            case 'o':
                output = creat(optarg, 0666);
                if (output >= 0) {
                    close(1);
                    dup(output);
                    close(output);
                } else {
                    fprintf(stderr, "Error: could not create output file %s\n%s\n", optarg, strerror(errno));
                    exit(3);
                }
                break;
            case 's':
                sflag = 1;
                break;
            case 'c':
                signal(SIGSEGV, catch_segfault);
                break;
            default:
                fprintf(stderr, "Unrecognized argument! \nSupported options are: --input [FILE], --output [FILE], --segfault, --catch\n");
                exit(1);
        }
    }

    if (sflag)
        force_segfault();
    
    // copy FD0 to FD1
    char buffer;
    while (read(0, &buffer, sizeof(char)) > 0) {
        write(1, &buffer, sizeof(char));
    }

    exit(0);
}
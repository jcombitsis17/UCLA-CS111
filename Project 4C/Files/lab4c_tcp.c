/*
NAME: Jordan Combitsis
EMAIL: jcombitsis17@gmail.com
ID: 004921527
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <poll.h>
#include <mraa.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

const int B = 4275;
const int R0 = 100000;
const int BUFFER_SIZE = 256;

int period = 1;
char scale = 'F';
int lflag = 0;
int do_report = 1;
FILE *logfile;
char *buffer;
struct tm *currtime;

char* id;
char* host;
int port;
int sockFd;
struct sockaddr_in addr;
struct hostent *server;

mraa_aio_context temp_sensor;

float read_temp()
{
    int reading = mraa_aio_read(temp_sensor);
    float R = 1023.0 / (float) reading - 1.0;
    R = R0 * R;
    float temperature = 1.0 / (log(R/R0)/B + 1/298.15) - 273.15;

    return (scale == 'C') ? temperature : (temperature * 9.0/5.0 + 32.0);
}

void do_exit_things()
{
    if (temp_sensor)
        mraa_aio_close(temp_sensor);
    if (logfile)
        fclose(logfile);
    free(buffer);
}

void generate_report(int shutdown)
{
    if (!do_report && !shutdown)
        return;
    
    char time_s[9];
    char temp_s[9];
    time_t t;
    
    time(&t);
    currtime = localtime(&t);
    sprintf(time_s, "%02d:%02d:%02d ", currtime->tm_hour, currtime->tm_min, currtime->tm_sec);
    if (shutdown) sprintf(temp_s, "SHUTDOWN");
    else          sprintf(temp_s, "%.1f", read_temp());

    dprintf(sockFd,  "%s%s\n", time_s, temp_s);
    if (lflag)
        fprintf(logfile, "%s%s\n", time_s, temp_s);
}

void interrupt()
{
    generate_report(1);
    exit(0);
}

void process_command(char* input)
{
    input[strlen(input) - 1] = '\0';
    
    if (lflag) fprintf(logfile, "%s\n", input);

    if (strcmp(input, "START") == 0) {
        do_report = 1;
    } else if (strcmp(input, "STOP") == 0) {
        do_report = 0;
    } else if (strncmp(input, "PERIOD=", sizeof(char)*7) == 0) {
        period = atoi(input + 7);
    } else if (strcmp(input, "SCALE=C") == 0) {
        scale = 'C';
    } else if (strcmp(input, "SCALE=F") == 0) {
        scale = 'F';
    } else if (strncmp(input, "LOG ", sizeof(char)*4) == 0) {
        // log (do nothing unless lflag = 1)
    } else if (strcmp(input, "OFF") == 0) {
        interrupt();
    }
}

int main(int argc, char *argv[])
{
    atexit(do_exit_things);

    static struct option long_options[] = 
    {
        { "period", required_argument, 0, 'p' },
        { "scale",  required_argument, 0, 's' },
        { "log",    required_argument, 0, 'l' },
        { "id",     required_argument, 0, 'i' },
        { "host",   required_argument, 0, 'h' },
        { 0,        0,                 0,  0  }
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1)
    {
        switch(opt)
        {
            case 'p':
                period = atoi(optarg);
                if (period < 1) {
                    fprintf(stderr, "Invalid period: must be a positive integer");
                    exit(1);
                }
                break;
            case 's':
                switch (optarg[0]) {
                    case 'C':
                    case 'F':
                        scale = optarg[0];
                        break;
                    default:
                        fprintf(stderr, "Invalid scale: must be F or C (case-sensitive).\n");
                        exit(1);
                }
                break;
            case 'l':
                lflag = 1;
                logfile = fopen(optarg, "w+");
                if (logfile == NULL) {
                    fprintf(stderr, "Error: fopen()\n");
                    exit(1);
                }
                break;
            case 'i':
                id = optarg;
                if (strlen(id) != 9) {
                    fprintf(stderr, "Error: ID is not a 9-digit number.\n");
                    exit(1);
                }
                break;
            case 'h':
                host = optarg;
                if (strlen(host) == 0) {
                    fprintf(stderr, "Error: empty hostname.\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "Unrecognized argument! \nSupported options are: --period=[NUM], --scale=[C|F], --log=[PATH], --id=[NUM], --host=[NAME]\n");
                exit(1);
        }
    }
    
    if (optind >= argc) {
        fprintf(stderr, "No port specified.\n");
        exit(1);
    }
    port = atoi(argv[optind]);
    if (port <= 0) {
        fprintf(stderr, "Error: bad/missing port number.\n");
        exit(1);
    }
    if (!lflag) {
        fprintf(stderr, "Error: --log=[PATH] option is mandatory.\n");
        exit(1);
    }

    if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Error: socket()\n");
        exit(2);
    }
    if ((server = gethostbyname(host)) == NULL) {
        fprintf(stderr, "Error: gethostbyname() -- could not find host name.\n");
        exit(1);
    }
    memset((char*)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    memcpy((char*)&addr.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
    addr.sin_port = htons(port);
    if ((connect(sockFd, (struct sockaddr*)&addr, sizeof(addr))) == -1) {
        fprintf(stderr, "Error: connect()\n");
        exit(2);
    }
    char id_str[12];
    sprintf(id_str, "ID=%s\n", id);
    dprintf(sockFd, "%s", id_str);
    if (lflag) fprintf(logfile, "%s", id_str);

    temp_sensor = mraa_aio_init(1);
    if (temp_sensor == NULL) {
        fprintf(stderr, "Error: mraa_aio_init()\n");
        exit(2);
    }

    struct pollfd pfd;
    pfd.fd = sockFd;
    pfd.events = POLLIN | POLLERR | POLLHUP;

    buffer = malloc(sizeof(char) * BUFFER_SIZE);
    memset(buffer, 0, BUFFER_SIZE);

    time_t curr, prev;
    while (1)
    {
        generate_report(0);

        time(&prev);
        time(&curr);
        while ((int) difftime(curr, prev) < period)
        {
            if (poll(&pfd, 1, 0) == -1) {
                fprintf(stderr, "Error: poll()\n");
                exit(2);
            }

            if (pfd.revents & POLLIN) {
                int r = read(sockFd, buffer, BUFFER_SIZE);
                if (r == -1) {
                    fprintf(stderr, "Error: read()\n");
                    exit(2);
                }
                process_command(buffer);
                memset(buffer, 0, BUFFER_SIZE);
            } else if (pfd.revents & (POLLERR | POLLHUP)) {
                fprintf(stderr, "Error: POLLERR | POLLHUP\n");
                exit(2);
            }

            time(&curr);
        }
    }

    exit(0);
}

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

mraa_aio_context temp_sensor;
mraa_gpio_context button;

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
    if (button)
        mraa_gpio_close(button);
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
    if (shutdown) sprintf(temp_s, "SHUTDOWN\n");
    else          sprintf(temp_s, "%.1f\n", read_temp());

    fprintf(stdout,  "%s%s", time_s, temp_s);
    if (lflag)
        fprintf(logfile, "%s%s", time_s, temp_s);
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
            default:
                fprintf(stderr, "Unrecognized argument! \nSupported options are: --period=[NUM], --scale=[C|F], --log=[PATH]\n");
                exit(1);
        }
    }

    temp_sensor = mraa_aio_init(1);
    if (temp_sensor == NULL) {
        fprintf(stderr, "Error: mraa_aio_init()\n");
        exit(1);
    }

    button = mraa_gpio_init(60);
    if (button == NULL) {
        fprintf(stderr, "Error: mraa_gpio_init()\n");
        exit(1);
    }
    mraa_gpio_dir(button, MRAA_GPIO_IN);
    mraa_gpio_isr(button, MRAA_GPIO_EDGE_RISING, &interrupt, NULL);

    struct pollfd pfd;
    pfd.fd = STDIN_FILENO;
    pfd.events = POLLIN | POLLERR | POLLHUP;

    buffer = malloc(sizeof(char) * BUFFER_SIZE);

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
                exit(1);
            }

            if (pfd.revents & POLLIN) {
                fgets(buffer, BUFFER_SIZE, stdin);
                process_command(buffer);
            } else if (pfd.revents & (POLLERR | POLLHUP)) {
                fprintf(stderr, "Error: POLLERR | POLLHUP\n");
                exit(1);
            }

            time(&curr);
        }
    }

    exit(0);
}

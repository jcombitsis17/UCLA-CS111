/*
NAME: Jordan Combitsis
EMAIL: jcombitsis17@gmail.com
ID: 004921527
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <termios.h>
#include <poll.h>
#include <sys/wait.h>
#include <string.h>

const int BUFFER_SIZE = 256;
int pipe_p[2];
int pipe_c[2];
int pid;
int shflag = 0;
char CRLF[2] = {'\r', '\n'};
struct termios save_term;

void get_exit_status()
{
    int exit_status;
    waitpid(pid, &exit_status, 0);
    fprintf(stderr, "SHELL EXIT SIGNAL=%d STATUS=%d\n", exit_status & 0xFF, exit_status / 256);
}

void restore_term()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &save_term);
    if (shflag) {
        get_exit_status();
    }
}

void shell_shutdown()
{
    kill(pid, SIGINT);
    exit(0);
}

int main(int argc, char *argv[])
{
    int opt;
    char* program;

    static struct option long_options[] = 
    {
        { "shell", required_argument, 0, 's' },
        { 0,       0,                 0,  0  }
    };

    while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1)
    {
        switch(opt)
        {
            case 's':
                program = optarg;
                shflag = 1;
                break;
            default:
                fprintf(stderr, "Unrecognized argument! \nSupported options are: --shell=[PROGRAM]\n");
                exit(1);
        }
    }

    // change terminal mode
    struct termios terminal;
    tcgetattr(STDIN_FILENO, &save_term);
    atexit(restore_term);
    
    tcgetattr(STDIN_FILENO, &terminal);
    terminal.c_iflag = ISTRIP;
    terminal.c_oflag = 0;
    terminal.c_lflag = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &terminal);

    // shell option
    if (shflag) {
        // create pipes to/from shell
        if (pipe(pipe_c) == -1 || pipe(pipe_p) == -1) {
            fprintf(stderr, "Pipe Error\n");
            exit(1);
        }

        // set up SIGPIPE handler
        signal(SIGPIPE, shell_shutdown);

        // create new process
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork Error\n");
            exit(1);
        } else if (pid == 0) { // child
            close(pipe_c[1]);
            close(pipe_p[0]);

            dup2(pipe_c[0], STDIN_FILENO);
            dup2(pipe_p[1], STDOUT_FILENO);
            dup2(pipe_p[1], STDERR_FILENO);

            close(pipe_c[0]);
            close(pipe_p[1]);

            if (execl(program, "sh", (char*)NULL) == -1) {
                fprintf(stderr, "Error running program: %s\n", program);
                exit(1);
            }
        } else { // parent
            close(pipe_c[0]);
            close(pipe_p[1]);
            
            struct pollfd fds[2]; // {keyboard, pipe}
            fds[0].fd = STDIN_FILENO;
            fds[1].fd = pipe_p[0];
            fds[0].events = POLLIN | POLLERR | POLLHUP;
            fds[1].events = POLLIN | POLLERR | POLLHUP;

            while (1)
            {
                if (poll(fds, 2, 0) == -1) {
                    fprintf(stderr, "Poll System Call Error\n");
                    exit(1);
                }

                if (fds[0].revents & POLLIN) { // keyboard
                    int i;
                    char c;
                    
                    char poll_buf[BUFFER_SIZE];
                    int bytes = read(STDIN_FILENO, &poll_buf, sizeof(char) * BUFFER_SIZE);
                    if (bytes == -1) {
                        fprintf(stderr, "Read Error (STDIN)\n");
                        exit(1);
                    }

                    for (i = 0; i < bytes; i++) {
                        c = poll_buf[i];
                        switch (c) {
                            case '\r': case '\n':
                                write(STDOUT_FILENO, &CRLF, sizeof(char) * 2);
                                c = '\n';
                                write(pipe_c[1], &c, sizeof(char));
                                break;
                            case 0x03: // ^C
                                kill(pid, SIGINT);
                                break;
                            case 0x04: // ^D
                                close(pipe_c[1]);
                                break;
                            default:
                                write(STDOUT_FILENO, &c, sizeof(char));
                                write(pipe_c[1], &c, sizeof(char));
                                break;
                        }
                    }
                } else if (fds[0].revents & (POLLERR | POLLHUP)) {
                    fprintf(stderr, "Polling Error (STDIN)\n");
                    exit(1);
                }

                if (fds[1].revents & POLLIN) { // shell
                    int i;
                    char c;
                    
                    char poll_buf[BUFFER_SIZE];
                    int bytes = read(pipe_p[0], &poll_buf, sizeof(char) * BUFFER_SIZE);
                    if (bytes == -1) {
                        fprintf(stderr, "Read Error (Shell)\n");
                        exit(1);
                    }

                    for (i = 0; i < bytes; i++) {
                        c = poll_buf[i];
                        switch (c) {
                            case '\n':
                                write(STDOUT_FILENO, &CRLF, sizeof(char) * 2);
                                break;
                            default:
                                write(STDOUT_FILENO, &c, sizeof(char));
                                break;
                        }
                    }
                } else if (fds[1].revents & (POLLERR | POLLHUP)) {
                    exit(0);
                }
            }
            exit(0);
        }
    }

    // print typed character(s)
    char buffer;
    while (read(STDIN_FILENO, &buffer, sizeof(char) * BUFFER_SIZE) > 0) {
        if (buffer == 0x04) // ^D
            exit(0);
        
        if (buffer == '\r' || buffer == '\n') { // CR, LF
            write(STDOUT_FILENO, &CRLF, sizeof(char) * 2);
        } else {
            write(STDOUT_FILENO, &buffer, sizeof(char));
        }
    }

    exit(0);
}
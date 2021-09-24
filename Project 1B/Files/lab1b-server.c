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
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <zlib.h>

int pid;
int pipe_p[2];
int pipe_c[2];
char CRLF[2] = {'\r', '\n'};
const int BUFFER_SIZE = 256;
z_stream to_server, to_client;

void get_exit_status()
{
    int exit_status;
    waitpid(pid, &exit_status, 0);
    fprintf(stderr, "SHELL EXIT SIGNAL=%d STATUS=%d\n", exit_status & 0xFF, exit_status / 256);
}

void shell_shutdown()
{
    kill(pid, SIGINT);
    exit(0);
}

void compression_end()
{
    inflateEnd(&to_server);
    deflateEnd(&to_client);
}

void compression_setup()
{
    to_client.zalloc = Z_NULL;
    to_client.zfree = Z_NULL;
    to_client.opaque = Z_NULL;
    if (deflateInit(&to_client, Z_DEFAULT_COMPRESSION) != Z_OK) {
        fprintf(stderr, "Server Error: deflateInit\n");
        exit(1);
    }

    to_server.zalloc = Z_NULL;
    to_server.zfree = Z_NULL;
    to_server.opaque = Z_NULL;
    if (inflateInit(&to_server) != Z_OK) {
        fprintf(stderr, "Server Error: inflateInit\n");
        exit(1);
    }

    atexit(compression_end);
}

int main(int argc, char *argv[])
{
    atexit(get_exit_status);

    int opt;
    int port;
    int pflag = 0, shflag = 0, cflag = 0;
    char* program;

    static struct option long_options[] = 
    {
        { "port",     required_argument, 0, 'p' },
        { "shell",    required_argument, 0, 's' },
        { "compress", no_argument,       0, 'c' },
        { 0,          0,                 0,  0  }
    };

    while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1)
    {
        switch(opt)
        {
            case 'p':
                pflag = 1;
                port = atoi(optarg);
                break;
            case 's':
                program = optarg;
                shflag = 1;
                break;
            case 'c':
                cflag = 1;
                compression_setup();
                break;
            default:
                fprintf(stderr, "Unrecognized argument! \nSupported options are: --port=[PORT#], --shell=[PROGRAM], --compress\n");
                exit(1);
        }
    }

    if (!pflag) {
        fprintf(stderr, "--port=[PORT#] is a mandatory option.\n");
        exit(1);
    }

    // socket code
    struct sockaddr_in s_addr, c_addr;
    int sfd, sfd_acc;
    unsigned int c_len;
    
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        fprintf(stderr, "Server Error: Socket\n");
        exit(1);
    }

    memset((char*) &s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    
    if ( bind(sfd, (struct sockaddr*) &s_addr, sizeof(s_addr)) < 0 ) {
        fprintf(stderr, "Server Error: Bind\n");
        exit(1);
    }

    if ( listen(sfd, 5) != 0 ) {
        fprintf(stderr, "Server Error: Listen\n");
        exit(1);
    }

    c_len = sizeof(c_addr);
    sfd_acc = accept(sfd, (struct sockaddr*) &c_addr, &c_len);
    if (sfd_acc < 0) {
        fprintf(stderr, "Server Error: Accept\n");
        exit(1);
    }

    // pipes
    if (pipe(pipe_c) == -1 || pipe(pipe_p) == -1) {
        fprintf(stderr, "Pipe Error\n");
        exit(1);
    }

    signal(SIGPIPE, shell_shutdown);
    // signal(SIGINT, shell_shutdown);

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

        if (shflag) {
            if (execl(program, "sh", (char*)NULL) == -1) {
                fprintf(stderr, "Error running program: %s\n", program);
                exit(1);
            }
        }
    } else { // parent
        close(pipe_c[0]);
        close(pipe_p[1]);

        struct pollfd fds[2];
        fds[0].fd = sfd_acc;
        fds[1].fd = pipe_p[0];
        fds[0].events = POLLIN | POLLERR | POLLHUP;
        fds[1].events = POLLIN | POLLERR | POLLHUP;

        while (1)
        {
            if (poll(fds, 2, 0) == -1) {
                fprintf(stderr, "Poll System Call Error\n");
                exit(1);
            }

            if (fds[0].revents & POLLIN) {
                int i;
                char c;
                
                char poll_buf[BUFFER_SIZE];
                char comp_buf[BUFFER_SIZE];
                int bytes = read(sfd_acc, &poll_buf, sizeof(char) * BUFFER_SIZE);
                if (bytes == -1) {
                    fprintf(stderr, "Server Error: Read\n");
                    exit(1);
                }

                if (cflag) {
                    to_server.avail_in = bytes;
                    to_server.next_in = (unsigned char*) poll_buf;
                    to_server.avail_out = BUFFER_SIZE;
                    to_server.next_out = (unsigned char*) comp_buf;
                    do {
                        if ( (inflate(&to_server, Z_SYNC_FLUSH)) != Z_OK ) {
                            fprintf(stderr, "Server Error: Compression (Inflate)\n");
                            exit(1);
                        }
                    } while (to_server.avail_in > 0);
                }

                for (i = 0; i < (cflag ? (int) (BUFFER_SIZE - to_server.avail_out) : bytes); i++) {
                    c = cflag ? comp_buf[i] : poll_buf[i];
                    switch (c) {
                        case '\r': case '\n':
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
                            write(pipe_c[1], &c, sizeof(char));
                            break;
                    }
                }
            } else if (fds[0].revents & (POLLERR | POLLHUP)) {
                fprintf(stderr, "Server Error: Polling\n");
                exit(1);
            }

            if (fds[1].revents & POLLIN) {
                int i;
                char c;
                
                char poll_buf[BUFFER_SIZE];
                char comp_buf[BUFFER_SIZE];
                int bytes = read(pipe_p[0], &poll_buf, sizeof(char) * BUFFER_SIZE);
                if (bytes == -1) {
                    fprintf(stderr, "Server Error: Read\n");
                    exit(1);
                }

                if (cflag) {
                    to_client.avail_in = bytes;
                    to_client.next_in = (unsigned char*) poll_buf;
                    to_client.avail_out = BUFFER_SIZE;
                    to_client.next_out = (unsigned char*) comp_buf;
                    do {
                        if ( (deflate(&to_client, Z_SYNC_FLUSH)) != Z_OK ) {
                            fprintf(stderr, "Client Error: Compression (Deflate)\n");
                            exit(1);
                        }
                    } while (to_client.avail_in > 0);
                    write(sfd_acc, comp_buf, BUFFER_SIZE - to_client.avail_out);
                } else {
                    for (i = 0; i < bytes; i++) {
                        c = poll_buf[i];
                        switch (c) {
                            case 0x03: // ^C
                                kill(pid, SIGINT);
                                break;
                            case 0x04: // ^D
                                close(pipe_c[1]);
                                break;
                            case '\n':
                                write(sfd_acc, &CRLF, sizeof(char) * 2);
                                break;
                            default:
                                write(sfd_acc, &c, sizeof(char));
                                break;
                        }
                    }
                }

                
            } else if (fds[1].revents & (POLLERR | POLLHUP)) {
                fprintf(stderr, "Server Error: Polling\n");
                exit(1);
            }
        }
    }

    exit(0);
}
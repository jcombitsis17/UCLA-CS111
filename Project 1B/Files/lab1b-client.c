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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <zlib.h>
#include <ulimit.h>

struct termios save_term;
const int BUFFER_SIZE = 256;
char CRLF[2] = {'\r', '\n'};
int sfd, lfd;
z_stream to_server, to_client;

void restore_term()
{
    close(sfd);
    close(lfd);
    tcsetattr(STDIN_FILENO, TCSANOW, &save_term);
}

void compression_end()
{
    inflateEnd(&to_client);
    deflateEnd(&to_server);
}

void compression_setup()
{
    to_client.zalloc = Z_NULL;
    to_client.zfree = Z_NULL;
    to_client.opaque = Z_NULL;
    if (inflateInit(&to_client) != Z_OK) {
        fprintf(stderr, "Client Error: inflateInit\n");
        exit(1);
    }

    to_server.zalloc = Z_NULL;
    to_server.zfree = Z_NULL;
    to_server.opaque = Z_NULL;
    if (deflateInit(&to_server, Z_DEFAULT_COMPRESSION) != Z_OK) {
        fprintf(stderr, "Client Error: deflateInit\n");
        exit(1);
    }

    atexit(compression_end);
}

int main(int argc, char *argv[])
{
    int opt;
    int port;
    int pflag = 0, lflag = 0, cflag = 0;

    static struct option long_options[] = 
    {
        { "port",     required_argument, 0, 'p' },
        { "log",      required_argument, 0, 'l' },
        { "compress", no_argument,       0, 'c' },
        { 0,      0,                     0,  0  }
    };

    while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1)
    {
        switch(opt)
        {
            case 'p':
                pflag = 1;
                port = atoi(optarg);
                break;
            case 'l':
                lflag = 1;
                // set max file size (according to spec)
                ulimit(UL_SETFSIZE, 10000);
                // setup log file
                lfd = creat(optarg, 0666);
                if (lfd < 0) {
                    fprintf(stderr, "Log File Error\n");
                    exit(1);
                }
                break;
            case 'c':
                cflag = 1;
                compression_setup();
                break;
            default:
                fprintf(stderr, "Unrecognized argument! \nSupported options are: --port=[PORT#], --log=[FILENAME], --compress\n");
                exit(1);
        }
    }

    if (!pflag) {
        fprintf(stderr, "--port=[PORT#] is a mandatory option.\n");
        exit(1);
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

    // socket code
    struct hostent* server;
    struct sockaddr_in addr;
    
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        fprintf(stderr, "Client Error: Socket\n");
        exit(1);
    }

    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr, "Client Error: Host\n");
        exit(1);
    }

    memset((char*) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    memcpy((char*) &addr.sin_addr.s_addr, (char*) server->h_addr, server->h_length);
    addr.sin_port = htons(port);

    if ( connect(sfd, (struct sockaddr*) &addr, sizeof(addr)) < 0 ) {
        fprintf(stderr, "Client Error: Connection\n");
        exit(1);
    }

    struct pollfd fds[2];
    fds[0].fd = STDIN_FILENO;
    fds[1].fd = sfd;
    fds[0].events = POLLIN | POLLERR | POLLHUP;
    fds[1].events = POLLIN | POLLERR | POLLHUP;

    while (1) {
        if (poll(fds, 2, 0) == -1) {
            fprintf(stderr, "Poll System Call Error\n");
            exit(1);
        }

        if (fds[0].revents & POLLIN) {
            int i;
            char c;
            
            char poll_buf[BUFFER_SIZE];
            char comp_buf[BUFFER_SIZE];
            int bytes = read(STDIN_FILENO, &poll_buf, sizeof(char) * BUFFER_SIZE);
            if (bytes == -1) {
                fprintf(stderr, "Client Error: Read\n");
                exit(1);
            }
            if (bytes == 0) {
                fprintf(stderr, "Error: Server Network Socket\r\n");
                exit(0);
            }

            for (i = 0; i < bytes; i++) {
                c = poll_buf[i];
                switch (c) {
                    case '\r': case '\n':
                        write(STDOUT_FILENO, &CRLF, sizeof(char) * 2);
                        break;
                    default:
                        write(STDOUT_FILENO, &c, sizeof(char));
                        break;
                }
            }

            if (!cflag) {
                write(sfd, poll_buf, bytes);
            } else {
                to_server.avail_in = bytes;
                to_server.next_in = (unsigned char*) poll_buf;
                to_server.avail_out = BUFFER_SIZE;
                to_server.next_out = (unsigned char*) comp_buf;
                do {
                    if ( (deflate(&to_server, Z_SYNC_FLUSH)) != Z_OK ) {
                        fprintf(stderr, "Client Error: Compression (Deflate)\n");
                        exit(1);
                    }
                } while (to_server.avail_in > 0);
                write(sfd, comp_buf, BUFFER_SIZE - to_server.avail_out);
            }

            if (lflag) {
                char sent_msg[16];
                if (cflag) {
                    sprintf(sent_msg, "SENT %d bytes: ", BUFFER_SIZE - to_server.avail_out);
                    write(lfd, sent_msg, strlen(sent_msg));
                    write(lfd, comp_buf, BUFFER_SIZE - to_server.avail_out);
                } else {
                    sprintf(sent_msg, "SENT %d bytes: ", bytes);
                    write(lfd, sent_msg, strlen(sent_msg));
                    write(lfd, poll_buf, bytes);
                }
                char n = '\n';
                write(lfd, &n, sizeof(char));
            }
        } else if (fds[0].revents & (POLLERR | POLLHUP)) {
            fprintf(stderr, "Client Error: Polling\n");
            exit(1);
        }

        if (fds[1].revents & POLLIN) {
            int i;
            char c;
            
            char poll_buf[BUFFER_SIZE];
            char comp_buf[BUFFER_SIZE];
            int bytes = read(sfd, &poll_buf, sizeof(char) * BUFFER_SIZE);
            if (bytes == -1) {
                fprintf(stderr, "Client Error: Read\n");
                exit(1);
            }
            if (bytes == 0) {
                fprintf(stderr, "Error: Server Network Socket\r\n");
                exit(0);
            }

            if (cflag) {
                to_client.avail_in = bytes;
                to_client.next_in = (unsigned char*) poll_buf;
                to_client.avail_out = BUFFER_SIZE;
                to_client.next_out = (unsigned char*) comp_buf;
                do {
                    if ( (inflate(&to_client, Z_SYNC_FLUSH)) != Z_OK ) {
                        fprintf(stderr, "Client Error: Compression (Inflate)\n");
                        exit(1);
                    }
                } while (to_client.avail_in > 0);
                write(STDOUT_FILENO, comp_buf, BUFFER_SIZE - to_client.avail_out);
            } else {
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
            }

            if (lflag && bytes > 0) {
                char recv_msg[20];
                sprintf(recv_msg, "RECEIVED %d bytes: ", bytes);
                write(lfd, recv_msg, strlen(recv_msg));
                write(lfd, poll_buf, bytes);
                char n = '\n';
                write(lfd, &n, sizeof(char));
            }
        } else if (fds[1].revents & (POLLERR | POLLHUP)) {
            fprintf(stderr, "Client Error: Polling\n");
            exit(1);
        }
    }

    exit(0);
}


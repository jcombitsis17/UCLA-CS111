/*
NAME: Jordan Combitsis
EMAIL: jcombitsis17@gmail.com
ID: 004921527
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <pthread.h>
#include <sched.h>
#include <string.h>

long long n_threads, n_iterations;
long long counter;
struct timespec start_time, end_time;
int opt_yield;
char sync_option;
pthread_mutex_t mutex;
static int lock = 0;

int sync_check(char snc)
{
    return (snc == 'm' || snc == 's' || snc == 'c');
}

void add(long long *pointer, long long value) {
    long long sum = *pointer + value;
    if (opt_yield)
        sched_yield();
    *pointer = sum;
}

void add_option(int one)
{
    switch (sync_option)
    {
        case 'm':
            pthread_mutex_lock(&mutex);
            add(&counter, one);
            pthread_mutex_unlock(&mutex);
            break;
        case 's':
            while (__sync_lock_test_and_set(&lock, 1));
            add(&counter, one);
            __sync_lock_release(&lock);
            break;
        case 'c': ;
            long long oldval, newval;
            do {
                oldval = counter;
                newval = oldval + one;
                if (opt_yield)
                    sched_yield();
            } while (__sync_val_compare_and_swap(&counter, oldval, newval) != oldval);
            break;
        default:
            add(&counter, one);
            break;
    }
}

void thread_func()
{
    for (int i = 0; i < n_iterations; i++) {
        add_option(1);
        add_option(-1);
    }
}

int main(int argc, char *argv[])
{
    n_threads = 1;
    n_iterations = 1;
    counter = 0;
    opt_yield = 0;
    sync_option = 0;
    
    static struct option long_options[] = 
    {
        { "threads",    required_argument, 0, 't' },
        { "iterations", required_argument, 0, 'i' },
        { "yield",      no_argument,       0, 'y' },
        { "sync",       required_argument, 0, 's' },
        { 0,            0,                 0,  0  }
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1)
    {
        switch(opt)
        {
            case 't':
                n_threads = atoi(optarg);
                break;
            case 'i':
                n_iterations = atoi(optarg);
                break;
            case 'y':
                opt_yield = 1;
                break;
            case 's':
                if (strlen(optarg) != 1 || !sync_check(optarg[0])) {
                    fprintf(stderr, "Invalid sync option. Must be exactly one letter and one of: m, s, or c\n");
                    exit(1);
                }
                sync_option = optarg[0];
                break;
            default:
                fprintf(stderr, "Unrecognized argument! \nSupported options are: \
                                 --threads=[NUM], --iterations=[NUM], --yield, --sync=[OPT]\n");
                exit(1);
        }
    }

    if (sync_option == 'm') {
        if (pthread_mutex_init(&mutex, NULL) != 0) {
            fprintf(stderr, "Error: pthread_mutex_init\n");
            exit(1);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    pthread_t tid[n_threads];
    for (int i = 0; i < n_threads; i++) {
        if (pthread_create(&tid[i], NULL, (void*) &thread_func, NULL) != 0) {
            fprintf(stderr, "Error: pthread_create\n");
            exit(1);
        }
    }
    for (int i = 0; i < n_threads; i++) {
        if (pthread_join(tid[i], NULL) != 0) {
            fprintf(stderr, "Error: pthread_join\n");
            exit(1);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    long long n_ops = n_threads * n_iterations * 2;
    long long total_runtime = (1000000000 * (end_time.tv_sec - start_time.tv_sec)) + (end_time.tv_nsec - start_time.tv_nsec);
    long long avg_time_per_op = total_runtime / n_ops;
    
    fprintf(stdout, "add-");
    if (opt_yield)
        fprintf(stdout, "yield-");
    if (sync_option) fprintf(stdout, "%c", sync_option);
    else             fprintf(stdout, "none");
    fprintf(stdout, ",%lld,%lld,%lld,%lld,%lld,%lld\n", 
            n_threads, n_iterations, n_ops, total_runtime, avg_time_per_op, counter);

    if (sync_option == 'm')
        pthread_mutex_destroy(&mutex);

    exit(0);
}
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
#include <string.h>
#include <signal.h>
#include "SortedList.h"


long long n_threads, n_iterations, n_elements;
SortedList_t *list;
SortedListElement_t **list_elements;
struct timespec start_time, end_time;
char sync_option;
pthread_mutex_t mutex;
static int s_lock = 0;

void lock_unlock(int lock)
{
    if (lock) {
        if (sync_option == 'm')
            pthread_mutex_lock(&mutex);
        else if (sync_option == 's')
            while (__sync_lock_test_and_set(&s_lock, 1));
    } else {
        if (sync_option == 'm')
            pthread_mutex_unlock(&mutex);
        else if (sync_option == 's')
            __sync_lock_release(&s_lock);
    }
}

void thread_func(void* thread)
{
    if (sync_option) lock_unlock(1);

    // insert
    int loc = *(int*) thread;
    for (int i = 0; i < n_iterations; i++) {
        SortedList_insert(list, &list_elements[loc][i]);
    }

    // get length
    if (SortedList_length(list) < n_iterations) {
        fprintf(stderr, "Error: list length\n");
        exit(2);
    }

    // delete
    SortedListElement_t *e;
    for (int i = 0; i < n_iterations; i++) {
        e = SortedList_lookup(list, list_elements[loc][i].key);
        if (e == NULL) {
            fprintf(stderr, "Error: list lookup\n");
            exit(2);
        }
        if (SortedList_delete(e) != 0) {
            fprintf(stderr, "Error: list delete\n");
            exit(2);
        }
    }

    if (sync_option) lock_unlock(0);
}

void initList()
{
    list = malloc(sizeof(SortedList_t));
    list->prev = NULL;
    list->next = NULL;

    n_elements = n_threads * n_iterations;
    list_elements = malloc(sizeof(SortedListElement_t) * n_elements);
    for (int i = 0; i < n_threads; i++)
        list_elements[i] = malloc(sizeof(SortedListElement_t) * n_iterations);

    srand(time(NULL));
    for (int i = 0; i < n_threads; i++) {
        for (int j = 0; j < n_iterations; j++) {
            char *randkey = malloc(sizeof(char) * 4);
            for (int k = 0; k < 3; k++) {
                randkey[k] = 'a' + rand() % 26;
            }
            randkey[3] = '\0';
            list_elements[i][j].key = randkey;
            list_elements[i][j].prev = NULL;
            list_elements[i][j].next = NULL;
        }
    }
}

void catch_segfault()
{
    fprintf(stderr, "Segmentation Fault (caught)\n");
    exit(2);
}

void freeMemory()
{
    for (int i = 0; i < n_threads; i++)
        for (int j = 0; j < n_iterations; j++)
            free((void*) list_elements[i][j].key);
    for (int i = 0; i < n_threads; i++)
        free(list_elements[i]);
    free(list_elements);
    free(list);
}

int main(int argc, char *argv[])
{
    signal(SIGSEGV, catch_segfault);

    n_threads = 1;
    n_iterations = 1;
    opt_yield = 0;
    sync_option = 0;
    
    static struct option long_options[] = 
    {
        { "threads",    required_argument, 0, 't' },
        { "iterations", required_argument, 0, 'i' },
        { "yield",      required_argument, 0, 'y' },
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
                for (size_t i = 0; i < strlen(optarg); i++) {
                    switch (optarg[i]) {
                        case 'i':
                            opt_yield |= INSERT_YIELD;
                            break;
                        case 'd':
                            opt_yield |= DELETE_YIELD;
                            break;
                        case 'l':
                            opt_yield |= LOOKUP_YIELD;
                            break;
                        default:
                            fprintf(stderr, "Invalid yield option. Must be one or more of: i, d, l\n");
                            exit(1);
                            break;
                    }
                }
                break;
            case 's':
                if (strlen(optarg) != 1 || !(optarg[0] == 'm' || optarg[0] == 's')) {
                    fprintf(stderr, "Invalid sync option. Must be exactly one letter and either m or s\n");
                    exit(1);
                }
                sync_option = optarg[0];
                break;
            default:
                fprintf(stderr, "Unrecognized argument! \nSupported options are: \
                                 --threads=[NUM], --iterations=[NUM], --yield=[idl], --sync=[s|m]\n");
                exit(1);
        }
    }

    if (sync_option == 'm') {
        if (pthread_mutex_init(&mutex, NULL) != 0) {
            fprintf(stderr, "Error: pthread_mutex_init\n");
            exit(1);
        }
    }

    initList();

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    pthread_t *tid = malloc(sizeof(pthread_t) * n_threads);
    int *pos = malloc(sizeof(int) * n_threads);
    for (int i = 0; i < n_threads; i++) {
        pos[i] = i;
        pos[i] = i;
        if ( pthread_create(&tid[i], NULL, (void*) &thread_func, &pos[i]) != 0) {
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

    if (SortedList_length(list) != 0) {
        fprintf(stderr, "Error: list length (after thread completion)\n");
        exit(2);
    }

    long long n_ops = n_threads * n_iterations * 3;
    long long total_runtime = (1000000000 * (end_time.tv_sec - start_time.tv_sec)) + (end_time.tv_nsec - start_time.tv_nsec);
    long long avg_time_per_op = total_runtime / n_ops;
    
    fprintf(stdout, "list-");
    int yield = 0;
    if (opt_yield & INSERT_YIELD) {
        fprintf(stdout, "i");
        yield = 1;
    }
    if (opt_yield & DELETE_YIELD) {
        fprintf(stdout, "d");
        yield = 1;
    }
    if (opt_yield & LOOKUP_YIELD) {
        fprintf(stdout, "l");
        yield = 1;
    }
    if (!yield)
        fprintf(stdout, "none");
    if (sync_option) fprintf(stdout, "-%c", sync_option);
    else             fprintf(stdout, "-none");
    fprintf(stdout, ",%lld,%lld,1,%lld,%lld,%lld\n", 
            n_threads, n_iterations, n_ops, total_runtime, avg_time_per_op);
    
    if (sync_option == 'm')
        pthread_mutex_destroy(&mutex);
    
    freeMemory();

    exit(0);
}

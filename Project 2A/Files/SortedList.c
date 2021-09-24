/*
NAME: Jordan Combitsis
EMAIL: jcombitsis17@gmail.com
ID: 004921527
*/

#include "SortedList.h"
#include <stdio.h>
#include <sched.h>
#include <string.h>

int opt_yield;

void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
    if (list == NULL || element == NULL)
        return;

    SortedListElement_t *curr = list->next;
    SortedListElement_t *prev = list;
    
    if (opt_yield & INSERT_YIELD)
        sched_yield();

    if (curr == NULL) { // empty list case
        list->next = element;
        element->next = NULL;
        element->prev = list;
    } else { // normal case
        while (curr != NULL) {
            if (curr->key == NULL)
                break;
            if (strcmp(element->key, curr->key) <= 0)
                break;
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            prev->next = element;
            element->next = NULL;
            element->prev = prev;
        } else {
            element->next = curr;
            element->prev = curr->prev;
            curr->prev->next = element;
            curr->prev = element;
        }
    }
}

int SortedList_delete( SortedListElement_t *element)
{
    if (element == NULL)
        return 1;

    if ((element->next != NULL && element->next->prev != element) || 
        (element->prev != NULL && element->prev->next != element))
    {
        return 1;
    }

    if (opt_yield & DELETE_YIELD)
        sched_yield();

    if (element->prev != NULL)
        element->prev->next = element->next;
    if (element->next != NULL)
        element->next->prev = element->prev;

    return 0;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
    if (list == NULL || key == NULL)
        return NULL;
        
    SortedListElement_t *curr = list->next;

    if (curr == NULL)
        return NULL;

    if (opt_yield & LOOKUP_YIELD)
        sched_yield();

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0)
            return curr;
        curr = curr->next;
    }

    return NULL;
}

int SortedList_length(SortedList_t *list)
{
    if (list == NULL)
        return -1;

    SortedListElement_t *curr = list->next;
    
    if (opt_yield & LOOKUP_YIELD)
        sched_yield();

    int len = 0;
    while (curr != NULL) {
        if ((curr->next != NULL && curr->next->prev != curr) ||
            (curr->prev != NULL && curr->prev->next != curr))
        {
            return -1;
        }
        curr = curr->next;
        len++;
    }

    return len;
}

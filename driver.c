/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"

#define SIZE    100

static int taskID = 1;
struct node *head = NULL;

void add(char *name, int priority, int burst){
    Task *toAdd = (Task *) malloc(sizeof(Task));
    toAdd->name = name;
    toAdd->priority = priority;
    toAdd->burst = burst;
    toAdd->tid = taskID++;

    if(toAdd == NULL){
        free(toAdd);
        return;
    }

    struct node *toInsert = (struct node*) malloc(sizeof(struct node));
    toInsert->task = toAdd;
    toInsert->next = NULL;
    
    if(head == NULL){
        head = toInsert;
        insert(&toInsert, toAdd);
    } else {
        struct node *travel = head;
        while(travel->next != NULL){
            travel = travel->next;
        }
        travel->next = toInsert;
    }
}

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    in = fopen(argv[1],"r");
    
    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add(name,priority,burst);

        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    schedule(head);

    return 0;
}
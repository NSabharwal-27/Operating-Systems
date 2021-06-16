#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cpu.h"
#include "task.h"
#include "list.h"
#include "schedulers.h"
#define INT_MAX 2147483647;

int getSize(struct node *head);

void schedule(struct node *head){
    int sizeOf = getSize(head);
    int iteration = 0;
    int waiTime[sizeOf - 1];
    float wait = 0;
    float sum = 0;
    int burstTotal = 0;
    int smallest = INT_MAX;
    struct node *curr = head;        
    struct node *toExec;

    while(iteration <= sizeOf){

        while(curr != NULL){
            if(smallest > curr->task->burst){
                smallest = curr->task->burst;
                toExec = curr;
            }
            curr = curr->next;
        }

        run(toExec->task, toExec->task->burst);
        burstTotal += toExec->task->burst;
        waiTime[iteration] = burstTotal;
        delete(&head, toExec->task);
        curr = head;
        toExec = NULL;
        smallest = INT_MAX;
        iteration++;
    }

    burstTotal = 0;
    for(int i = 0; i < iteration; i++){
        if (i != iteration - 1){
            wait += waiTime[i];
        }
        sum += waiTime[i];
    }

    printf("Average turn around time: %.3f\n", sum / iteration);
    printf("Average wait time: %.3f\nAverage response time: %.3f\n", wait / iteration, wait / iteration);
}

int getSize(struct node *head){
    int count = 0;
    struct node *counter = head;
    while(counter->next != NULL){
        count++;
        counter = counter->next;
    }
    return count;
}

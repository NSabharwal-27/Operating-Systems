#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "task.h"
#include "list.h"
#include "schedulers.h"

int lengthOf(struct node *head);

void schedule(struct node *head){
    struct node *ref = head;
    int size = lengthOf(head);
    int timeElapsed[size];
    int bursTotal = 0;
    float wait = 0;
    float turnTime = 0;
    int level = 10;
    int index = 0;

    while(level > 0){
        if(ref->task->priority == level){
            run(ref->task, ref->task->burst);
            bursTotal += ref->task->burst;
            timeElapsed[index] = bursTotal;
            index++;
        }
        if(ref->next == NULL){
            ref = head;
            level--;
        } else {
            ref = ref->next;
        }
    }

    for (int i = 0; i < size; i++){
        if(i < size - 1){
            wait += timeElapsed[i];
        }
        turnTime += timeElapsed[i];
    }
    
    printf("Average wait time is: %.3f\nAverage response time is: %.3f\n", wait / size, wait / size);
    printf("Average turn around time is: %.3f\n", turnTime / size);
}

int lengthOf(struct node *head){
    struct node *tmp = head;
    int toReturn = 0;
    while(tmp != NULL){
        toReturn++;
        tmp = tmp->next;
    }
    return toReturn;
}
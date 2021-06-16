#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "task.h"
#include "list.h"
#include "schedulers.h"

void schedule(struct node *head){
    struct node *travel = head;
    double waiTime = 0.0;
    double turnTime = 0.0;
    int burstSum = 0;
    int length = 0;

    while(travel != NULL){
        burstSum += travel->task->burst;
       if(travel->next != NULL){
           //printf("total execution time so far: %d\n", totalTime);
           waiTime = waiTime + burstSum;
       }
       run(travel->task, travel->task->burst);
       travel = travel->next;
       length++;
    }

    turnTime = (waiTime - burstSum) / length;
    waiTime = (waiTime) / length;

    printf("Average wait time: %0.3f\n", waiTime);
    printf("Average turn around time: %0.3f\n", turnTime);
    printf("Average response time: %0.3f\n", waiTime);
}

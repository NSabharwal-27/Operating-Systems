#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "task.h"
#include "list.h"
#include "schedulers.h"

int convert2Circle(struct node *head);


void schedule(struct node *head){
    struct node *travel = head;
    int count = convert2Circle(head);
    float turn = 0;
    int completionTime[count];
    int burstTime = 0;
    int i = 0;

    while(count > 0){
        if(travel->task->burst <= QUANTUM){
            burstTime += travel->task->burst;
            run(travel->task, travel->task->burst);
            delete(&head, (travel->task));
            count--;
            completionTime[i] = burstTime;
            i++;
        } else {
            burstTime += QUANTUM; 
            run(travel->task, QUANTUM);
            travel->task->burst = (travel->task->burst - QUANTUM);
        }
        travel = travel->next;
    }

    for(int j = 0; j < i; j++){
        turn += completionTime[j];
    }


    printf("Average Turn Around time: %.3f\n", turn/(i + 1));
    printf("Average Wait Time: %.3f \nAverage Response Time: %.3f\n", (turn - burstTime) / (i + 1), (turn  - burstTime) / (i + 1));
}

int convert2Circle(struct node *head){
    struct node *tmp = head;
    int toReturn = 0;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    toReturn = tmp->task->tid + 1;
    tmp->next = head;
    tmp = tmp->next;
    return toReturn;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "task.h"
#include "list.h"
#include "schedulers.h"

struct node *priorityHead = NULL;

void addTask(Task *task);
void roundRobin(int length);

void schedule(struct node *head)
{
    struct node *travel = head;
    int length = 0;
    int level = 10;

    while (level > 0)
    {
        if (travel->task->priority == level)
        {
            insert(&priorityHead, travel->task);
            delete (&head, travel->task);
        }
        if (travel->next == NULL)
        { // reached end of list all tasks with priority added to new list
            //time to round robin the new list
           while(priorityHead != NULL){
               if (priorityHead->task->burst <= QUANTUM)
               {
                   run(priorityHead->task, priorityHead->task->burst);
                   delete (&priorityHead, priorityHead->task);
                   length--;
               }
               else
               {
                   run(priorityHead->task, QUANTUM);
                   priorityHead->task->burst -= QUANTUM;
                   delete (&priorityHead, priorityHead->task);
                   insert(&priorityHead, priorityHead->task);
               }
           }

        }
        printf("here");
        travel = travel->next == NULL ? head : travel->next;
    }
}


/*void schedule(struct node *head){
    struct node *travel = head;
    int level = 10;

    while (level > 0){
        if (travel->task->priority == level) {
            struct node *search = travel;
            while(1){
                if(search->task->burst <= QUANTUM && search->task->priority == level){
                    run(search->task, search->task->burst);
                    search->task->burst -= QUANTUM;
                    delete(&head, search->task);
                    break;
                } else {
                    if(search->task->priority == level){
                        run(search->task, QUANTUM);
                        search->task->burst -= QUANTUM;
                        delete(&head, search->task);
                        insert(&head, search->task);
                    }
                    if (search->next == NULL){
                        search = head;
                    } else {
                        search = search->next;
                    }
                }
            }
        } 
        if (travel->next == NULL) {
            travel = head;
            level--;
        }
        travel = travel->next;
    }
}
*/
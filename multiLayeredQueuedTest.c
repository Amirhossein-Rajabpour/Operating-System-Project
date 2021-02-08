#include "types.h"
#include "stat.h"
#include "user.h"

// number of children created
#define NUM_CHILDREN 40

int main(int argc, char *argv[])
{

    int result = changePolicy(5);
    if (result == 5)
    {
        printf(1, "Policy changed successfully!\n");
    }
    else
    {
        printf(1, "Policy change failed!\n");
    }

    int turnarounds[NUM_CHILDREN] = {0}; // turnaround times for each child
    int waitings[NUM_CHILDREN] = {0};    // waiting times for each child
    int CBTs[NUM_CHILDREN] = {0};        // CBTs for each child

    int original_pid = getpid();
    int indexInQueue = 0;
    int child_num = -1;

    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        if (fork() == 0) // Child
        {
            if (i == 0)
            {
                changeQueue(1);
                indexInQueue = 0;
            }
            else if (i == 10)
            {
                changeQueue(2);
                indexInQueue = 0;
            }
            else if (i == 20)
            {
                changeQueue(3);
                indexInQueue = 0;
            }            
            else if (i == 30)
            {
                changeQueue(4);
                indexInQueue = 0;
            }
            child_num = i + 1;
            cur_queue[indexInQueue] = getpid();
            printf(1, "i: %d, index in queue is: %d\n", i, indexInQueue);
            indexInQueue++;
            break;
        }
    }


    if (getpid() != original_pid)
    {
        for (int i = 1; i <= 200; i++)
            printf(1, "/%d/: /%d/\n", child_num, i);

        exit();
    }

    else
    {
        printf(1, "\n\n\n*****Times for each child*****\n");

        // while (wait() > 0)
        // {
        //     printf(1, "wow");
        // }

        int *procTimes = malloc(4 * sizeof(int));
        int i = 0;
        while (customWait(procTimes) > 0)
        {
            printf(1, "YEKI DIGE GEREFTAM\n");
            int childTurnaround = procTimes[0];
            int childWaiting = procTimes[1];
            int childCBT = procTimes[2];

            turnarounds[i] = childTurnaround;
            waitings[i] = childWaiting;
            CBTs[i] = childCBT;
            i++;
        }

        printf(1, "%d%d%d", turnarounds[0], waitings[0], CBTs[0]);
    }
    exit();
}
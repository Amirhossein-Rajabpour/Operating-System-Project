#include "types.h"
#include "stat.h"
#include "user.h"

// number of children created
#define NUM_CHILDREN 30

int main(int argc, char *argv[])
{
    int result = changePolicy(2);
    if (result == 0)
    {
        printf(1, "Policy changed successfully!\n");
    }
    else
    {
        printf(1, "Policy change failed!\n");
    }

    int priorities[NUM_CHILDREN] = {0};  // priorites for each child
    int turnarounds[NUM_CHILDREN] = {0}; // turnaround times for each child
    int waitings[NUM_CHILDREN] = {0};    // waiting times for each child
    int CBTs[NUM_CHILDREN] = {0};        // CBTs for each child

    int original_pid = getpid();
    int child_num = -1;
    int priority = -1;

    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        if (fork() == 0) // Child
        {
            child_num = i + 1;
            // priority = 6 - (i / 5);
            priority = (i / 5) + 1;
            printf(1, "i: %d, priority: %d\n", i, priority);
            setPriority(priority);
            break;
        }
    }

    if (getpid() != original_pid)
    {
        for (int i = 1; i <= 250; i++)
            printf(1, "/%d/: /%d/\n", child_num, i);
    }

    else
    {
        printf(1, "\n\n\n*****Times for each child*****\n");
        int *procTimes = {0};
        int i = 0;
        while (customWait(procTimes) > 0)
        {
            customWait(procTimes);
            printf(1, "YEKI DIGE GEREFTAM\n");
            int childPriority = procTimes[3];
            int childTurnaround = procTimes[0];
            int childWaiting = procTimes[1];
            int childCBT = procTimes[2];

            priorities[i] = childPriority;
            turnarounds[i] = childTurnaround;
            waitings[i] = childWaiting;
            CBTs[i] = childCBT;
            i++;
        }

        printf(1, "%d%d%d%d", priorities[0], turnarounds[0], waitings[0], CBTs[0]);
    }

    while (wait() != -1)
        ;

    exit();
}
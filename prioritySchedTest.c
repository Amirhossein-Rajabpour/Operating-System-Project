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

    int turnaroundsSum[6] = {0}; // Sum of turnaround times for each priority class
    int waitingsSum[6] = {0};    // Sum of waiting times for each priority class
    int CBTsSum[6] = {0};        // Sum of CBTs for each priority class

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
        printf(1, "*****Times for each child*****\n\n");

        int *procTimes = {0};
        while (customWait(procTimes) > 0)
        {
            int childPriority = procTimes[3];
            int childTurnaround = procTimes[0];
            int childWaiting = procTimes[1];
            int childCBT = procTimes[2];

            printf(1, "Child with priority: %d, -> Turnaround time: %d\n", childPriority, childTurnaround);
            printf(1, "Child with priority: %d, -> Waiting time: %d\n", childPriority, childWaiting);
            printf(1, "Child with priority: %d, -> CBT: %d\n", childPriority, childCBT);
            printf(1, "\n\n");

            turnaroundsSum[childPriority - 1] += procTimes[0];
            waitingsSum[childPriority - 1] += procTimes[1];
            CBTsSum[childPriority - 1] += procTimes[2];
        }

        printf(1, "*****Average times for each priority class*****\n\n");

        for (int i = 0; i < 6; i++)
        {
            printf(1, "Priority class: %d, Average turnaround time: %d\n", i + 1, turnaroundsSum[i] / NUM_CHILDREN);
            printf(1, "Priority class: %d, Average waiting time: %d\n", i + 1, waitingsSum[i] / NUM_CHILDREN);
            printf(1, "Priority class: %d, Average CBT: %d\n", i + 1, CBTsSum[i] / NUM_CHILDREN);
            printf(1, "\n\n");
        }

        printf(1, "*****Average times in total*****\n\n");

        int totalTurnaround = 0;
        int totalWaiting = 0;
        int totalCBT = 0;
        for (int i = 0; i < 6; i++)
        {
            totalTurnaround += turnaroundsSum[i];
            totalWaiting += waitingsSum[i];
            totalCBT += CBTsSum[i];
        }
        printf(1, "Total average turnaround time: %d\n", totalTurnaround / NUM_CHILDREN);
        printf(1, "Total average waiting time: %d\n", totalWaiting / NUM_CHILDREN);
        printf(1, "Total average CBT: %d\n", totalCBT / NUM_CHILDREN);
    }

    while (wait() != -1)
        ;

    exit();
}
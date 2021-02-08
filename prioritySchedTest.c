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
        for (int i = 1; i <= 50; i++)
            printf(1, "/%d/: /%d/\n", child_num, i);
    }

    else
    {
        int priorities[NUM_CHILDREN] = {0};  // priorites for each child
        int turnarounds[NUM_CHILDREN] = {0}; // turnaround times for each child
        int waitings[NUM_CHILDREN] = {0};    // waiting times for each child
        int CBTs[NUM_CHILDREN] = {0};        // CBTs for each child

        printf(1, "\n\n\n*****Times for each child*****\n");
        int *procTimes = malloc(4 * sizeof(int));
        int i = 0;
        while (customWait(procTimes) > 0)
        {
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

        printf(1, "\n\n\n*****Times for each child*****\n");
        for (int j = 0; j < NUM_CHILDREN; j++)
        {
            printf(1, "Child with priority %d -> Turnaround: %d, Waiting: %d, CBT: %d\n",
                   priorities[j], turnarounds[j], waitings[j], CBTs[j]);
        }

        printf(1, "\n\n\n*****AVG Times for each priority class*****\n");
        int turnaroundsPerClass[6] = {0};
        int waitingsPerClass[6] = {0};
        int CBTsPerClass[6] = {0};
        for (int j = 0; j < NUM_CHILDREN; j++)
        {
            int childPriority = priorities[j];
            turnaroundsPerClass[childPriority - 1] += turnarounds[j];
            waitingsPerClass[childPriority - 1] += waitings[j];
            CBTsPerClass[childPriority - 1] += CBTs[j];
        }
        for (int j = 0; j < 6; j++)
        {
            printf(1, "Priority class: %d -> AVG Turnaround: %d, AVG Waiting: %d, AVG CBT: %d\n",
                   j + 1,
                   turnaroundsPerClass[j] / (NUM_CHILDREN / 6),
                   waitingsPerClass[j] / (NUM_CHILDREN / 6),
                   CBTsPerClass[j] / (NUM_CHILDREN / 6));
        }

        printf(1, "\n\n\n*****AVG Times in total*****\n");
        int turnaroundsSum = 0;
        int waitingsSum = 0;
        int CBTsSum = 0;
        for (int j = 0; j < NUM_CHILDREN; j++)
        {
            turnaroundsSum += turnarounds[j];
            waitingsSum += waitings[j];
            CBTsSum += CBTs[j];
        }
        printf(1, "Total -> AVG Turnaround: %d, AVG Waiting: %d, AVG CBT: %d\n",
               turnaroundsSum / NUM_CHILDREN,
               waitingsSum / NUM_CHILDREN,
               CBTsSum / NUM_CHILDREN);
    }

    while (wait() != -1)
        ;

    exit();
}
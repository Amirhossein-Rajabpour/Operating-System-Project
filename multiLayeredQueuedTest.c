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

    int original_pid = getpid();
    int child_num = -1;

    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        if (fork() == 0) // Child
        {
            setQueue((i / 10) + 1);
            if (i > 9 && i < 20)
            {
                setPriority(i % 6 + 1);
            }
            else if (i > 20 && i < 30)
            {
                setPriority(i % 6 + 1);
            }
            child_num = i + 1;
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
        int queues[NUM_CHILDREN] = {0};      // priorites for each child
        int turnarounds[NUM_CHILDREN] = {0}; // turnaround times for each child
        int waitings[NUM_CHILDREN] = {0};    // waiting times for each child
        int CBTs[NUM_CHILDREN] = {0};        // CBTs for each child

        printf(1, "\n\n\n*****Times for each child*****\n");
        int *procTimes = malloc(4 * sizeof(int));
        int i = 0;
        while (customWait(procTimes) > 0)
        {
            int childQueue = procTimes[3];
            int childTurnaround = procTimes[0];
            int childWaiting = procTimes[1];
            int childCBT = procTimes[2];

            queues[i] = childQueue;
            turnarounds[i] = childTurnaround;
            waitings[i] = childWaiting;
            CBTs[i] = childCBT;
            i++;
        }

        printf(1, "\n\n\n*****Times for each child*****\n");
        for (int j = 0; j < NUM_CHILDREN; j++)
        {
            printf(1, "Child with priority %d -> Turnaround: %d, Waiting: %d, CBT: %d\n",
                   queues[j], turnarounds[j], waitings[j], CBTs[j]);
        }

        printf(1, "\n\n\n*****AVG Times for each queue*****\n");
        int turnaroundsPerQueue[4] = {0};
        int waitingsPerQueue[4] = {0};
        int CBTsPerQueue[4] = {0};
        for (int j = 0; j < NUM_CHILDREN; j++)
        {
            int childQueue = queues[j];
            turnaroundsPerQueue[childQueue - 1] += turnarounds[j];
            waitingsPerQueue[childQueue - 1] += waitings[j];
            CBTsPerQueue[childQueue - 1] += CBTs[j];
        }
        for (int j = 0; j < 4; j++)
        {
            printf(1, "Queue: %d -> AVG Turnaround: %d, AVG Waiting: %d, AVG CBT: %d\n",
                   j + 1,
                   turnaroundsPerQueue[j] / (NUM_CHILDREN / 4),
                   waitingsPerQueue[j] / (NUM_CHILDREN / 4),
                   CBTsPerQueue[j] / (NUM_CHILDREN / 4));
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
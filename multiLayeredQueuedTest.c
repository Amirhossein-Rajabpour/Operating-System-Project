#include "types.h"
#include "stat.h"
#include "user.h"

// number of children created
#define NUM_CHILDREN 40

int main(int argc, char *argv[])
{
    int *first_queue = {0};
    int *second_queeu = {0};
    int *third_queue = {0};
    int *forth_queue = {0};

    int result = changePolicy();
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



    while (wait() != -1)
        ;

    exit();
}
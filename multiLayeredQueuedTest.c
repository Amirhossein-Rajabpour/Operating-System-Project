#include "types.h"
#include "stat.h"
#include "user.h"

// number of children created
#define NUM_CHILDREN 40

int *cur_queue = {0};
int *first_queue = {0};
int *second_queeu = {0};
int *third_queue = {0};
int *forth_queue = {0};

void changeQueue(int queueNumber)
{
    switch(queueNumber)
    {
        case 1:
            cur_queue = first_queue;
            break;

        case 2:
            cur_queue = second_queue;
            break;

        case 3:
            cur_queue = third_queue;
            break;

        case 4:
            cur_queue = forth_queue;
            break;
    }
}

int main(int argc, char *argv[])
{

    int result = changePolicy();
    if (result == )
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
            if (i == 0)
                changeQueue(1);
            else if (i == 10)
                changeQueue(2);
            else if (i == 20)
                changeQueue(3);
            else if (i == 30)
                changeQueue(4); 

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
#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    int original_pid = getpid();

    int num_children;
    int *children_pid = malloc(64 * sizeof(int));

    for (int i = 0; i < 3; i++)
    {
        fork();
    }

    num_children = getChildren(children_pid);

    if (getpid() == original_pid)
    {
        printf(1, "Original process ID: %d\n", original_pid);
        printf(1, "Number of children: %d\n", num_children);
        printf(1, "Child proccesses: [");
        for (int i = 0; i < num_children; i++)
        {
            printf(1, "%d, ", children_pid[i]);
        }
        printf(1, "]\n");
    }

    while (wait() != -1)
        ;

    exit();
}
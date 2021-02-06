#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    changePolicy(0);
    int original_pid = getpid();
    int child_num = -1;
    int priority = -1;

    for (int i = 0; i < 30; i++)
    {
        if (fork() == 0)
        {
            child_num = i;
            priority = 6 - (int)(i / 5);
            printf(1, "i: %d, priority: %d\n", i, priority);
            setPriority(priority);
            break;
        }
    }

    if (getpid() != original_pid)
    {
        for (int i = 1; i <= 250; i++)
            printf(1, "/%d/: /%d/\n", child_num, i);

        int pid = getpid();
        printf(1, "Turnaround time for process /%d/ is :%d\n", pid, getTurnAroundTime(pid));
        printf(1, "Waiting time for process /%d/ is :%d\n", pid, getWaitingTime(pid));
        printf(1, "CBT for process /%d/ is :%d\n", pid, getCBT(pid));
        printf(1, "\n\n");
    }

    while (wait() != -1)
    {
        ;
    }

    exit();
}
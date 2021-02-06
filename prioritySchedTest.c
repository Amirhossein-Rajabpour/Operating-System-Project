#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int result = changePolicy(1);
    printf(1, "%d", result);

    int original_pid = getpid();
    int child_num = -1;
    int priority = -1;

    for (int i = 0; i < 30; i++)
    {
        if (fork() == 0) // Child
        {
            child_num = i + 1;
            // priority = 6 - (i / 5);
            priority = (i / 5) + 1;
            printf(1, "i: %d, priority: %d\n", i, priority);
            setPriority(priority);
        }
        else // Parent
        {
            break;
        }
    }

    if (getpid() != original_pid)
    {
        for (int i = 1; i <= 250; i++)
            printf(1, "/%d/: /%d/\n", child_num, i);

        int pid = getpid();
        int turnAroundTime = getTurnAroundTime(pid);
        int waitingTime = getWaitingTime(pid);
        int CBT = getCBT(pid);

        while (wait() != -1)
            ;

        printf(1, "PID: %d, Child Number: %d, -> Turnaround time: %d\n", pid, child_num, turnAroundTime);
        printf(1, "PID: %d, Child Number: %d, -> Waiting time: %d\n", pid, child_num, waitingTime);
        printf(1, "PID: %d, Child Number: %d, -> CBT: %d\n", pid, child_num, CBT);
        printf(1, "\n\n");
    }

    while (wait() != -1)
        ;

    exit();
}
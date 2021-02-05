#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int main_pid = getpid();
    for (int i = 0 ; i < 10 ; i++)
    {
        if ( fork() == 0 )
            break;
    }

    if (main_pid != getpid())
    {
        for (int i = 0 ; i < 1000 ; i++)
            printf(1, "/%d/: %d\n", getpid(), i);  
        
        int turnAroundTime = getTurnAroundTime(getpid());
        int waitingTime    = getWaitingTime(getpid());
        int CBT            = getCBT(getpid());

        printf(1, "turnAroundTime for process /%d/ is :%d\n", getpid(), turnAroundTime);  
        printf(1, "waitingTime for process /%d/ is :%d\n", getpid(), waitingTime);  
        printf(1, "CBT for process /%d/ is :%d\n", getpid(), CBT);  
    }

    while (wait() != -1){;}

    exit();
}
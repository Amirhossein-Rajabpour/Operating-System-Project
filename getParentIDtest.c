#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    for (int i = 0; i < 1; i++)
    {
        int pid = fork();
        if (pid > 0){ // parent
            sleep(100);
            printf(1, "This is process (getpid) %d and the parent id is %d\n", getpid(), getParentID());
            wait();
        }
        else // child
            printf(1, "This is process (getpid) %d and the parent id is %d\n", getpid(), getParentID());
    }
    exit();
}
#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    for (int i = 0; i < 1; i++)
    {
        int pid = fork();
        if (pid > 0){ // parent
            wait();
            printf(1, "This is process (getpid) %d and the parent id is %d\n", getpid(), getParentID());
        }
        else // child
            printf(1, "This is process (getpid) %d and the parent id is %d\n", getpid(), getParentID());
    }
    exit();
}
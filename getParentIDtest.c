#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    for (int i = 0; i < 1; i++)
    {
        fork();
        printf(1, "This is process (getpid) %d and the parent id is %d\n", getpid(), getParentID());
        // printf(1, "This is process (fork return) %d and the parent id is %d\n\n", pid, getParentID());
    }
    exit();
}
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int main_pid = getpid();
    for (int i = 0 ; i < 4 ; i++)
        fork();

    if (main_pid != getpid())
    {
        for (int i = 0 ; i < 1000 ; i++)
            printf(1, "/%d/: %d\n", getpid(), i);  
    }

    while (wait() != -1){;}

    exit();
}
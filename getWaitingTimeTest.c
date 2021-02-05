#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    printf(1, "This is getWaitingTimeTest template!");

    while (wait() != -1)
        ;

    exit();
}
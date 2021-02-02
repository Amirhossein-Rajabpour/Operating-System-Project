#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    printf(1, "Parent Process ID is %d\n", getParentID());
    exit();
}
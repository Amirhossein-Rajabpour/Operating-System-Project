#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int syscall_num = atoi(argv[1]);
    printf(1, "Syscall #%d has been called %d times\n", syscall_num, getSyscallCounter(syscall_num));
    exit();
}
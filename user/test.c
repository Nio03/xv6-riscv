#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{

    int ppid = getppid();
    printf("Parent PID: %d\n", ppid);
    exit(0);
}

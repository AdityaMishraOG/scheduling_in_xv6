#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[])
{
    int pid = atoi(argv[1]);
    int new_priority = atoi(argv[2]);

    set_priority(pid, new_priority);
    // int old_priority = set_priority(pid, new_priority);


    exit(0);
}
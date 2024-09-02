
#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
uint64
sys_getppid(void)
{
    struct proc *p = myproc();

    return p->parent->pid;
}
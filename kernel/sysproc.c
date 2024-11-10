#include "syscall.h"
#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64 sys_mprotect(void)
{
  uint64 addr;
  int len;

  // Obtener los argumentos de la llamada al sistema (sin retorno)
  argaddr(0, &addr);
  argint(1, &len);

  // Verificar si los valores de `addr` y `len` son válidos
  if (addr % PGSIZE != 0 || len <= 0)
  {
    return -1;
  }

  // Lógica de protección de memoria
  for (int i = 0; i < len; i++)
  {
    pte_t *pte = walk(myproc()->pagetable, addr + i * PGSIZE, 0);
    if (!pte || (*pte & PTE_V) == 0)
    {
      return -1;
    }

    // Marcar la página como solo lectura
    *pte &= ~PTE_W;
  }
  return 0;
}

uint64 sys_munprotect(void)
{
  uint64 addr;
  int len;

  // Obtener los argumentos de la llamada al sistema (sin retorno)
  argaddr(0, &addr);
  argint(1, &len);

  // Verificar si los valores de `addr` y `len` son válidos
  if (addr % PGSIZE != 0 || len <= 0)
  {
    return -1;
  }

  // Lógica de desprotección de memoria
  for (int i = 0; i < len; i++)
  {
    pte_t *pte = walk(myproc()->pagetable, addr + i * PGSIZE, 0);
    if (!pte || (*pte & PTE_V) == 0)
    {
      return -1;
    }

    // Restaurar el permiso de escritura
    *pte |= PTE_W;
  }
  return 0;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if (n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (killed(myproc()))
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

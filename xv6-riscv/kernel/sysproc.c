#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "pstat.h"
#include "random.h"

// added for project 3
int getpinfo(struct pstat*);

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
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
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
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


// declare proc array as an extern for it to be used in sys_getfilenum
extern struct proc proc[NPROC];

// added for sys_getfilennum
uint64
sys_getfilenum(void)
{

  // pid holds process id
  int pid;
  
  // openfilecount used to count the open files
  int openfilecount = 0;

  // get pid
  argint(0, &pid);

 // Iterate over the proc array to find the process with the given pid
  for (struct proc *p = proc; p < &proc[NPROC]; p++) {
    // Acquire the lock for the individual process to safely access its data
    acquire(&p->lock);

    // Check if this process has the matching pid
    if (p->pid == pid) {
      // Count the number of open files by checking the p->ofile array
      for (int i = 0; i < NOFILE; i++) {
        if (p->ofile[i] != 0) {
          openfilecount++;
        }
      }
      // Release the lock for the found process
      release(&p->lock);
      return openfilecount;
    }

    // Release the lock if this is not the process we are looking for
    release(&p->lock);
  }

  // Process not found, return -1
  return -1;
}
// added for project 3
uint64
sys_settickets(void){
  int n;
  argint(0, &n);

  myproc()->tickets=n;
  return 0;
}

uint64
sys_getpinfo(void)
{
  struct pstat *p;
  argaddr(0, (uint64*)&p);
  return (getpinfo(p));
}
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_getParentID(void)
{
  return getParentID();
}

int sys_getChildren(void)
{
  int *children_pid;
  if (argptr(0, (void *)&children_pid, sizeof(*children_pid)) < 0)
  {
    return -1;
  }
  else
  {
    return getChildren(children_pid);
  }
}

int sys_getSyscallCounter(void)
{
  int syscall_num;
  if (argint(0, &syscall_num) < 0)
  {
    return -1;
  }
  else
  {
    return getSyscallCounter(syscall_num);
  }
}

int sys_setPriority(void)
{
  int newPriority;
  if (argint(0, &newPriority) < 0)
    return -1;
  else
    return setPriority(newPriority);
}

int sys_changePolicy(void)
{
  int newPolicy;
  if (argint(0, &newPolicy) < 0)
    return -1;
  else
    return changePolicy(newPolicy);
}

int sys_getTurnAroundTime(void)
{
  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  else
    return getTurnAroundTime(pid);
}

int sys_getWaitingTime(void)
{
  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  else
    return getWaitingTime(pid);
}

int sys_getCBT(void)
{
  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  else
    return getCBT(pid);
}

int sys_customWait(void)
{
  int *procTimes;
  if (argptr(0, (void *)&procTimes, sizeof(*procTimes)) < 0)
  {
    return -1;
  }
  else
  {
    return customWait(procTimes);
  }
}

int sys_setQueue(void)
{
  int queueNumber;
  if (argint(0, &queueNumber) < 0)
  {    
    return -1;
  }
  else
    return setQueue(queueNumber);

}
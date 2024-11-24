**Project 3 ReadMe**

Files modified:

**Syscall.c:**

- Created syscall for settickets() and getpinfo()

**Syscall.h:**

- Created syscalls numbers for settickets() and getpinfo()

**Sysproc.s:**

- Implemented settickets() and getpinfo()

**Proc.c:**

- Initialized tickets and ticks in alloporc()  
- Set child tickets to inherit from parents in fork()  
- Implemented a lottery system to collect total number of tickets and use scaled\_random in scheduler()

**Proc.h:**

- Created struct for tickets and ticks

**User.h:**

- Added getpinfo() and settickets() to syscalls

**Usys.pl:**

- Added getpinfo() and settickets()

**Makefile:**

- Added hardwork and getpinfo for the user  
- Added random for the kernel

Files added:

**Getpinfo.c:**

- Added to xv6 in the user so that tickets and ticks can be displayed

**Hardwork.c:**

- Added to xv6 in the user for testing that the lottery works

**Pstat.h:**

- Added to xv6 in the kernel so that results can be passed to the user

**Random.c:**

- Added to xv6 in the kernel for random number generation

**Random.h:**

- Added to xv6 in the kernel to use scaled\_random()

Also see:

**OSProj3Graph.xlsx:**

- Excel file containing graphed results

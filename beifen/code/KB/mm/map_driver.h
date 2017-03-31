#include<asm/atomic.h>
#include<as/semaphore.h>
#include<linux/cdev.h>

struct mapdrvo{

struct cdev mapdevo;
atomic_t usage;
};



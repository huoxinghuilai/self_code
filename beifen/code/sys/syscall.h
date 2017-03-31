#ifndef syscall.h
#define syscall.h

#define _syscall(type,name)\
type name(void){\
\
__asm__ volatile ("int &0x60"\
: "=a" (__res)\
: "0" (__NR_##name))\
if(__res>=0)
return (type)__res;\
errno=-__res;\
return -1;
}


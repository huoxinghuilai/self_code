#include<stdio.h>

int man(int ac,char *av[]){
setup();
if(get_ticket()!=0)
exit(0);
do_regular_work();
release_ticket();
shut_down();
}

do_regular_work(){
printf("supersleep version 1.0 running-licensed software\n");
sleep(10);
}


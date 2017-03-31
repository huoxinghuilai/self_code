static inline _syscall(int,cpfork);

int main(void){

int i;

i=cpfork();
if(i==-1)
printf("error\n");
else if(i==0)
printf("this is child\n");
else
printf("this is father\n");

return 0;
}


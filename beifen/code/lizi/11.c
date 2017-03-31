int i,fd;
char *buf;
fd=open("test_data",O_RDONLY);
buf=mmap(0,12,PROT_READ,MAP_PRAVITE,fd,0);
for(i=0;i<12;i++)
printf("%c\n",buf[i]);


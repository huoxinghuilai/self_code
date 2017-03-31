#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

const char *test_file="/tmp/test_lock";

int main(){

int file_desc;
int byte_count;
char *byte_to_write="A";
struct flock region_1;
struct flock region_2;
int res;

file_desc=open(test_file,O_RDWR|O_CREAT,0666);
if(!file_desc){
fprintf(stderr."unable to open %s for read/write\n",test_file);
exit(EXIT_FAILUER);
}

for(byte_count=0;byte_count<100;byte_count++){
(void)write(file_desc,byte_to_write,1);
}



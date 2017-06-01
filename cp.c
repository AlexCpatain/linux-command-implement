#include <stdio.h>
#include <fcntl.h> //open()
#include <unistd.h>//close()  read()
#include <stdlib.h>

void error(const char *info, const char *file){
    printf("%s\n", info);
    perror(file);
    exit(-1);
}
int main(int argc, char *argv[])
{
    if(argc != 3)
	return ;
    int fd_d, fd_s;
    int read_size = 4096;
    char buf[read_size];
    int has_read;
    if((fd_s = open(argv[1], O_RDONLY)) == -1){
	error("can not open", argv[1]);
    }
    if((fd_d = creat(argv[2],  DEF_MODE)) == -1){
	error("can not create", argv[2]);
    }
    while((has_read = read(fd_s, buf, read_size)) > 0){
	if(write(fd_d, buf, has_read) != has_read){
	    error("can not write", argv[2]);
	}
    }
    if(has_read == -1){
	error("can not read", argv[1]);
    }
    if(close(fd_s) == -1 || close(fd_d) == -1){
	error("can not close", "");
    }
    return 0;
}


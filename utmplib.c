#include <stdio.h>
#include <utmp.h>
#include <fcntl.h> //open()
#include <unistd.h>//close()  read()
#include <stdlib.h>
#include "utmplib.h"

#define BUFSIZE 16
#define UTSIZE (sizeof(struct utmp))


static struct utmp buf[BUFSIZE * UTSIZE];
static int num = 0;//numbers of utmp in buf
static int next = 0;//point to next utmp in buf
static fd_utmp = -1;

static error(const char *info, const char *file)
{
    printf("%s\n", info);
    perror(file);
    exit(-1);
}

int utmp_open(const char *filename){
    fd_utmp = open(filename, O_RDONLY);
    if(fd_utmp == -1)
	    error("can not open", filename);
    num = next = 0;
    return fd_utmp;
}
struct utmp *utmp_next()
{
	if(fd_utmp == -1)
		return NULL;
	if(num == 0 && utmp_reload() == 0)
		return NULL;
	--num;
	next = (next + 1) % BUFSIZE;
	return &buf[next-1];
}
int utmp_reload()
{
	int len = read(fd_utmp, buf, UTSIZE*BUFSIZE);
	if(len == -1)
		error("can not read", "");
	num = len / UTSIZE;
	return num;
}
int utmp_close(int fd)
{
	if(fd != -1)
		return close(fd);
	return -1;
}

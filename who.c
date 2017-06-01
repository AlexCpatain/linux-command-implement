#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <stdio.h>
#include <time.h>
#include "utmplib.h"

char *utmp_file = "/var/run/utmp";

void show_info(struct utmp *info)
{
	if(info->ut_type != USER_PROCESS)
		return ;
        time_t time = (time_t)info->ut_tv.tv_sec;
	printf("%-8s %-8d %-8s %12.12s\n", info->ut_user, info->ut_pid, info->ut_line, ctime(&time)+4);
	
}
int main(int argc, int *argv[])
{

	struct utmp *utmp_recoured;
	int fd;
	int length = sizeof(struct utmp), l;
	fd = utmp_open(utmp_file);
	while((utmp_recoured = utmp_next()) != NULL){

		show_info(utmp_recoured);


	}
	utmp_close(fd);
	
	
	
        return 0;
}



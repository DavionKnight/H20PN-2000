#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <string.h>
#include <pthread.h>

#define WAIT_FOR_EXTERN_INTERRUPT	0x1

int fun_pthread(void *arg)
{
	int count = 0;
	int bcmfd;
	
	while(1)
	{
		bcmfd = open( "/dev/exirq", O_RDWR);
		if(bcmfd<0)
		{
			sleep(1);
			printf("bcmfd = %d\n",bcmfd);
			continue;
		}
		ioctl(bcmfd, WAIT_FOR_EXTERN_INTERRUPT, 0); 
		printf("get an interrupt, count=%d\n",++count);
		close(bcmfd);
		
	}
}

int main(int argc, char *argv[])
{
	int pid;
	char arg1 = 1, arg2 = 2;
	pthread_t id_1,id_2;


	pthread_create(&id_1, NULL, (void *)fun_pthread, &arg1);

	pthread_join(id_1,NULL);
	return 0;
}



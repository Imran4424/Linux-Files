#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>


const BUFF_SIZE = 1024;


int main(int num,char *argv[])

{

	int fd;

	char *msgBuff = "Hello World";

	char *pipeName = "Pipe1";



	umask(0);



	mknod(pipeName, S_IFIFO | 0666, 0);



	fd = open(pipeName, O_WRONLY);

	write(fd, msgBuff, strlen(msgBuff)+1);

	close(fd);

	int fd2;

	fd2 = open(argv[1], O_RDONLY);


	printf("I am writer\n");

	return 0;

}

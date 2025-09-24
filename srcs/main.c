#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv, char **envp)
{

		(void) argc;
		(void) argv;
		(void) envp;
		int fd = open("srcs/tmp/a.out", O_RDONLY);
		fexecve(fd, argv + 1, );
		perror("AAAAAAAAAA");
	return(0);
}

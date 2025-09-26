#include "woody_woodpacker.h"


int main(int argc, char **argv, char **envp)
{
	t_settings set;
	int fd;

	set = parse_options(argc, argv);
	//printf("key : %s\nout: %s\n", set.key, set.output);
	fd = open("hein", O_WRONLY | O_CREAT, 0755);
	printf("le voilà le jus d'orange: %d\n", fd);
	(void)set;
	(void)envp;	
}

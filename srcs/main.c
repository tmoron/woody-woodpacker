#include "woody_woodpacker.h"


int main(int argc, char **argv, char **envp)
{
	Elf64_Ehdr herderœ;
	t_settings set;
	int fd;

	set = parse_options(argc, argv);
	//printf("key : %s\nout: %s\n", set.key, set.output);
	herderœ = fill_64header(0x1234);
	fd = open("hein", O_WRONLY | O_CREAT, 0755);
	printf("le voilà le jus d'orange: %d\n", fd);
	write(fd, &herderœ, sizeof(herderœ));
	(void)set;
	(void)envp;	
}

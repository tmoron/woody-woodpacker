#include "woody_woodpacker.h"

#include "stub_code.h" // only present during compilation

int main(int argc, char **argv, char **envp)
{
	t_settings set;
	int fd;

	set = parse_options(argc, argv);
	//printf("key : %s\nout: %s\n", set.key, set.output);
	fd = open("hein", O_WRONLY | O_CREAT, 0755);
	write(fd, &stub_code, stub_code_len);
	write(fd, "patate douce", 12);
	write(fd, &(uint64_t){12}, sizeof(uint64_t));
	(void)set;
	(void)envp;	
}

#include "woody_woodpacker.h"


int main(int argc, char **argv, char **envp)
{
	t_settings set;

	set = parse_options(argc, argv);
	//printf("key : %s\nout: %s\n", set.key, set.output);
	(void)set;
	(void)envp;

	
}

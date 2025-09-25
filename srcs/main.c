#include "woody_woodpacker.h"

t_settings parse_options(int argc, char **argv)
{
    (void)argc;
    (void)argv;
	t_settings res;
	ft_bzero(&res, sizeof(t_settings));
	return(res);
}

int main(int argc, char **argv, char **envp)
{
	t_settings set;

	set = parse_options(argc, argv);
	(void)set;
	(void)envp;
}

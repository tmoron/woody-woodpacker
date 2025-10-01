#include "woody_woodpacker.h"
#include "parsing.h"

void show_help(void)
{
	printf("glhf, 󱓞 hope you figure it out ! 󰱱  \n");
}

void get_string(char *arg, char **res)
{
	if(!*arg)
		return ;
	*res = ft_strdup(arg);
	if(!*res)
		fprintf(stderr, "failed allocation, fallback to default\n");
}

char *gen_key(void)
{
	return(ft_strdup(""));
}

void set_defaults(t_settings *set)
{
	set->output = ft_strdup("woody");
	set->key = gen_key();
}

void free_settings(t_settings *set)
{
	free(set->output);
	free(set->key);
}

int parse_options(int argc, char **argv, t_settings *set)
{
	int arg;
	struct option opts[] = 
	{
		{"key", required_argument, 0, 'k'},
		{"output", required_argument, 0, 'o'},
		{"help", no_argument, 0, 'h'}
	};

	ft_bzero(set, sizeof(t_settings));
	set_defaults(set);
	while((arg = getopt_long(argc, argv, "k:o:h", opts, NULL)) != -1)
	{
		switch(arg) {
			case 'k':
				get_string(optarg, &set->key);
				break;
			case 'o':
				get_string(optarg, &set->output);
				break;
			case 'h':
			default:
				show_help();
				return (0);
		}
	}
	if (optind != argc - 1)
	{
		fprintf(stderr, "error: exactly one program name is required\n");
		show_help();
		return (0);
	}
	set->program = argv[optind];
	return(1);
}

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
	return(ft_strdup("")); //TODO actual random key generation
}

void set_defaults(t_settings *set)
{
	set->output_name = ft_strdup("hein");
	set->key = gen_key();

	set->out_fd = -1;
	set->in_fd = -1;
}

void free_settings(t_settings *set)
{
	free(set->output_name);
	free(set->key);
	if(set->out_fd != -1)
		close(set->out_fd);
	if(set->in_fd != -1)
		close(set->in_fd);
}

int check_options(t_settings *set)
{
	if(set->in_fd == -1)
	{
		fprintf(stderr, "error : failed to open input file\n");
		return(0);
	}
	if(set->out_fd == -1)
	{
		fprintf(stderr, "error : failed to open input file\n");
		return(0);
	}
	return(1);
}

int get_options(int argc, char **argv, t_settings *set)
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
				get_string(optarg, &set->output_name);
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
	if(!set->output_name)
		return(0);
	if(!*set->output_name)
		return(0);
	set->in_fd = open(argv[optind], O_RDONLY);
	if(set->in_fd != -1)
		set->out_fd = open(set->output_name, O_CREAT | O_WRONLY, 0755);
	return(check_options(set));
}

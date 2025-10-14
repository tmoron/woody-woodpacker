#ifndef PARSING_H
# define PARSING_H

#include <getopt.h>
#include "woody_woodpacker.h"

int get_options(int argc, char **argv, t_settings *set);
int check_options(t_settings *set);
void free_settings(t_settings *set);

#endif //PARSING_H

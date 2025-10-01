#ifndef PARSING_H
# define PARSING_H

#include <getopt.h>
#include "woody_woodpacker.h"

int parse_options(int argc, char **argv, t_settings *set);
void free_settings(t_settings *set);

#endif //PARSING_H

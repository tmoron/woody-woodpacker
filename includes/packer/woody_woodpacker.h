#ifndef WOODY_H
# define WOODY_H

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include "libft.h"
#include "elf.h"

typedef struct s_settings
{
	char *key;
	char *output;
} t_settings;

#include "parsing.h"

#endif //WOODY_H

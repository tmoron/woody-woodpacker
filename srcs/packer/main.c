#include "woody_woodpacker.h"
#include "󱓞.h"

char *add_char_to_data(char c, char **data, int *data_size)
{
	char *new_data;
	int i = 0;

	new_data = malloc(*data_size + 1);
	if (!new_data)
	{
		perror("malloc");
		return NULL; }
	while (i < *data_size)
	{
		new_data[i] = (*data)[i];
		i++;
	}
	new_data[i] = c;
	free(*data);
	*data = new_data;
	(*data_size)++;
	return *data;
}

char *add_str_to_data(char **data, int *data_size, char *str_data, int str_data_size)
{
	int i = 0;

	while (i < str_data_size)
	{
		*data = add_char_to_data((str_data)[i], data, data_size);
		i++;
	}
	return *data;
}

int find_longest_match(char c, char **all_data, int all_data_size, int fd, int *match_index, char **match_str, int *match_len)
{
	int best_index = -1;
	int best_len = 0;
	char temp_buf[1000];
	int temp_len = 0;

	temp_buf[0] = c;
	temp_len = 1;

	off_t current_pos = lseek(fd, 0, SEEK_CUR);

	int read_ahead = read(fd, &temp_buf[1], 999);
	if (read_ahead > 0)
		temp_len += read_ahead;

	lseek(fd, current_pos, SEEK_SET);

	for (int i = 0; i <= all_data_size - 1; i++)
	{
		if ((*all_data)[i] == c)
		{
			int len = 0;
			while (len < temp_len && (i + len) < all_data_size &&
				   (*all_data)[i + len] == temp_buf[len])
			{
				len++;
			}

			if (len > best_len)
			{
				best_len = len;
				best_index = i;
			}
		}
	}

	if (best_len >= 3)
	{
		*match_index = best_index;
		*match_len = best_len;
		*match_str = malloc(best_len);
		if (*match_str)
		{
			for (int i = 0; i < best_len; i++)
				(*match_str)[i] = temp_buf[i];
		}
		return 1;
	}

	return 0;
}

int init_data(char **data, int *data_size)
{
	*data = malloc(1);
	if (!*data)
	{
		perror("malloc");
		return 0;
	}
	*data_size = 0;
	return 1;
}

void read_file(int fd)
{
	char buf[1];
	char *all_data;
	int all_data_size;
	int ret;
	
	// TOTDO à enlever juste du print
	off_t file_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	off_t bytes_read = 0;
	int last_percentage = -1;
	//

	if (!init_data(&all_data, &all_data_size))
		return;

	// enlevé print
	printf("Traitement du fichier (%ld bytes)...\n", file_size);

	while ((ret = read(fd, buf, 1)) > 0)
	{
		char *match_str = NULL;
		int match_index = -1;
		int match_len = 0;
		
		bytes_read++;
		
		// cal pourcentage à enlever
		int percentage = (int)((bytes_read * 100) / file_size);
		if (percentage != last_percentage && percentage % 5 == 0)
		{
			printf("\rProgrès: %d%% (%ld/%ld bytes)", percentage, bytes_read, file_size);
			fflush(stdout);
			last_percentage = percentage;
		}
		//

		if (find_longest_match(buf[0], &all_data, all_data_size, fd, &match_index, &match_str, &match_len))
		{
			// printf("Match trouvé: longueur %d à l'index %d\n", match_len, match_index);
			/* j'ai ajouté des {} pour signaler le début et la fin de la séquence et < pour l'index du pattern initial
			   mais tu peux juste les réécrire comme tu veux après
			   il faudra juste implémenter la détection continue si tu veux la faire aussi
			*/
			all_data = add_char_to_data('{', &all_data, &all_data_size);
			all_data = add_str_to_data(&all_data, &all_data_size, match_str, match_len);
			all_data = add_char_to_data('}', &all_data, &all_data_size);
			all_data = add_char_to_data('<', &all_data, &all_data_size);
			char *index_str = ft_itoa(match_index);
			all_data = add_str_to_data(&all_data, &all_data_size, index_str, ft_strlen(index_str));
			free(index_str);

			// a enleve en même temps que les pourcentages
			bytes_read += match_len - 1;

			lseek(fd, match_len - 1, SEEK_CUR);
			free(match_str);
		}
		else
			all_data = add_char_to_data(buf[0], &all_data, &all_data_size);
	}

	// enlever print
	printf("\rProgrès: 100%% (%ld/%ld bytes) - Terminé!\n", file_size, file_size);

	printf("Résultat final:\n");
	for (int i = 0; i < all_data_size; i++)
		write(1, &all_data[i], 1);
	printf("\n");

	free(all_data);
	if (ret < 0)
		perror("read");
	close(fd);
}

int main(int argc, char **argv, char **envp)
{
	t_settings set;
	// uint8_t *data;
	int fd;

	if (!parse_options(argc, argv, &set))
	{
		free_settings(&set);
		return (1);
	}

	fd = open(set.program, O_RDONLY);
	read_file(fd);

	// printf("key : %s\nout: %s\n", set.key, set.output);
	fd = open("hein", O_WRONLY | O_CREAT, 0755);
	write(fd, &_objs_stub_stub, _objs_stub_stub_len);
	write(fd, "patate douce", 12);
	write(fd, &(uint64_t){12}, sizeof(uint64_t));
	free_settings(&set);
	(void)envp;
	return (0);
}

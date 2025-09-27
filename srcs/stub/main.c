#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	uint64_t	payload_len;
	char		*buffer;

	if(!argc)
		return (1);
	int fd = open(argv[0], O_RDONLY);
	if(lseek(fd, -8, SEEK_END) == -1)
	{
		write(2, "error, invalid file\n", 20);
		return(1);
	}
	read(fd, &payload_len, sizeof(payload_len));
	buffer = malloc(payload_len + 1);
	printf("length : %lu\n", payload_len);
	if(lseek(fd, -(8 + payload_len), SEEK_END) == -1)
	{
		write(2, "error, invalid file\n", 20);
		return(1);
	}
	if(read(fd, buffer, payload_len) != (ssize_t)payload_len)
	{
		write(2, "error, invalid file\n", 20);
		return(1);
	}
	buffer[payload_len] = 0;
	printf("str : %s\n", buffer);
	free(buffer);
	return(0);
}

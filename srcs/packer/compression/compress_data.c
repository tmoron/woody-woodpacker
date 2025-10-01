#include "woody_woodpacker.h"

uint8_t *compress_data(uint8_t *data)
{
	uint8_t *buffer;

	(void)data;
	buffer = malloc(COMPRESSION_BLOC_SIZE);
	if(!buffer)
		return(0);
	return(buffer);
}

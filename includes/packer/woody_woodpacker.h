#ifndef WOODY_H
# define WOODY_H

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include "libft.h"
#include "elf.h"
#include "settings.h"

/**
 * @brief global settings for the program
 */
typedef struct s_settings
{
	char *key; /**< the encryption key for the executable */
	char *output_name; /**< the file name of the output */

	int in_fd; /**< the input file descriptor */
	int out_fd; /**< the output file descriptor */
} t_settings;


/**
 *  @brief context for the compression, everything the compression algorithm needs to run
 */
typedef struct s_compr_ctx
{
	uint8_t		buffer[COMPRESSION_BLOC_SIZE]; /**< data accumulated until there is enough to create a bloc */
	uint64_t	b_cur; /**< current length of the buffer */
	uint8_t		s_win[SLIDING_WINDOW_SIZE]; /**< sliding window of the *SLIDING_WINDOW_SIZE* bytes last read */
	uint64_t	s_win_cur; /**< current position in the sliding window */

	int			out_fd; /**< fd where the output stream is written */
} t_compr_ctx;


/**
 * brief creates a compression context and initialize its values
 *
 * @param[in]	fd	the fd where the compression should write
 * @return	the compression context on succes, 0 on failure
 */
t_compr_ctx	*compression_init(int fd);

/**
 * ends a stream compression, writes any remaining bytes to the file descriptor and frees the context
 *
 * @param ctx the compression context
 */
void		compression_end(t_compr_ctx *ctx);

/**
 * compresses a data stream
 * 
 * @param[in]	ctx 	the compression context
 * @param[in]	data	the data that needs to be compressed
 * @param[in]	len		the number of bytes in data
 * @return		0 on success, 1 on failure
 */
int			compress_data(t_compr_ctx *ctx, uint8_t *data, uint64_t len);



#include "parsing.h"

#endif //WOODY_H

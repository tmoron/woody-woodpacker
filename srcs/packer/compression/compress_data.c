#include "woody_woodpacker.h"

t_compr_ctx	*compression_init(int fd)
{
	t_compr_ctx	*res;

	res = malloc(sizeof(t_compr_ctx));
	if(!res)
		return (0);

	ft_bzero(res, sizeof(t_compr_ctx));
	res->out_fd = fd;
	return (res);
}

void	compression_end(t_compr_ctx *ctx)
{
	free(ctx);
}

int	compress_data(t_compr_ctx *ctx, uint8_t *data, uint64_t len)
{
	if(!ctx)
		return(1)
}

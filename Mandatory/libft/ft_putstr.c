#include <unistd.h>
#include "cub3D.h"

void	fd_putstr(const char	*str, int fd)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	write(fd, str, i);
}

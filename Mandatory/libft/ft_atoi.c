#include "../include/cub3D.h"

int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	if (str[0] == 0 || str[0] == '\n')
		exit_strerror("invalid color informaton\n", 1);
	while (*str != 0 && *str != '\n')
	{
		if (*str < '0' || *str > '9')
			exit_strerror("invalid color informaton\n", 1);
		result = result * 10 + (*str - 48);
		if (result > 255)
			exit_strerror("invalid color informaton\n", 1);
		str++;
	}
	return (result);
}

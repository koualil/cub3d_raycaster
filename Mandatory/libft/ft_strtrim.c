#include "../include/cub3D.h"

char	*ft_strtrim(char *str, char c)
{
	int		size;
	int		i;
	char	*trim;

	size = 0;
	i = 0;
	while (str[size] != 0 && str[size] != c)
		size++;
	trim = malloc((sizeof(char)) * (size + 1));
	malloc_null_check(trim);
	while (i < size)
	{
		trim[i] = str[i];
		i++;
	}
	trim[i] = 0;
	return (trim);
}

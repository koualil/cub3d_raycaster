#include "cub3D.h"

void	windows_resize(int width, int height, void *param)
{
	t_data	*data;

	data = param;
	if (!mlx_resize_image(data->image, width, height))
		return (error_exit(data));
	data->height = height;
	data->width = width;
	game(data);
}

int	main(int ac, char **argv)
{
	t_data	data;

	if (ac != 2)
	{
		printf("Invalid number of argument\n");
		printf("usage: cub3d map.cub\n");
		return (1);
	}
	data = init_data(argv[1]);
	game(&data);
	clean_exit(&data);
	return (EXIT_SUCCESS);
}

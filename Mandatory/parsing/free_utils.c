#include "../include/cub3D.h"


void	destroy_texture(t_text *texture, int n)
{
	if (n >= 0)
		mlx_delete_texture(texture->north);
	if (n >= 1)
		mlx_delete_texture(texture->south);
	if (n >= 2)
		mlx_delete_texture(texture->east);
	if (n >= 3)
		mlx_delete_texture(texture->west);
}

void	destroy_img(t_img *img, mlx_t *mlx, int n, t_text *text)
{
	if (n >= 1)
		mlx_delete_image(mlx, img->north);
	if (n >= 2)
		mlx_delete_image(mlx, img->south);
	if (n >= 3)
		mlx_delete_image(mlx, img->east);
	if (n >= 4)
		mlx_delete_image(mlx, img->west);
	if (text != NULL)
		destroy_texture(text, 4);
}

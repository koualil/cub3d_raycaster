# include <MLX42.h>

#include <stdlib.h>
#include <stdio.h>

#define TILE_SIZE 250  // Size of the square
#define WIN_WIDTH 500 // Window width
#define WIN_HEIGHT 500 // Window height

typedef struct s_data {
    mlx_t *mlx;
    mlx_image_t *image;
    int width;
    int height;
} t_data;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}




void draw_square(void *w)
{
	t_data* data = w;
	

    // Draw a red square at the top-left corner
    for (int x = 0; x < TILE_SIZE; ++x)
	{
        for (int y = 0; y < TILE_SIZE; ++y)
		{

            mlx_put_pixel(data->image, x, y, 0xFFA500FF
); // Red color
		}

	}
	 mlx_image_to_window(data->mlx, data->image, 0, 0);

	//  mlx_image_to_window(data->mlx, data->image, 0, 0);
    // Put the image into the window
}

int main()
{
    t_data data;

    // Initialize mlx and create a window (with MLX42)
    data.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Squarde", true);
    if (!data.mlx) {
        printf("Error: mlx initialization failed.\n");
        return (EXIT_FAILURE);
    }

    // Set the window size
    data.width = WIN_WIDTH;
    data.height = WIN_HEIGHT;

    // Create a new image (to draw on)
    data.image = mlx_new_image(data.mlx, data.width, data.height);
    if (!data.image) {
        printf("Error: Failed to create image.\n");
        return (EXIT_FAILURE);
    }

    // Create a new window
   
   

    // Draw the red square in the image
   for (int x = 0; x < data.width; ++x)
	{
        for (int y = 0; y < data.height; ++y)
		{
            mlx_put_pixel(data.image, x, y, 0xADD8E6FF);

		}}
    // Enter the mlx loop to keep the window open
	 mlx_image_to_window(data.mlx, data.image, 0, 0);

	mlx_loop_hook(data.mlx, draw_square, &data);
    mlx_loop(data.mlx);
	mlx_terminate(data.mlx);

    return EXIT_SUCCESS;
}

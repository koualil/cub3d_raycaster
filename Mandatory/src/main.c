#include "../include/cub3D.h"

#include "../include/cub3D.h"

void my_mlx_pixel_put(t_data *mlx, int x, int y, int color) {
    if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
        return;
    mlx_put_pixel(mlx->image, x, y, color);
}

static void draw_wall(t_data *data, int ray, int wall_t, int wall_b) {
    while (wall_t < wall_b) {
        my_mlx_pixel_put(data, ray, wall_t++, 0x00FF00FF);
    }
}

void projected_wall(t_data *data, int ray) {
    double disproplan = (data->width / 2) / tan(FOV / 2);
    data->ray_distance *= cos(data->player.ray_angel - data->player_angle); // Fish-eye correction
    double wall_h = (TILE_SIZE / data->ray_distance) * disproplan;

    int wall_t = (data->height / 2) - (wall_h / 2);
    int wall_b = (data->height / 2) + (wall_h / 2);

    if (wall_b > data->height) 
		wall_b = data->height;
    if (wall_t < 0)
		wall_t = 0;

    draw_wall(data, ray, wall_t, wall_b);
}

double calcul_distance(t_vec2f start, t_vec2d end) {
    return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}

int is_wall(double x, double y, t_data *data) {
    t_vec2d m;

    if (x < 0 || y < 0)
        return 1;

    m.x = floor(x / TILE_SIZE);
    m.y = floor(y / TILE_SIZE);

    if (m.y < 0 || m.y >= data->param->map_data->sizes.y ||
        m.x < 0 || m.x >= data->param->map_data->sizes.x)
        return 1;

    return (data->param->map_data->map[m.y][m.x] == '1');
}

static double vertical_intersect(t_data *data) {
    t_vec2f inter, delta;
    inter.x = floor(data->param->map_data->pos.x / TILE_SIZE) * TILE_SIZE;
	// pixel = inter_check(angl, &h_y, &y_step, 1); check direction of player
    inter.y = data->player.p_y + (inter.x - data->param->map_data->pos.x) * tan(data->player.ray_angel);

    delta.x = TILE_SIZE;
    delta.y = TILE_SIZE * tan(data->player.ray_angel);

    while (!is_wall(inter.x - data->left, inter.y, data)) {
        inter.x += delta.x;
        inter.y += delta.y;
    }

    data->vwall = inter;
    return calcul_distance(inter, (t_vec2d){data->param->map_data->pos.x, data->param->map_data->pos.y});
}

static double horizontal_intersect(t_data *data) {
    t_vec2f inter, delta;

    inter.y = floor(data->player.p_y / TILE_SIZE) * TILE_SIZE;
	// pixel = inter_check(angl, &h_y, &y_step, 1);  check direction of player
    inter.x = data->player.p_x + (inter.y - data->player.p_y) / tan(data->player.ray_angel);

    delta.y = TILE_SIZE;
    delta.x = TILE_SIZE / tan(data->player.ray_angel);

    while (!is_wall(inter.x, inter.y - data->up, data)) {
        inter.x += delta.x;
        inter.y += delta.y;
    }
    data->hwall = inter;
    return calcul_distance(inter, (t_vec2d){data->player.p_x, data->player.p_y});
}

void cast_rays(t_data *data)
{

    t_vec2f distance;

    data->player.ray_angel = data->player_angle - (FOV / 2);
    for (int i = 0; i < data->width; i++) {
        distance.x = horizontal_intersect(data);
        distance.y = vertical_intersect(data);
		
        if (distance.y <= distance.x) {
            data->ray_distance = distance.y;
            data->was_hit_virtical = 1;
        } 
		else {
            data->ray_distance = distance.x;
            data->was_hit_virtical = 0;
        }

        projected_wall(data, i);
        data->player.ray_angel += (FOV / data->width);
    }
}
void draw_square(void* d)
{
    t_data *data = d;

    
    for(int j=0;j < data->param->map_data->sizes.y;j++)
    {
        for(int i=0;i < data->param->map_data->sizes.x;i++)
        {
            
            int offset_x = i * TILE_SIZE;
            int offset_y = j * TILE_SIZE;
           
            if(data->param->map_data->map[j][i] == '1')
			{
				for(int x=0;x < TILE_SIZE;x++)
					for(int y=0;y < TILE_SIZE;y++)
					mlx_put_pixel(data->image,  offset_x+x,  offset_y+y, 0xFFFFFFFF);

			}
			
            if(data->param->map_data->map[j][i] == '0')
            for(int x=0;x<TILE_SIZE;x++)
                for(int y=0;y<TILE_SIZE;y++)
                mlx_put_pixel(data->image,  offset_x+x, offset_y+y, 0xADD8E6FF);

			if(data->param->map_data->map[j][i] == 'N')
            for(int x=0;x<TILE_SIZE;x++)
                for(int y=0;y<TILE_SIZE;y++)
				{
                mlx_put_pixel(data->image,  offset_x+x, offset_y+y, 0xADD8E6FF);

				if (x <= TILE_SIZE/4 && y <= TILE_SIZE / 4)
                	mlx_put_pixel(data->image,  offset_x+x, offset_y+y, 0x006400FF);
				}
        }
    }
}

void	game_loop(void *ml)	
{
	t_data	*data;

	data = ml;	
	mlx_delete_image(data->mlx, data->image);	
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	// hook(mlx, 0, 0); 
	cast_rays(data);	
    // draw_square(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0); 
}


void start_game(t_data *data) {

    data->player.p_x = data->param->map_data->pos.x * TILE_SIZE + TILE_SIZE / 2;
    data->player.p_y = data->param->map_data->pos.y * TILE_SIZE + TILE_SIZE / 2;
    data->player.fov_rd = (FOV * M_PI) / 180;
    data->player.angle = data->player_angle;
    mlx_loop_hook(data->mlx, &game_loop, data);
    mlx_loop(data->mlx);
}

int main(int ac, char **argv) {
    if (ac != 2) {
        printf("Invalid number of arguments\n");
        printf("Usage: cub3d map.cub\n");
        return 1;
    }

    t_data data = init_data(argv[1]);
    // start_game(&data);
    mlx_loop_hook(data.mlx, &game_loop, &data);
    mlx_loop(data.mlx);
    return EXIT_SUCCESS;
}

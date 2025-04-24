#include "../../includes/cub.h"

void	my_pixel_put(t_win_img *img, int x, int y, int color)
{
	char	*offset;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	offset = img->pixel_ptr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)offset = color;
}

void	draw_square(t_game *g, int x, int y, int size, int color)
{
	int	i;
	int	j;

	j = -1;
	while (++j < size)
	{
		i = -1;
		while (++i < size)
			my_pixel_put(&g->win_img, x + i, y + j, color);
	}
}

void	draw_wall(t_map *map, t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->map_height - 1)
	{
		x = -1;
		while (++x < map->map_width - 1)
		{
			if (map->real_map[y][x][2])
				draw_square(g, x * g->tile_size, y * g->tile_size, g->tile_size, 0x0000FF);
		}
	}
}

void	draw_player(t_game *g)
{
	int		x;
	int		y;
	int		offset;
	int		player_size;

	player_size = g->tile_size / PLAYER_RATIO;
	offset = (g->tile_size - player_size) / 2;
	y = -1;
	while (++y < player_size)
	{
		x = -1;
		while (++x < player_size)
		{
			my_pixel_put(&g->win_img, g->player.x + x + offset, g->player.y + y + offset, 0xFF0000);
		}
	}
}

int	two_diagonal_wall(int mx, int my, t_game *g, float angle)
{
	int	***map;
	int	height;
	int	width;

	height = g->map_info.map_height - 1;
	width = g->map_info.map_width - 1;
	map = g->map_info.real_map;
	if (angle >= 0 && angle < PI / 2)
	{
		if (mx > 0 && my > 0 && map[my][mx - 1][2] && map[my - 1][mx][2])
			return (1);
	}
	else if (angle >= PI / 2 && angle < PI)
	{
		if (mx < width - 1 && my > 0 && map[my][mx + 1][2] && map[my - 1][mx][2])
			return (1);
	}
	else if (angle >= PI && angle < PI * 3 / 2)
	{
		if (mx < width - 1 && my < height - 1 && map[my + 1][mx][2] && map[my][mx + 1][2])
			return (1);
	}
	else if (angle >= PI * 3 / 2 && angle < 2 * PI)
	{
		if (mx > 0 && my < height - 1 && map[my][mx - 1][2] && map[my + 1][mx][2])
			return (1);
	}
	return (0);
}

// at up_left/up_right/down_right/down_left --> to check the position with its wall
int	angle_vs_2_walls(float x, float y, t_game *g, float angle)
{
	float	local_x;
	float	local_y;
	float	margin;

	local_x = fmodf(x, g->tile_size);
	local_y = fmodf(y,g->tile_size);
	margin = 0.1 * g->tile_size;
	if (local_x < margin && local_y < margin && angle >= 0 && angle < PI / 2)
		return (1);
	if (local_x > g->tile_size - margin && local_y < margin && angle >= PI / 2 && angle < PI)
		return (1);
	if (local_x > g->tile_size - margin && local_y > g->tile_size - margin && angle >= PI && angle < 3 * PI / 2)
		return (1);
	if (local_x < margin && local_y > g->tile_size - margin && angle >= 3 * PI / 2 && angle < 2 * PI)
		return (1);
	return (0);
}

int	is_wall(float x, float y, t_game *g, float angle)
{
	if (x < 0 || y < 0 || x > g->map_info.map_width - 1 || y > g->map_info.map_height - 1)
		return (1);
	if (g->map_info.real_map[(int)y][(int)x][2])
		return (1);
	if (angle_vs_2_walls(x, y, g, angle))
	{
		if (two_diagonal_wall(x, y, g, angle))
			return (1);
	}
	return (0);
}

void	set_move_dir_d(t_ray *ray, t_game *g, float x_dir, float y_dir)
{
	//depend on the angle, if angle > 90, mean the next move should toward the (0,0)-->position -1, other wise, the position +1
	//because the difference in the direction of move, the starting length --> the distance between the center of ray to its correspondence side of wall is different
	//----> if move left, distance = center of ray - left side of tile; other wise distance = right side of tile - center of ray
	if (x_dir < 0)
	{
		ray->x_move = -1;
		ray->d_x = (ray->ray_x - ray->map_x * g->tile_size) / g->tile_size * ray->chage_along_ray_convert_to_1_unitx;
	}
	else
	{
		ray->x_move = 1;
		ray->d_x = ((ray->map_x + 1) * g->tile_size - ray->ray_x) / g->tile_size * ray->chage_along_ray_convert_to_1_unitx;
	}
	if (y_dir < 0)
	{
		ray->y_move = -1;
		ray->d_y = (ray->ray_y - ray->map_y * g->tile_size) / g->tile_size * ray->chage_along_ray_convert_to_1_unity;
	}
	else
	{
		ray->y_move = 1;
		ray->d_y = ((ray->map_y + 1) * g->tile_size - ray->ray_y) / g->tile_size * ray->chage_along_ray_convert_to_1_unity;
	}
}

void	init_1_ray(t_ray *ray, t_game *g, float x_dir, float y_dir)
{
	// center of ray position in window
	ray->ray_x = g->player.x + g->tile_size / 2;
	ray->ray_y = g->player.y + g->tile_size / 2;
	// ray position if convert into parse-map
	ray->map_x = (int)(ray->ray_x / g->tile_size);
	ray->map_y = (int)(ray->ray_y / g->tile_size);
	// this means: in order to change 1 unit length ialong x or y axis, the length you need to change in the length of the ray itself
	// So if angle = 30 degree --> sin30 = 1/2, cos30 = root3/2 ---> it means to change in y axis, more change in the ray should have
	ray->chage_along_ray_convert_to_1_unitx = fabs(1.0 / x_dir) * g->tile_size;
	ray->chage_along_ray_convert_to_1_unity = fabs(1.0 / y_dir) * g->tile_size;
	set_move_dir_d(ray, g, x_dir, y_dir);
}

void	move_1_ray(t_ray *ray, t_game *g, float angle)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		// first we compare to touch the side of a tile, if touching along x-axis is short or along y-axis
		//--> the shorter the distance, the earlier of touch the side of a tile
		if (ray->d_x < ray->d_y)
		{
			ray->d_x += ray->chage_along_ray_convert_to_1_unitx;
			ray->map_x += ray->x_move;
			ray->side = 0;
		}
		else
		{
			ray->d_y += ray->chage_along_ray_convert_to_1_unity;
			ray->map_y += ray->y_move;
			ray->side = 1;
		}
		// then touched the tile, then check if the side of tile --> the tile itself is a "wall" (or: 1)
		if (is_wall(ray->map_x, ray->map_y, g, angle))
			ray->hit = 1;
	}
}

void	real_draw_1_ray(t_ray *ray, t_game *g, float x_dir, float y_dir)
{
	float	distance;
	float	center_x;
	float	center_y;
	int		i;

	//since when moving, the d_x or d_y is incremented -->but when touching the wall, the ray is actually at the wall's tile
	//so need to - 1 unit of the ray
	if (ray->side == 0)
		distance = (ray->d_x - ray->chage_along_ray_convert_to_1_unitx);
	else
		distance = (ray->d_y - ray->chage_along_ray_convert_to_1_unity);
	//center of ray to start
	center_x = g->player.x + g->tile_size / 2;
	center_y = g->player.y + g->tile_size / 2;
	i = -1;
	//draw the ray from the center along the direction using x_dir and y_dir ---> actually is the angle we calculated before
	//till the length of the ray it should be
	while (++i < (int)distance)
	{
		my_pixel_put(&g->win_img, center_x, center_y, 0x00FF00);
		center_x += x_dir;
		center_y += y_dir;
	}
}

void	draw_1_ray(t_game *g, float angle)
{
	t_ray	ray;
	float	x_dir;
	float	y_dir;

	x_dir = cosf(angle);
	y_dir = sinf(angle);
	init_1_ray(&ray, g, x_dir, y_dir);
	move_1_ray(&ray, g, angle);
	real_draw_1_ray(&ray, g, x_dir, y_dir);
}

void	draw_rays(t_game *g)
{
	float	start_angle;
	float	ray_angle;
	float	angle_degree;
	int		i;

	start_angle = g->player.angle - (FOV / 2);
	angle_degree = FOV / RAY_NB;
	i = -1;
	while (++i < RAY_NB)
	{
		ray_angle = start_angle + i * angle_degree;
		draw_1_ray(g, ray_angle);
	}

}

void	draw_map(t_game *g)
{
	int		x;
	int		y;
	t_map	*map;
	int		offset;
	int		player_size;

	ft_memset(g->win_img.pixel_ptr, 0, WIDTH * HEIGHT * (g->win_img.bpp / 8));
	map = &g->map_info;
	draw_wall(map, g);
	draw_player(g);
	draw_rays(g);
	mlx_put_image_to_window(g->mlx_connection, g->mlx_win, g->win_img.img_ptr, 0, 0);
}

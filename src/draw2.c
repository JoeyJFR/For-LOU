#include "../includes/cub.h"

bool	touch(float px, float py, t_game *game)
{
	int x = px / BLOCK_SIZE;
	int y = py / BLOCK_SIZE;
	if (game->test_map[y][x] == '1')
		return (true);
	return (false);
}
float	distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float	fix_distance(float x1, float y1, float x2, float y2, t_game *game)
{
	float	d_x = x2 - x1;
	float	d_y = y2 - y1;
	float	angle = atan2(d_y, d_x) - game->player.angle;
	float	fix_dis = distance(d_x, d_y)* cos(angle);
	return (fix_dis);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)

{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;
	float	delta_x = cos_angle * 0.1;
	float	delta_y = sin_angle * 0.1;
	while (!touch(ray_x, ray_y, game))
	{
		if (MINIMAP_MODE)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += delta_x;
		ray_y += delta_y;
	}
	if (!MINIMAP_MODE)
	{
		float	dist = fix_distance(player->x, player->y, ray_x, ray_y, game);
		float	height = (BLOCK_SIZE * HEIGHT) / (2 * dist);
		int	start_y = (HEIGHT - height) / 2;
		int	end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, 0x0000FF, game);
			start_y++;
		}
	}
}

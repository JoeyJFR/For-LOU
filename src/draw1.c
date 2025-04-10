#include "../includes/cub.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	offset;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	offset = y * game->win_img.line_length + x * game->win_img.bpp / 8;
	*((unsigned int *)(game->win_img.pixel_ptr + offset)) = color;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, color, game);
	i = -1;
	while (++i < size)
		put_pixel(x, y + i, color, game);
	i = -1;
	while (++i < size)
		put_pixel(x + size, y + i, color, game);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size, color, game);
}

void	clear_prev_player(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(x, y, 0, game);
	}
}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		y;
	int		x;

	map = game->test_map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, color, game);
			x++;
		}
		y++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player = &game->player;
	float		fraction;
	float		start_x;
	int			i;

	move_player(player);
	clear_prev_player(game);
	if (MINIMAP_MODE)
	{
		draw_square(player->x, player->y, 5, 0x00FF00, game);
		draw_map(game);
	}
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx_connection, game->mlx_win, game->win_img.img_ptr, 0, 0);
	return (0);
}
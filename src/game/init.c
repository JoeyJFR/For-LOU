#include "../../includes/cub.h"

static void	cal_tile_size(t_game *game)
{
	int	tile_size_x;
	int	tile_size_y;

	tile_size_x = WIDTH / (game->map_info.map_width - 1);
	tile_size_y = HEIGHT / (game->map_info.map_height - 1);
	if (tile_size_x < tile_size_y)
		game->tile_size = tile_size_x;
	else
		game->tile_size = tile_size_y;
}

void	init_game(t_game *game)
{
	game->mlx_connection = mlx_init();
	if (!game->mlx_connection)
		malloc_error(game);
	game->mlx_win = mlx_new_window(game->mlx_connection, WIDTH, HEIGHT, "cub3d");
	if (!game->mlx_win)
		d_free(game);
	game->win_img.img_ptr = mlx_new_image(game->mlx_connection, WIDTH, HEIGHT);
	if (!game->win_img.img_ptr)
		d_w_free(game);
	game->win_img.pixel_ptr = mlx_get_data_addr(game->win_img.img_ptr, &(game->win_img.bpp), &(game->win_img.line_length), &(game->win_img.endian));
	game->map_img.img_ptr = mlx_new_image(game->mlx_connection, WIDTH / 5, HEIGHT / 5);
	if (!game->map_img.img_ptr)
		d_w_i_free(game);
	game->map_img.pixel_ptr = mlx_get_data_addr(game->map_img.img_ptr, &(game->map_img.bpp), &(game->map_img.line_length), &(game->map_img.endian));
	mlx_put_image_to_window(game->mlx_connection, game->mlx_win, game->win_img.img_ptr, 0, 0);
	mlx_put_image_to_window(game->mlx_connection, game->mlx_win, game->map_img.img_ptr, 0, 0);
	cal_tile_size(game);
}

void	init_player(t_game *game)
{
	game->player.x = game->map_info.player_x * game->tile_size;
	game->player.y = game->map_info.player_y * game->tile_size;

	if (game->map_info.player_direction == 'S')
		game->player.angle = PI / 2;
	else if (game->map_info.player_direction == 'N')
		game->player.angle = PI * 3 / 2;
	else if (game->map_info.player_direction == 'E')
		game->player.angle = 0;
	else if (game->map_info.player_direction == 'W')
		game->player.angle = PI;

	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_left = false;
	game->player.key_right = false;

	game->player.left_rotate = false;
	game->player.right_rotate = false;
}

void	init_hook(t_game *game)
{
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, key_press_handle, game);
	mlx_hook(game->mlx_win, DestroyNotify, StructureNotifyMask, close_handle, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, key_release_handle, game);
}

#include "../includes/cub.h"

char	**get_map(void)
{
	char	**map = malloc(sizeof(char *) * 11);

	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000010001";
	map[3] = "100010000000001";
	map[4] = "100001000000001";
	map[5] = "100000000000001";
	map[6] = "100000000000001";
	map[7] = "100000010000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;

	return (map);

}

//fail handle: init, new window, new image
void	init_game(t_game *game)
{
	game->test_map = get_map();//for test, need to change to real_map;

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
}

void	init_player(t_player *player)
{
	//should be parse from map
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	player->left_rotate = false;
	player->right_rotate = false;
}

void	init_hook(t_game *game)
{
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, key_press_handle, game);
	mlx_hook(game->mlx_win, DestroyNotify, StructureNotifyMask, close_handle, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, key_release_handle, game);
}

#include "../includes/cub.h"

void	exit_handle(t_game *game)
{
	mlx_destroy_image(game->mlx_connection, game->win_img.img_ptr);
	mlx_destroy_image(game->mlx_connection, game->map_img.img_ptr);
	mlx_destroy_window(game->mlx_connection, game->mlx_win);
	mlx_destroy_display(game->mlx_connection);
	free(game->mlx_connection);
	free(game->test_map);//TO modify
	exit(0);
}

void	malloc_error(t_game *game)
{
	printf("Error: Malloc.\n");
	(void)game;//to clean t_game
	exit(1);
}

void	d_free(t_game *game)
{
	mlx_destroy_display(game->mlx_connection);
	free(game->mlx_connection);
	malloc_error(game);
}

void	d_w_free(t_game *game)
{
	mlx_destroy_window(game->mlx_connection, game->mlx_win);
	mlx_destroy_display(game->mlx_connection);
	free(game->mlx_connection);
	malloc_error(game);
}

void	d_w_i_free(t_game *game)
{
	mlx_destroy_image(game->mlx_connection, game->win_img.img_ptr);
	mlx_destroy_window(game->mlx_connection, game->mlx_win);
	mlx_destroy_display(game->mlx_connection);
	free(game->mlx_connection);
	malloc_error(game);
}

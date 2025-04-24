#include "../../includes/cub.h"

int	key_press_handle(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		exit_handle(game);
	if (keysym == XK_w)
		game->player.key_up = true;
	if (keysym == XK_s)
		game->player.key_down = true;
	if (keysym == XK_a)
		game->player.key_left = true;
	if (keysym == XK_d)
		game->player.key_right = true;
	if (keysym == XK_Left)
		game->player.left_rotate = true;
	if (keysym == XK_Right)
		game->player.right_rotate = true;
	return (0);
}

int	close_handle(t_game *game)
{
	exit_handle(game);
	return (0);
}

int	key_release_handle(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		exit_handle(game);
	if (keysym == XK_w)
		game->player.key_up = false;
	if (keysym == XK_s)
		game->player.key_down = false;
	if (keysym == XK_a)
		game->player.key_left = false;
	if (keysym == XK_d)
		game->player.key_right = false;
	if (keysym == XK_Left)
		game->player.left_rotate = false;
	if (keysym == XK_Right)
		game->player.right_rotate = false;
	return (0);
}

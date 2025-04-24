#include "../../includes/cub.h"

// void	clear_prev_player(t_player p_player, t_game *game)
// {
// 	int	x;
// 	int	y;
// 	int	size;

// 	size = game->tile_size;

// 	y = p_player.y;
// 	while (y < p_player.y + size)
// 	{
// 		x = p_player.x;
// 		while (x < p_player.x + size)
// 		{
// 			my_pixel_put(&game->win_img, x, y, 0);
// 			x++;
// 		}
// 		y++;
// 	}
// }

int	draw_loop(t_game *game)
{
	t_player	*player = &game->player;
	float		fraction;
	float		start_x;
	int			i;
	t_player	p_player = *player;

	move_player(game);
	//clear_prev_player(p_player, game);
	draw_map(game);
	//draw_sprite
	return (0);
}
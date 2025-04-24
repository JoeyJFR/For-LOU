#include "../../includes/cub.h"

// static int	same_tile(t_game *g, float px, float py)
// {
// 	int	cur_tile_x;
// 	int	cur_tile_y;
// 	int	new_tile_x;
// 	int	new_tile_y;

// 	cur_tile_x = (int)((g->player.x + g->tile_size / 2) / g->tile_size);
// 	cur_tile_y = (int)((g->player.y + g->tile_size / 2) / g->tile_size);
// 	new_tile_x = (int)(px);
// 	new_tile_y = (int)(py);

// 	return (new_tile_x == cur_tile_x && new_tile_y == cur_tile_y);
// }

static int	can_move(float next_center_x, float next_center_y, t_game *g)
{
	float	px;
	float	py;
	float	buffer;

	px = next_center_x / g->tile_size;
	py = next_center_y / g->tile_size;
	buffer = ((g->tile_size / (float)PLAYER_RATIO) / 2.0f + PLAYER_BUFFER) / g->tile_size;
	if (is_wall(px, py, g, g->player.angle))
		return (0);
	if (is_wall(px + buffer, py, g, g->player.angle) \
				|| is_wall(px - buffer, py, g, g->player.angle) \
				|| is_wall(px, py + buffer, g, g->player.angle) \
				|| is_wall(px, py - buffer, g, g->player.angle) \
				|| is_wall(px + buffer, py + buffer, g, g->player.angle) \
				|| is_wall(px - buffer, py + buffer, g, g->player.angle) \
				|| is_wall(px + buffer, py - buffer, g, g->player.angle) \
				|| is_wall(px - buffer, py - buffer, g, g->player.angle))
		return (0);
	return (1);
}

static void	move_direction(t_game *g, float dx, float dy)
{
	t_player	*p;
	float		center_x;
	float		center_y;
	float		next_x;
	float		next_y;

	p = &g->player;
	center_x = p->x + g->tile_size / 2;
	center_y = p->y + g->tile_size / 2;
	next_x = center_x + dx * SPEED;
	next_y = center_y + dy * SPEED;
	if (can_move(next_x, next_y, g))
	{
		p->x += dx * SPEED;
		p->y += dy * SPEED;
	}
}

void	move_up(t_game *g, float cos_angle, float sin_angle)
{
	move_direction(g, cos_angle, sin_angle);
}

void	move_down(t_game *g, float cos_angle, float sin_angle)
{
	move_direction(g, -cos_angle, -sin_angle);
}

void	move_left(t_game *g, float cos_angle, float sin_angle)
{
	move_direction(g, sin_angle, -cos_angle);
}

void	move_right(t_game *g, float cos_angle, float sin_angle)
{
	move_direction(g, -sin_angle, cos_angle);
}

void	move_player(t_game *g)
{
	t_player	*player;
	float		cos_angle;
	float		sin_angle;

	player = &g->player;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= ANGLE;
	if (player->right_rotate)
		player->angle += ANGLE;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->key_up)
		move_up(g, cos_angle, sin_angle);
	if (player->key_down)
		move_down(g, cos_angle, sin_angle);
	if (player->key_left)
		move_left(g, cos_angle, sin_angle);
	if (player->key_right)
		move_right(g, cos_angle, sin_angle);
}

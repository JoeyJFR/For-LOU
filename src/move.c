#include "../includes/cub.h"


void	move_up(t_player *player, float cos_angle, float sin_angle)
{
	player->x += cos_angle * SPEED;
	player->y += sin_angle * SPEED;
}

void	move_down(t_player *player, float cos_angle, float sin_angle)
{
	player->x -= cos_angle * SPEED;
	player->y -= sin_angle * SPEED;
}

void	move_left(t_player *player, float cos_angle, float sin_angle)
{
	player->x -= sin_angle * SPEED;
	player->y += cos_angle * SPEED;
}

void	move_right(t_player *player, float cos_angle, float sin_angle)
{
	player->x += sin_angle * SPEED;
	player->y -= cos_angle * SPEED;
}

void	move_player(t_player *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= ANGLE;
	if (player->right_rotate)
		player->angle += ANGLE;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up)
		move_up(player, cos_angle, sin_angle);
	if (player->key_down)
		move_down(player, cos_angle, sin_angle);
	if (player->key_left)
		move_left(player, cos_angle, sin_angle);
	if (player->key_right)
		move_right(player, cos_angle, sin_angle);
}

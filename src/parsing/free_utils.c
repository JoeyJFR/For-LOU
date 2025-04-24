#include "../../includes/cub.h"

void	free_map(t_map *map, int ***tab)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->map_height - 1)
	{
		x = 0;
		while (x <= map->map_width)
		{
			free(tab[y][x]);
			x++;
		}
		free(tab[y]);
		y++;
	}
	x = 0;
	free(tab[y][x]);
	free(tab[y]);
	free(tab);
}

int	free_texture(t_texture texture)
{
	if (texture.north)
		free(texture.north);
	if (texture.south)
		free(texture.south);
	if (texture.west)
		free(texture.west);
	if (texture.east)
		free(texture.east);
	return (0);
}

#include "../../includes/cub.h"

static int	***free_tab_error(int x, int y, int ***tab, t_map *map)
{
	if (x >= 0)
	{
		while (--x >= 0)
			free(tab[y][x]);
		free(tab[y]);
	}
	while (--y >= 0)
	{
		x = 0;
		while (x <= map->map_width)
			free(tab[y][x++]);
		free(tab[y]);
	}
	free(tab);
	return (NULL);
}

static int	***alloc_last_tab(int ***tab, int y, t_map *map)
{
	int	x;

	x = 0;
	tab[y] = malloc(1 * sizeof(int *));
	if (!tab[y])
		return (free_tab_error(-1, y, tab, map));
	tab[y][x] = ft_calloc(3, sizeof(int));
	if (!tab[y][0])
		return (free_tab_error(x, y, tab, map));
	return (tab);
}

int	***alloc_tab(t_map *map)
{
	int	y;
	int	x;
	int	***tab;

	y = -1;
	tab = malloc(map->map_height * sizeof(int **));
	if (!tab)
		return (NULL);
	while (++y < map->map_height - 1)
	{
		tab[y] = malloc((map->map_width + 1) * sizeof(int *));
		if (!tab[y])
			return (free_tab_error(-1, y, tab, map));
		x = -1;
		while (++x <= map->map_width)
		{
			tab[y][x] = ft_calloc(3, sizeof(int));
			if (!tab[y][x])
				return (free_tab_error(x, y, tab, map));
		}
	}
	if (alloc_last_tab(tab, y, map) == NULL)
		return (NULL);
	return (tab);
}

void	print_table(t_map *map, int ***tab)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->map_height - 1)
	{
		x = 0;
		while (x < map->map_width)
		{
			printf("%d %d %d\n", tab[y][x][0], tab[y][x][1], tab[y][x][2]);
			x++;
		}
		printf("\n\n");
		y++;
	}
	x = 0;
	printf("%d %d %d\n", tab[y][x][0], tab[y][x][1], tab[y][x][2]);
}

#include "../../includes/cub.h"
#include "../../includes/parsing.h"
#include <stdio.h>

static int	direction_to_ascii(char d)
{
	if (d == 'N')
		return (NO);
	if (d == 'E')
		return (EA);
	if (d == 'S')
		return (SO);
	if (d == 'W')
		return (WE);
	return (0);
}

static int check_closed_map_condition(t_map *map, char c, int y_index, char **map_copy, int x)
{
	if ((y_index == 0 || y_index == map->map_height - 2)
		&& (c == '0' || c == 'N' || c == 'E' || c == 'S' || c =='W'))
		return (0);
	else if (x == 0 && (c == '0' || c == 'N' || c == 'E' || c == 'S' || c =='W'))
		return (0);
	else if ((c == '0' || c == 'N' || c == 'E' || c == 'S' || c =='W')
		&& (is_whitespace(map_copy[y_index][x - 1]) == 1 || is_whitespace(map_copy[y_index][x + 1]) == 1
		|| is_whitespace(map_copy[y_index- 1][x]) == 1 || is_whitespace(map_copy[y_index + 1][x]) == 1))
		return (0);
	return (1);
}

static void	fill_map_end(int x, t_map_pos *pos, int y_index, int ****tab)
{
	while (x < pos->end_x)
	{
		(*tab)[y_index][x - pos->start_x + 1][0] = y_index;
		(*tab)[y_index][x - pos->start_x + 1][1] = x - pos->start_x + 1;
		(*tab)[y_index][x - pos->start_x + 1][2] = 2;
		x++;
	}
	ft_memset((*tab)[y_index][x - pos->start_x + 1], -1, 3 * sizeof(int));
}

static void	fill_map_in(int x, int ****tab, t_map_pos *pos, int y_index, char **map_copy)
{
	(*tab)[y_index][x - pos->start_x + 1][0] = y_index;
	(*tab)[y_index][x - pos->start_x + 1][1] = x- pos->start_x + 1;
	if (map_copy[y_index][x] == '1')
		(*tab)[y_index][x - pos->start_x + 1][2] = 1;
	else if (is_whitespace(map_copy[y_index][x]) == 1)
		(*tab)[y_index][x - pos->start_x + 1][2] = 2;
	else
		(*tab)[y_index][x - pos->start_x + 1][2] = 0;
}

static int	fill_player_pos(char **map_copy, int y_index, int x, t_map_pos *pos, t_map *map)
{
	if (map_copy[y_index][x] == 'N' || map_copy[y_index][x] == 'S' || map_copy[y_index][x] == 'W' || map_copy[y_index][x] == 'E')
	{
		if (map->player_direction != 0)
		{
			ft_putstr_fd("Error\nMany players detected\n", 2);
			return (0);
		}
		else
		{
			map->player_direction = direction_to_ascii(map_copy[y_index][x]);
			map->player_x = x - pos->start_x + 1;
			map->player_y = y_index;
		}
	}
	return (1);
}

static int check_closed_map(t_map *map, char **map_copy, t_map_pos *pos, int y_index, int ****tab)
{
	int	x;

	x = 0;
	while (x < pos->start_x - 1)
		x++;
	// printf("%s", map_copy[y_index] + x);
	while (map_copy[y_index][x] && x < pos->end_x)
	{
		// printf("[%d][%d] = '%c'\n", y_index, x, map_copy[y_index][x]);
		if (check_closed_map_condition(map, map_copy[y_index][x], y_index, map_copy, x) == 0)
		{
			ft_putstr_fd("Error\nNo possible closed map found\n", 2);
			return (0);
		}
		fill_map_in(x, tab, pos, y_index, map_copy);
		if (fill_player_pos(map_copy, y_index, x, pos, map) == 0)
			return (0);
		x++;
	}
	fill_map_end(x, pos, y_index, tab);
	return (1);
}

static int	error_handling_map_check(char **map_copy, t_map *map, int ***tab)
{
	if (tab)
		free_map(map, tab);
	free_texture(map->texture);
	ft_free_double(map_copy);
	return (0);
}

int	check_map(t_map *map, char **map_copy, t_map_pos *pos)
{
	int	***tab;
	int	i;

	i = 0;
	tab = alloc_tab(map);
	if (!tab)
		return (error_handling_map_check(map_copy, map, tab));
	while (map_copy[i] && i < map->map_height - 1)
	{
		if (check_closed_map(map, map_copy, pos, i, &tab) == 0)
			return (error_handling_map_check(map_copy, map, tab));
		i++;
	}
	ft_memset(tab[i][0], -1, 3 * sizeof(int));
	if (map->player_direction == 0)
	{
		ft_putstr_fd("Error\nNo player detected\n", 2);
		return (error_handling_map_check(map_copy, map, tab));
	}
	map->real_map = tab;
	// print_table(map, tab);
	return (1);
}

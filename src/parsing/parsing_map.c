#include "../../includes/cub.h"
#include "../../includes/parsing.h"
#include <stdio.h>

static int	error_handling_map_exist(bool wrong_carac, bool one,
		char **map_copy)
{
	if (wrong_carac == true)
		ft_putstr_fd("Error\nThe map has caracters other than 1, 0, whitespaces and player direction (N, E, S or W)\n", 2);
	else if (one == false)
		ft_putstr_fd("Error\nNo possible closed map found\n", 2);
	ft_free_double(map_copy);
	return (0);
}

static int	check_map_exist(char **map_copy, t_map_pos *pos)
{
	int		i;
	int		j;
	bool	one;
	bool	wrong_carac;

	i = 0;
	one = false;
	wrong_carac = false;
	while (map_copy[i])
	{
		if (check_line_whitespaces(map_copy[i]) == 0)
			pos->end_y = i + 1;
		if (map_pre_checking(map_copy[i], &one, &wrong_carac, pos) == 0)
			break ;
		i++;
	}
	if (wrong_carac == true || one == false)
		return (error_handling_map_exist(wrong_carac, one, map_copy));
	return (1);
}

static void	find_first_start_x(char *map_copy, t_map_pos *pos)
{
	int	i;

	i = 0;
	while (map_copy[i] && is_whitespace(map_copy[i]) == 1)
		i++;
	pos->start_x = i + 1;
}

int	parse_map(t_map *map, char **map_copy)
{
	t_map_pos	pos;

	ft_memset(&pos, 0, sizeof(t_map_pos));
	pos.start_y = 1;
	find_first_start_x(map_copy[0], &pos);
	if (check_map_exist(map_copy, &pos) == 0)
	{
		free_texture(map->texture);
		return (0);
	}
	map->map_height = pos.end_y + 1;
	map->map_width = pos.end_x - pos.start_x + 2;
	if (check_map(map, map_copy, &pos) == 0)
		return (0);
	return (1);
}

#include "../../includes/parsing.h"

static int	map_carac_checking(char map_carac, bool *one, bool *wrong_carac)
{
	if (map_carac == '1')
		*one = true;
	if (is_right_carac(map_carac) == 0)
	{
		*wrong_carac = true;
		return (0);
	}
	return (1);
}

int	map_pre_checking(char *map_copy, bool *one, bool *wrong_carac,
	t_map_pos *pos)
{
	int		i;
	bool	x;

	i = 0;
	x = false;
	while (map_copy[i])
	{
		if (map_carac_checking(map_copy[i], one, wrong_carac) == 0)
			return (0);
		if (x == false && is_whitespace(map_copy[i]) == 0
			&& (i + 1) < pos->start_x)
		{
			x = true;
			pos->start_x = i + 1;
		}
		if (check_line_whitespaces(map_copy + i + 1) == 1)
		{
			if (pos->end_x < (i + 1))
				pos->end_x = i + 1;
			break ;
		}
		i++;
	}
	return (1);
}

#include "../../includes/cub.h"
#include "../../includes/parsing.h"

static int	error_handling_color(char **color, char *msg)
{
	ft_free_double(color);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return (0);
}

static int	get_color_detail(t_map *map, char *color, t_type type, int index)
{
	int	i;
	int	nb;

	i = 0;
	while (color[i])
	{
		if (ft_isdigit(color[i]) == 0)
			return (0);
		i++;
	}
	nb = ft_atoi(color); //check atoi overflow ??
	if (nb < 0 || nb > 255)
		return (0);
	if (type == C)
		(*map).color.ceilling[index] = nb;
	if (type == F)
		(*map).color.floor[index] = nb;
	return (1);
}

static int	check_comas(char *elem)
{
	int	coma;
	int	i;

	i = 0;
	coma = 0;
	while (elem[i])
	{
		if (elem[i] == ',')
			coma++;
		i++;
	}
	if (coma != 2)
	{
		ft_putstr_fd("Error\nToo many comas for colors\n", 2);
		return (0);
	}
	return (1);
}

int	handle_elem_color(t_map *map, t_elem_checker *check, char **elem,
		t_type type)
{
	char	**color;
	int		i;

	if (check_comas(elem[1]) == 0)
		return (0);
	i = -1;
	color = ft_split(elem[1], ",");
	if (!color)
		return (0);
	while (color[++i])
	{
		if (i == 3)
			return (error_handling_color(color, "Too many colors\n"));
		if (get_color_detail(map, color[i], type, i) == 0)
			return (error_handling_color(color, "Color has wrong format\n"));
	}
	if (i != 3)
		return (error_handling_color(color, "Not enough colors\n"));
	if (type == C)
		check->ceilling = true;
	else if (type == F)
		check->floor = true;
	free(elem[1]);
	ft_free_double(color);
	return (1);
}

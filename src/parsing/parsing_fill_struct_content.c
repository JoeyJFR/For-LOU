#include "../../includes/cub.h"
#include "../../includes/parsing.h"

static void	update_elem_texture(t_map *map, t_elem_checker *check,
	char **elem, t_type type)
{
	if (type == NO)
	{
		(*map).texture.north = elem[1];
		check->north = true;
	}
	else if (type == EA)
	{
		(*map).texture.east = elem[1];
		check->east = true;
	}
	else if (type == SO)
	{
		(*map).texture.south = elem[1];
		check->south = true;
	}
	else if (type == WE)
	{
		(*map).texture.west = elem[1];
		check->west = true;
	}
}

static int	handle_elem_texture(t_map *map, t_elem_checker *check,
		char **elem, t_type type)
{
	int		fd;
	char	*ext;

	ext = ft_strrchr(elem[1], '.');
	if (!ext || ft_strcmp(ext, ".xpm"))
	{
		ft_putstr_fd("Error\nWrong content filename, should be .xpm\n", 2);
		return (0);
	}
	fd = open(elem[1], O_RDONLY); // TODO only .xpm ??
	if (fd == -1)
	{
		ft_putstr_fd(elem[1], 2);
		perror(" ");
		return (0);
	}
	close(fd);
	update_elem_texture(map, check, elem, type);
	return (1);
}

int	handle_elem_content(t_map *map, t_elem_checker *check, char **elem,
		t_type type)
{
	if (elem[1] == NULL || elem[2])
	{
		ft_putstr_fd("Error\nInccorect argument(s) for texture or color ", 2);
		ft_putstr_fd(elem[0], 2);
		ft_putstr_fd("/n", 2);
		return (0);
	}
	if (type == NO || type == SO || type == EA || type == WE)
		return (handle_elem_texture(map, check, elem, type));
	else if (type == C || type == F)
		return (handle_elem_color(map, check, elem, type));
	return (0);
}

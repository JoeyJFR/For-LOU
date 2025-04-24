#include "../../includes/cub.h"
#include "../../includes/parsing.h"

static int	check_elem(t_elem_checker *check)
{
	if (check->ceilling == true
		&& check->floor == true
		&& check->east == true
		&& check->north == true
		&& check->south == true
		&& check->west == true)
		return (1);
	return (0);
}

static int	compare_elem(t_map *map, t_elem_checker *check, char **elem)
{
	// printf("elem = %s\n", elem[0]); // TODO delete
	if (ft_strcmp(elem[0], NORTH) == 0 && check->north == false)
		return (handle_elem_content(map, check, elem, NO));
	else if (ft_strcmp(elem[0], SOUTH) == 0 && check->south == false)
		return (handle_elem_content(map, check, elem, SO));
	else if (ft_strcmp(elem[0], EAST) == 0 && check->east == false)
		return (handle_elem_content(map, check, elem, EA));
	else if (ft_strcmp(elem[0], WEST) == 0 && check->west == false)
		return (handle_elem_content(map, check, elem, WE));
	else if (ft_strcmp(elem[0], CEILLING) == 0 && check->ceilling == false)
		return (handle_elem_content(map, check, elem, C));
	else if (ft_strcmp(elem[0], FLOOR) == 0 && check->floor == false)
		return (handle_elem_content(map, check, elem, F));
	ft_putstr_fd("Error\nAt least one element is incorrect\n", 2);
	return (0);
}

static int	fill_elements(char *line, t_map *map, t_elem_checker *check)
{
	char	**elem;

	elem = ft_split(line, WHITESPACES);
	if (!elem)
		return (free_texture(map->texture));
	if (!elem[0])
	{
		free(elem);
		return (1);
	}
	if (compare_elem(map, check, elem) == 0)
	{
		ft_free_double(elem);
		return (free_texture(map->texture));
	}
	free(elem[0]);
	free(elem);
	return (1);
}

static int	error_handling(int fd, char *line, char *msg)
{
	close(fd);
	if (line)
		free(line);
	if (msg)
		ft_putstr_fd(msg, 2);
	return (0);
}

int	fill_struct(char **map_copy, t_map *map, int fd)
{
	char			*line;
	t_elem_checker	check;

	// printf("FILL STRUCT\n");
	ft_memset(&check, false, sizeof(t_elem_checker));
	line = get_next_line(fd);
	if (!line)
		return (error_handling(fd, NULL, "Error\nEmpty file ???\n"));
	while (line != NULL)
	{
		if (fill_elements(line, map, &check) == 0)
			return (error_handling(fd, line, NULL));
		free(line);
		if (check_elem(&check) == 1)
			return (1);
		line = get_next_line(fd); //TODO how to protect ??
	}
	if (check_elem(&check) == 0)
		return (free_texture(map->texture));
	return (1);
}

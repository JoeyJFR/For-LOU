#include "../../includes/cub.h"
#include "../../includes/parsing.h"

static int	check_map_file(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strcmp(ext, ".cub"))
	{
		ft_putstr_fd("Error\nWrong filename, should be .cub\n", 2);
		return (0);
	}
	return (1);
}

static int	check_map_access(char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(filename, 2);
		perror(" ");
		return (0);
	}
	return (1);
}

void	print_texture_color(t_map map)
{
	printf("north = %s\n", map.texture.north);
	printf("south = %s\n", map.texture.south);
	printf("east = %s\n", map.texture.east);
	printf("west = %s\n", map.texture.west);
	printf("ceilling = %d, %d, %d\n", map.color.ceilling[0],
		map.color.ceilling[1], map.color.ceilling[2]);
	printf("floor = %d, %d, %d\n", map.color.floor[0],
		map.color.floor[1], map.color.floor[2]);
}

void	parse_info(char *filename, t_map *map)
{
	char	**map_copy;
	int		fd;

	map_copy = NULL;
	if (check_map_file(filename) == 0 || check_map_access(filename, &fd) == 0)
		exit(EXIT_FAILURE);
	if (fill_struct(map_copy, map, fd) == 0)
		exit(EXIT_FAILURE);
	// print_texture_color(*map);
	map_copy = copy_map(fd, map_copy);
	if (!map_copy)
	{
		free_texture(map->texture);
		exit(EXIT_FAILURE);
	}
	// ft_print_double(map_copy);
	if (parse_map(map, map_copy) == 0)
		exit(EXIT_FAILURE);
	ft_free_double(map_copy);
	// printf("player x = %d, y = %d, direction = %c\n", map->player_x, map->player_y, map->player_direction);
	// printf("map height = %d and map width = %d\n", map->map_height, map->map_width);
}

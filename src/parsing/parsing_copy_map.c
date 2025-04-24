#include <unistd.h>

#include "../../includes/parsing.h"

static char	**reallocate_copy(char **ret, char **strs, char *str)
{
	int		i;

	i = 0;
	while (strs[i])
	{
		ret[i] = strs[i];
		i++;
	}
	ret[i] = ft_strdup(str);
	if (!ret[i])
	{
		free(strs);
		return (free_strs_index(ret, i));
	}
	ret[i + 1] = NULL;
	free(strs);
	return (ret);
}

static char	**get_copy(char **strs, char *str, int index)
{
	char	**ret;

	if (!str)
		return (strs);
	ret = malloc((index + 1) * sizeof(char *));
	if (!ret)
		return (free_strs_index(strs, index));
	if (index == 1)
	{
		ret[0] = ft_strdup(str);
		if (!ret[0])
		{
			free(ret);
			return (NULL);
		}
		ret[1] = NULL;
	}
	else
	{
		ret = reallocate_copy(ret, strs, str);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

static char	**error_handling(int fd, char *line, char *msg)
{
	close(fd);
	if (line)
		free(line);
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
	}
	return (NULL);
}

static char	*skip_whitespaces(int fd, char *line)
{
	while (line != NULL && check_line_whitespaces(line) == 1)
	{
		free(line);
		line = get_next_line(fd); //TODO how to protect ??
	}
	return (line);
}

char	**copy_map(int fd, char **map_copy)
{
	char	*line;
	int		i;

	i = 1;
	line = get_next_line(fd);
	if (!line)
		return (error_handling(fd, NULL, "No map was found\n"));
	line = skip_whitespaces(fd, line);
	if (!line)
		return (error_handling(fd, NULL, "No map was found\n"));
	map_copy = get_copy(map_copy, line, i);
	if (!map_copy)
		return (error_handling(fd, line, NULL));
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd); //TODO how to protect ??
		i++;
		map_copy = get_copy(map_copy, line, i);
		if (!map_copy)
			return (error_handling(fd, line, NULL));
	}
	close(fd);
	return (map_copy);
}

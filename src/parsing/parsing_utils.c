#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // TODO delete with function print

void	ft_print_double(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		printf("line %zu : %s", i, strs[i]);
		i++;
	}
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_right_carac(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S'
		|| c == 'W' || is_whitespace(c) == 1)
		return (1);
	return (0);
}

int	check_line_whitespaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

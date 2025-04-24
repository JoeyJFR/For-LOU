#include <unistd.h>
#include <stdlib.h>

char	**ft_free_double(char **strs)
{
	size_t	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
		free (strs);
		strs = NULL;
	}
	return (NULL);
}

char	**free_strs_index(char **strs, int i)
{
	while (i > 0)
		free(strs[--i]);
	free(strs);
	return (NULL);
}

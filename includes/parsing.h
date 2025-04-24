#ifndef PARSING_H
# define PARSING_H

#include <fcntl.h>
# include "../libft/srcs/gnl/get_next_line.h"
# include "../libft/srcs/libft/libft.h"
#include "../includes/cub.h"

# define BLUE		"\001\033[1;34m\002"
# define BOLD_RED	"\001\033[1;31m\002"
# define CYAN		"\001\033[1;36m\002"
# define GREEN		"\001\033[1;32m\002"
# define PURPLE		"\001\033[0;35m\002"
# define RED		"\001\033[0;31m\002"
# define WHITE_BOLD	"\001\033[1;37m\002"
# define YELLOW		"\001\033[1;33m\002"
# define RESET      "\001\033[0m\002"

# define WHITESPACES " \t\r\n\v\f"
# define NORTH "NO"
# define SOUTH "SO"
# define EAST "EA"
# define WEST "WE"
# define CEILLING "C"
# define FLOOR "F"

typedef enum e_type
{
	C,
	F,
	EA = 69,
	NO = 78,
	SO = 83,
	WE = 87
}	t_type;

typedef struct s_elem_checker
{
	bool	north;
	bool	south;
	bool	west;
	bool	east;
	bool	ceilling;
	bool	floor;
}	t_elem_checker;

typedef struct s_map_pos
{
	int	start_y;
	int	end_y;
	int	start_x;
	int	end_x;
}	t_map_pos;


void	parse_info(char *filename, t_map *map);
char	**copy_map(int fd, char **map_copy);
int		fill_struct(char **map_copy, t_map *map, int fd);
int		free_texture(t_texture texture);
int		parse_map(t_map *map, char **map_copy);
int	check_line_whitespaces(char *line);
int	check_map(t_map *map, char **map_copy, t_map_pos *pos);
int	handle_elem_content(t_map *map, t_elem_checker *check, char **elem, t_type type);
int	handle_elem_color(t_map *map, t_elem_checker *check, char **elem, t_type type);
int	map_pre_checking(char *map_copy, bool *one, bool *wrong_carac,
	t_map_pos *pos);
int	***alloc_tab(t_map *map);

/*  UTILS  */
char	**ft_free_double(char **strs);
char	**free_strs_index(char **strs, int i);
void	ft_print_double(char **strs);
int	is_whitespace(char c);
void	free_map(t_map *map, int ***tab);
int	free_texture(t_texture texture);
int	check_line_whitespaces(char *line);
int	is_right_carac(char c);


// delete
void print_table(t_map *map, int ***tab);

#endif

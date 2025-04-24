#ifndef CUB_H
# define CUB_H

# include "../libft/srcs/libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define WIDTH 1280
# define HEIGHT 720
# define PI 3.14159265359
# define SPEED 3
# define ANGLE 0.034906585f
# define FOV   1.0471975512f
# define RAY_NB 120
# define RAY_LENGTH 400
# define PLAYER_BUFFER 5
# define PLAYER_RATIO 5


# define MINIMAP_MODE 0

// # define W 119
// # define A 97
// # define S 115
// # define D 100
// # define LEFT 65361
// # define RIGHT 65363

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_texture;

typedef struct s_color
{
	int	ceilling[3];
	int	floor[3];
}	t_color;

typedef struct s_map
{

	int			***real_map; // real_map[y_pos][x_pos][value] = end by flag of -1;
	int			map_height; // just one -1 for the last row
	int			map_width; // count the -1 (+1)
	int			player_direction; //ASCII for now and later calculation
	int			player_x;
	int			player_y;
	t_color		color;
	t_texture	texture;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_win_img
{
	void	*img_ptr;
	char	*pixel_ptr;
	int		bpp;
	int		line_length;
	int		endian;	
}	t_win_img;

typedef struct s_map_img
{
	void	*img_ptr;
	char	*pixel_ptr;
	int		bpp;
	int		line_length;
	int		endian;	
}	t_map_img;

typedef struct s_game
{
	void		*mlx_connection;
	void		*mlx_win;
	t_win_img	win_img;
	t_map_img	map_img;

	int			tile_size;

	t_player	player;
	t_map		map_info;
}	t_game;

//side: 0 for X, 1 for Y
typedef struct s_ray
{
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	chage_along_ray_convert_to_1_unitx;
	float	chage_along_ray_convert_to_1_unity;
	float	d_x;
	float	d_y;
	int		x_move;
	int		y_move;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
}	t_ray;


/* init */
void	init_game(t_game *game);
void	init_player(t_game *game);
void	init_hook(t_game *game);

/* hook */
int		key_press_handle(int keysym, t_game *game);
int		close_handle(t_game *game);
int		key_release_handle(int keysym, t_game *game);

/* draw */

void 	draw_map(t_game *g);
void	my_pixel_put(t_win_img *img, int x, int y, int color);
int		is_wall(float x, float y, t_game *g, float angle);

/* draw loop*/
int		draw_loop(t_game *game);

/* utils */
void	exit_handle(t_game *game);
void	malloc_error(t_game *game);
void	d_free(t_game *game);
void	d_w_free(t_game *game);
void	d_w_i_free(t_game *game);
void	free_map(t_map *map, int ***tab);
int		free_texture(t_texture texture);

/* move */
void	move_player(t_game *g);

#endif
#include "../includes/cub.h"
#include "../includes/parsing.h"

void	error_handling_arg(int ac)
{
	if (ac == 1)
		ft_putstr_fd("Error\n2 arguments needed\nUsage : ./cub3D filename\n", 2);
	else
		ft_putstr_fd("Error\nToo many arguments\nUsage : ./cub3D filename\n", 2);
	exit(EXIT_FAILURE);
}


int	main(int ac, char **av)
{
	t_game	game;
	t_map	map;

	if (ac != 2)
		error_handling_arg(ac);
	ft_memset(&map, 0, sizeof(t_map));
	parse_info(av[1], &map);

	//game init
	game.map_info = map;
	init_game(&game);
	init_player(&game);
	init_hook(&game);
	draw_map(&game);

	// init_minimap(); //Bonus

	//game hook
	mlx_loop_hook(game.mlx_connection, draw_loop, &game);
	mlx_loop(game.mlx_connection);
	return (0);
}

//in own Makefile: shall I add mlx as a dependence: whether during evaluation
// someone may "touch" a file in the mlx folder and think our program should compile again??

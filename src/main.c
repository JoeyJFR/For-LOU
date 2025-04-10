#include "../includes/cub.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_game	game;
	//parse_input(ac, av); //TO DO

	//parse_map(ac, av); //TO DO

	//game init
	init_game(&game);
	init_player(&game.player);
	init_hook(&game);
	draw_square(WIDTH / 2, HEIGHT / 2, 10, 0x00FF00, &game);
	// init_minimap(); //Bonus
	

	//game hook
	mlx_loop_hook(game.mlx_connection, draw_loop, &game);
	mlx_loop(game.mlx_connection);
	return (0);
}
#include "cub3d.h"

float correctFisheye(float distance, float ra, float playerAngle) {
	float ca = playerAngle - ra;
	if (ca < 0) ca += 2 * PI;
	if (ca > 2 * PI) ca -= 2 * PI;
	return distance * cos(ca);
}

int jkl = -1;
int yui = 0;

void	test2(t_structure_main *w)
{
	t_rescale_params	params;
	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.width, w->s_win.height);
	w->s_img.addr = mlx_get_data_addr(w->s_img.buffer, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	draw_map(w);
	drawRays2D(w);
	mlx_put_image_to_window(w->s_win.mlx, w->s_win.win, w->s_img.buffer, 0, 0);
	int new_sprite_width = w->s_map.mapS;
	int new_sprite_height = w->s_map.mapS;
	int sprite_x = w->s_player.px - new_sprite_width / 2;
	int sprite_y = w->s_player.py - new_sprite_height / 2;
		params.original_img = w->s_img.roomadslam[jkl];
		params.original_width = 112;
		params.original_height = 112;
		params.new_width = w->s_map.mapS;
		params.new_height = w->s_map.mapS;
		params.px = w->s_player.px - w->s_map.mapS / 2;
		params.py = w->s_player.py - w->s_map.mapS / 2;
	rescale_image(&params, w);
}

void	test(t_structure_main *w)
{
	int	x;
	int y;

	if (yui < 10)
	{
		usleep(1000);
		yui++;
	}
	else
	{
		yui = 0;
		jkl++;
		test2(w);
		mlx_mouse_get_pos(w->s_win.mlx, w->s_win.win, &x, &y);
		if ((x > 0 && x < w->s_win.height) && (y > 0 && y < w->s_win.width))
			if (x != w->s_win.height/2)
			{
				if (x < w->s_win.height/2)
					deal_key(65361,w);
				else
					deal_key(65363,w);
			}
	}
	if (jkl == 10)
		jkl = -1;
}

int	setup_and_load_map(int argc, char **argv, t_structure_main *w)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (0);
	}
	parse_map("map.cub", &w->s_map);
	if (!parse_map(argv[1], &w->s_map))
	{
		printf("Failed to load the map or map is not closed. Exiting...\n");
		return (0);
	}
	if (w->s_map.map == NULL)
	{
		printf("Failed to load the map.\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_structure_main	w;

	if (!setup_and_load_map(argc, argv, &w))
		return (1);
	init_windows(&w);
	mlx_loop_hook(w.s_win.mlx, (void *)test, &w);
	mlx_hook(w.s_win.win, 2, 1L<<0, deal_key, &w);
	mlx_hook(w.s_win.win, 17, 0, (void *)kill_prog, &w);
	mlx_loop(w.s_win.mlx);
	if (w.s_map.map)
	{
		free(w.s_map.map);
	}
	return (0);
}

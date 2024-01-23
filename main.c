/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:45:52 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/20 11:08:57 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	setup_and_load_map(int argc, char **argv, t_structure_main *w, t_texture *textures)
{
	if (argc > 2)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return (0);
	}
	if (!load_cub_file("map.cub", textures, &w->s_map))
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
	t_global_struct		global_struct;

	w.t = malloc(sizeof(t_texture));
	if (w.t == NULL)
	{
    // Gérer l'erreur d'allocation
	}
	ft_memset(w.t, 0, sizeof(t_texture));
	global_struct.w = &w;
	global_struct.state.jkl = -1;
	global_struct.state.yui = 0;
	if (!setup_and_load_map(argc, argv, &w, w.t))
		return (1);
	init_windows(&w);
	mlx_loop_hook(w.s_win.mlx, (void *)sleep_mouse, &global_struct);
	mlx_hook(w.s_win.win, 2, 1L << 0, deal_key, &w);
	mlx_hook(w.s_win.win, 17, 0, (void *)kill_prog, &w);
	mlx_loop(w.s_win.mlx);
	if (w.s_map.map)
	{
		free(w.s_map.map);
	}
	return (0);
}

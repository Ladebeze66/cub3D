/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:09:23 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/17 21:15:02 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_structure_main *w)
{
	w->s_player.px = 10;
	w->s_player.py = 10;
	w->s_player.pa = 0.1;
	w->s_player.pdx = cos(w->s_player.pa) * 5;
	w->s_player.pdy = sin(w->s_player.pa) * 5;
}

void	init_mlx_and_window(t_structure_main *w)
{
	w->s_win.mlx = mlx_init();
	if (w->s_win.mlx == NULL)
	{
		fprintf(stderr, "Erreur : Échec de mlx_init.\n");
		exit(1);
	}
	w->s_win.win = mlx_new_window(w->s_win.mlx, w->s_win.width,
			w->s_win.height, "WF99");
	if (w->s_win.win == NULL)
	{
		fprintf(stderr, "Erreur : Échec de mlx_new_window.\n");
		exit(1);
	}
}

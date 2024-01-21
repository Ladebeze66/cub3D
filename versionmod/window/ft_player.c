/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:09:23 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/21 14:33:45 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_player(t_structure_main *w)
{
    // Ajouter des logs pour vérifier les valeurs
    printf("Initialisation du joueur:\n");
    printf("Position X: %f\n", w->s_map.player_x);
    printf("Position Y: %f\n", w->s_map.player_y);

    w->s_player.px = w->s_map.player_x;
    w->s_player.py = w->s_map.player_y;

    if (w->s_map.player_direction == 'N')
    {
        w->s_player.pa = M_PI;
        w->s_player.pdx = 0;
        w->s_player.pdy = -5;
    }
    else if (w->s_map.player_direction == 'S')
    {
        w->s_player.pa = 0;
        w->s_player.pdx = 0;
        w->s_player.pdy = 5;
    }
    else if (w->s_map.player_direction == 'E')
    {
        w->s_player.pa = M_PI / 2;
        w->s_player.pdx = 5;
        w->s_player.pdy = 0;
    }
    else if (w->s_map.player_direction == 'W')
    {
        w->s_player.pa = 3 * M_PI / 2;
        w->s_player.pdx = -5;
        w->s_player.pdy = 0;
    }

    // Ajouter des logs pour vérifier les valeurs après l'initialisation
    printf("Angle de direction: %f radians\n", w->s_player.pa);
    printf("Vecteur de déplacement X: %f\n", w->s_player.pdx);
    printf("Vecteur de déplacement Y: %f\n", w->s_player.pdy);
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

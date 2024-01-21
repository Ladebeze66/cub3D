/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:17:56 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/21 21:12:41 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*kill_prog(t_structure_main *w)
{
	int	i;

	mlx_destroy_window(w->s_win.mlx, w->s_win.win);
	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	mlx_destroy_image(w->s_win.mlx, w->s_img.img_player);
	mlx_destroy_image(w->s_win.mlx, w->s_img.img_wall);
	mlx_destroy_image(w->s_win.mlx, w->s_img.pedro_wall);
	i = -1;
	while (++i <= 10)
		mlx_destroy_image(w->s_win.mlx, w->s_img.roomadslam[i]);
	if (w->s_map.map)
	{
		free(w->s_map.map);
		w->s_map.map = NULL;
	}
	mlx_destroy_display(w->s_win.mlx);
	free(w->s_win.mlx);
	exit(0);
	return (0);
}

void adjust_player_angle(t_structure_main *w, int key)
{
    double angle_adjustment;
	printf("adjust_player_angle: Key pressed: %d\n", key);
	printf("adjust_player_angle: Before adjustment - pa: %f\n", w->s_player.pa);

    if (key != 65361 && key != 65363)
        return;
    angle_adjustment = 16 * ((PI / 3) / NUMRAY);
    if (key == 65361)
    {
        w->s_player.pa -= angle_adjustment;
        if (w->s_player.pa < 0)
            w->s_player.pa += 2 * PI;
    }
    else
    {
        w->s_player.pa += angle_adjustment;
        if (w->s_player.pa > 2 * PI)
            w->s_player.pa -= 2 * PI;
    }
    w->s_player.pdx = cos(w->s_player.pa) * 5;
    w->s_player.pdy = sin(w->s_player.pa) * 5;
    printf("adjust_player_angle: After adjustment - pa: %f\n", w->s_player.pa);
}

void handle_movement_keys(t_structure_main *w, int key)
{
	if (key == 119 || key == 100 || key == 115 || key == 97)
	{
		adjust_player_angle(w, key);
		move(w, key);
	}
}

int	deal_key(int key, t_structure_main *w)
{
	printf("deal_key: Key received: %d\n", key);
	if (key == 65307)
	{
		kill_prog(w);
	}
	else if (key == 65361 || key == 65363)
	{
		adjust_player_angle(w, key);
	}
	else
	{
		handle_movement_keys(w, key);
	}
	printf("deal_key: Key handled: %d\n", key);
	return (key);
}

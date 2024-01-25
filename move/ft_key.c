/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:17:56 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/25 12:41:41 by fgras-ca         ###   ########.fr       */
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

void	adjust_player_angle(t_structure_main *w, int key)
{
	double	angle_adjustment;

	if (key != 65361 && key != 65363)
		return ;
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
}

void	handle_movement_keys(int key, t_structure_main *w)
{
	if (key == 119 || key == 100 || key == 115 || key == 97)
		move(key, w);
}

int	deal_key(int key, t_structure_main *w)
{
	if (key == 65307)
	{
		kill_prog(w);
	}
	else if (key == 65361 || key == 65363)
	{
		adjust_player_angle(w, key);
	}
	else if (key == 65362 || key == 65364 || key == 114 || key == 102)
	{
	}
	else if (key == 101) //e door
	{
		printf("Touche 101\n");
		if (w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + cos(w->s_player.pa) * 7)/w->s_map.mapS)] == '1')
			w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + cos(w->s_player.pa) * 7)/w->s_map.mapS)] = '2';
		else if (w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + cos(w->s_player.pa) * 7)/w->s_map.mapS)] == '2')
			w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + cos(w->s_player.pa) * 7)/w->s_map.mapS)] = '1';
	}
	else
	{
		handle_movement_keys(key, w);
	}
	return (key);
}

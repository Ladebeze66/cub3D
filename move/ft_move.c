/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:08:25 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/25 15:09:55 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_structure_main *w, int key)
{
	t_position_params	params;
	int					future_px;
	int					future_py;

if (key == 119 )
	{
		if (w->s_map.map[(int)((w->s_player.py)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + (cos(w->s_player.pa) * w->s_map.mapS))/w->s_map.mapS)]=='0')
			w->s_player.px += cos(w->s_player.pa) * w->s_map.mapS;
		if (w->s_map.map[(int)((w->s_player.py + (sin(w->s_player.pa) * w->s_map.mapS))/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px)/w->s_map.mapS)]=='0')
			w->s_player.py += sin(w->s_player.pa) * w->s_map.mapS;
	}
}

void	move_backward(t_structure_main *w, int key)
{
	t_position_params	params;
	int					future_px;
	int					future_py;

	if (key == 115 )
	{
		if (w->s_map.map[(int)((w->s_player.py)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + (cos(w->s_player.pa + (PI)) * w->s_map.mapS))/w->s_map.mapS)]=='0')
			w->s_player.px += cos(w->s_player.pa + (PI)) * w->s_map.mapS;
		if (w->s_map.map[(int)((w->s_player.py + (sin(w->s_player.pa + (PI)) * w->s_map.mapS))/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px)/w->s_map.mapS)]=='0')
			w->s_player.py += sin(w->s_player.pa + (PI)) * w->s_map.mapS;
	}
}

void	move_right(t_structure_main *w, int key)
{
	t_position_params	params;
	int					future_px;
	int					future_py;

	if (key == 100 )
	{	   
		if (w->s_map.map[(int)((w->s_player.py)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + (cos(w->s_player.pa + (PI/2)) * w->s_map.mapS))/w->s_map.mapS)]=='0')
			w->s_player.px += cos(w->s_player.pa + (PI/2)) * w->s_map.mapS;
		if (w->s_map.map[(int)((w->s_player.py + (sin(w->s_player.pa + (PI/2)) * w->s_map.mapS))/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px)/w->s_map.mapS)]=='0')
			w->s_player.py += sin(w->s_player.pa + (PI/2)) * w->s_map.mapS;
	}
}

void	move_left(t_structure_main *w, int key)
{
	t_position_params	params;
	int					future_px;
	int					future_py;

	if (key == 97)
	{
		if (w->s_map.map[(int)((w->s_player.py)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + (cos(w->s_player.pa + (3*(PI/2))) * w->s_map.mapS))/w->s_map.mapS)]=='0')
			w->s_player.px += cos(w->s_player.pa + (3*(PI/2))) * w->s_map.mapS;
		if (w->s_map.map[(int)((w->s_player.py + (sin(w->s_player.pa + (3*(PI/2))) * w->s_map.mapS))/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px)/w->s_map.mapS)]=='0')
			w->s_player.py += sin(w->s_player.pa + (3*(PI/2))) * w->s_map.mapS;
	}
}


void	move(int key, t_structure_main *w)
{
	move_forward(w, key);
	move_backward(w, key);
	move_right(w, key);
	move_left(w, key);
}

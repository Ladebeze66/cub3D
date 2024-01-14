/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:08:25 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/11 20:35:09 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_structure_main *w, int key)
{
	t_position_params	params;
	int					future_px;
	int					future_py;

	if (key != 119)
		return ;
	params.future_px = &future_px;
	params.future_py = &future_py;
	params.pdx = w->s_player.pdx;
	params.pdy = w->s_player.pdy;
	params.collisionBuffer = COLBUF;
	params.px = w->s_player.px;
	params.py = w->s_player.py;
	calculate_future_position(&params);
	if (check_collision(w, future_px, future_py))
	{
		w->s_player.px += w->s_player.pdx;
		w->s_player.py += w->s_player.pdy;
	}
}

void	move_backward(t_structure_main *w, int key)
{
	t_position_params	params;
	int					future_px;
	int					future_py;

	if (key != 115)
		return ;
	params.future_px = &future_px;
	params.future_py = &future_py;
	params.pdx = -w->s_player.pdx;
	params.pdy = -w->s_player.pdy;
	params.collisionBuffer = COLBUF;
	params.px = w->s_player.px;
	params.py = w->s_player.py;
	calculate_future_position(&params);
	if (check_collision(w, future_px, future_py))
	{
		w->s_player.px -= w->s_player.pdx;
		w->s_player.py -= w->s_player.pdy;
	}
}

void	move_right(t_structure_main *w, int key)
{
	t_position_params	params;
	int					future_px;
	int					future_py;

	if (key != 100)
		return ;
	params.future_px = &future_px;
	params.future_py = &future_py;
	params.pa = w->s_player.pa;
	params.collisionBuffer = COLBUF;
	params.px = w->s_player.px;
	params.py = w->s_player.py;
	params.direction = 'd';
	calculate_future_position_right_left(&params);
	if (check_collision(w, future_px, future_py))
	{
		w->s_player.px = future_px;
		w->s_player.py = future_py;
	}
}

void	move_left(t_structure_main *w, int key)
{
	t_position_params	params;
	int					future_px;
	int					future_py;

	if (key != 97)
		return ;
	params.future_px = &future_px;
	params.future_py = &future_py;
	params.pa = w->s_player.pa;
	params.collisionBuffer = COLBUF;
	params.px = w->s_player.px;
	params.py = w->s_player.py;
	params.direction = 'a';
	calculate_future_position_right_left(&params);
	if (check_collision(w, future_px, future_py))
	{
		w->s_player.px = future_px;
		w->s_player.py = future_py;
	}
}

void	move(int key, t_structure_main *w)
{
	move_forward(w, key);
	move_backward(w, key);
	move_right(w, key);
	move_left(w, key);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_horizontal_ray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:53:47 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/14 18:34:26 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_ra_equal_pi(t_ray_calc_params *params)
{
	*params->rx = params->w->s_player.px;
	*params->ry = params->w->s_player.py;
	params->dof = DOF;
}

void	inithorizontalray(t_ray_calc_params *params)
{
	float	atan;
	int		tilesize;

	atan = -1 / tan(params->ra);
	tilesize = params->w->s_map.mapS;
	if (params->ra != PI)
		handle_ra_not_equal_pi(params, atan, tilesize);
	else
		handle_ra_equal_pi(params);
}

void	update_ray_params(t_ray_calc_params *params, int mx, int my)
{
	int	mp;

	mp = my * params->w->s_map.mapX + mx;
	if (mp >= 0 && mp < params->w->s_map.mapX * params->w->s_map.mapY
		&& params->w->s_map.map[mp] == '1')
	{
		params->dof = DOF;
		*params->disRay = dist(params->w->s_player.px, params->w->s_player.py,
				*params->rx, *params->ry);
		if (params->ra > PI)
			*params->wallDir = NORTH;
		else
			*params->wallDir = SOUTH;
	}
}

void	processhorizontalray(t_ray_calc_params *params)
{
	int	mx;
	int	my;
	int	tilesize;

	tilesize = params->w->s_map.mapS;
	*params->disRay = DISRAY;
	while (params->dof < DOF)
	{
		mx = (int)(*params->rx) / tilesize;
		my = (int)(*params->ry) / tilesize;
		update_ray_params(params, mx, my);
		if (params->dof < DOF)
		{
			*params->rx += params->xo;
			*params->ry += params->yo;
			params->dof++;
		}
	}
}

void	calculatehorizontalray(t_ray_calc_params *params)
{
	params->xo = 0;
	params->yo = 0;
	params->dof = 0;
	inithorizontalray(params);
	processhorizontalray(params);
}

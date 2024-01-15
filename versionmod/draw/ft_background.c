/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_background.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:19:39 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/14 17:37:52 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_sky_ground(t_sky_ground_params *params)
{
	t_square_params	square_params;

	square_params.w = params->w;
	square_params.x = params->backgroundOffsetX;
	square_params.y = params->startHeight;
	square_params.xo = params->w->s_win.width + params->backgroundOffsetX;
	square_params.yo = params->endHeight;
	square_params.color = params->color;
	draw_square_raw(&square_params);
}

void	draw_background(t_structure_main *w)
{
	int					backgroundoffsetx;
	t_sky_ground_params	sky_params;
	t_sky_ground_params	ground_params;

	backgroundoffsetx = BOV;
	sky_params.w = w;
	sky_params.startHeight = 0;
	sky_params.endHeight = w->s_win.height / 2;
	sky_params.color = 0xB2FFFF;
	sky_params.backgroundOffsetX = backgroundoffsetx;
	draw_sky_ground(&sky_params);
	ground_params.w = w;
	ground_params.startHeight = w->s_win.height / 2;
	ground_params.endHeight = w->s_win.height;
	ground_params.color = 0x280000;
	ground_params.backgroundOffsetX = backgroundoffsetx;
	draw_sky_ground(&ground_params);
}

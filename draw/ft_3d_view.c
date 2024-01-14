/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3d_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:35:53 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/14 17:19:42 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_line_params(t_line_params *lineparams, t_ray_params *rayParams)
{
	lineparams->w = rayParams->w;
	lineparams->x0 = (int)rayParams->w->s_player.px;
	lineparams->y0 = (int)rayParams->w->s_player.py;
	lineparams->x1 = (int)rayParams->rx;
	lineparams->y1 = (int)rayParams->ry;
	lineparams->color = rayParams->color;
}

void	init_texture_params(t_texture_params *textureparams,
	t_ray_params *rayParams)
{
	textureparams->w = rayParams->w;
	textureparams->lineOff = rayParams->lineOff;
	textureparams->lineH = rayParams->lineH;
	textureparams->wallDir = rayParams->wallDir;
	textureparams->rx = rayParams->rx + rayParams->backgroundOffsetX;
	textureparams->ry = rayParams->ry;
	textureparams->disT = rayParams->disT;
}

void	drawray(t_ray_params *rayparams)
{
	t_line_params		lineparams;
	t_texture_params	textureparams;

	rayparams->start3DHeight = 0;
	rayparams->max3DHeight = rayparams->w->s_win.height
		+ rayparams->start3DHeight;
	rayparams->lineH = (rayparams->tileSize * rayparams->max3DHeight)
		/ rayparams->disT;
	if (rayparams->lineH > rayparams->max3DHeight)
	{
		rayparams->lineH = rayparams->max3DHeight;
	}
	rayparams->lineOff = ((rayparams->max3DHeight - rayparams->lineH) / 2);
	rayparams->backgroundOffsetX = BOV;
	rayparams->raywidth = rayparams->w->s_win.width / rayparams->numRays;
	textureparams.startX = rayparams->r * rayparams->raywidth
		+ rayparams->backgroundOffsetX;
	textureparams.endX = textureparams.startX + rayparams->raywidth;
	init_line_params(&lineparams, rayparams);
	draw_line(&lineparams);
	init_texture_params(&textureparams, rayparams);
	draw_texture(&textureparams);
}

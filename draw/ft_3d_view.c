/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3d_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:35:53 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/25 14:58:34 by fgras-ca         ###   ########.fr       */
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
	float				olineh;
	int					deca;
	int					color;

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
	olineh = (rayparams->w->s_map.mapS * rayparams->w->s_win.height) / rayparams->disT;
	rayparams->backgroundOffsetX = BOV;
	rayparams->raywidth = rayparams->w->s_win.width / rayparams->numRays;
	textureparams.startX = rayparams->r * rayparams->raywidth
		+ rayparams->backgroundOffsetX;
	textureparams.endX = textureparams.startX + rayparams->raywidth;
	init_texture_params(&textureparams, rayparams);
	init_line_params(&lineparams, rayparams);
	draw_line(&lineparams);
	if (olineh > rayparams->w->s_win.height)
		deca = olineh - rayparams->w->s_win.height;
	else
		deca = 0;
	//draw_black_ground(rayparams);
	if (deca != 0)
		draw_yolo(rayparams, &textureparams, deca);
	else
		draw_texture(&textureparams);
}

void draw_yolo(t_ray_params *rparams, t_texture_params *tparams, int deca)
{
	int		texturewidth;
	int		textureheight;
	int		i;
	int		y;
	int		x;
	float	perspectivefactor;
	int		texturex;
	int		color;
	
	texturewidth = tparams->w->s_img.texture_width;
	textureheight = tparams->w->s_img.texture_height;
	i = 0;
	for (y = rparams->lineOff; y < rparams->lineOff + rparams->lineH; y++) {
		// La variable perspectiveFactor permet de mapper la texture en tenant compte de la perspective
		perspectivefactor = (float)(y - rparams->lineOff) / rparams->lineH;
		int textureY = perspectivefactor * (textureheight );
		if (textureY >= textureheight) {
			textureY = textureheight - 1;
		}

		//for (int x = startX; x < endX; x++) {
			x = tparams->startX;
			switch (tparams->wallDir) {
				case NORTH:
				case SOUTH:
					// Assurez-vous que rx est normalisé correctement pour le mappage de texture
					texturex = (int)(tparams->rx * texturewidth / tparams->w->s_map.mapS) % texturewidth;
					break;
				case WEST:
				case EAST:
					// Assurez-vous que ry est normalisé correctement pour le mappage de texture
					texturex = (int)(tparams->ry * texturewidth /  tparams->w->s_map.mapS) % texturewidth;
					break;
			}
			if (texturex >= texturewidth) {
				texturex = texturewidth - 1;
			}
			//printf("%f %f\n",lineOff, lineOff/lineH);
		
		
			color = get_texture_color(tparams->w, tparams->wallDir, texturex, y);
		
		
		//	BLOCK OK MEH
		//	float ww = ((720+merde)/lineH);
		//	//printf("%d %d %d\n", t ,td, merde);
		//	put_pixel_img(w, x, (int)(iii*ww)-merde/2, color);	
		//	iii++;

			int a = tparams->lineOff - deca / 2;
			int b = tparams->lineH + (deca /2);
			int c = tparams->lineH;
			double step = (b - a)/(double)(c - 1);
			//printf("%d %d %d\n", t ,td, merde);
			put_pixel_img(tparams->w, x, (int)(a + i * step), color);
			i++;
		//}
	}
}

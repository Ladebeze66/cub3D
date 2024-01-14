/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:49:42 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/14 23:34:45 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void drawRays2D(t_structure_main *w)
{
	int					r;
	int					color;
	int					tilesize;
	int					numrays;
	float				ra;
	float				disH;
	float				disV;
	float				disT;
	float				hx;
	float				hy;
	float				vx;
	float				vy;
	float				FOV;
	float 				DR;
	WallDirection		hwalldir;
	WallDirection		vwalldir;
	t_ray_params		rayparams;
	t_ray_calc_params	hrayparams;
	t_ray_calc_params	vrayparams;

	tilesize = w->s_map.mapS;
	numrays = NUMRAY;
	FOV = FOVIEW * (PI / 180);
	DR = FOV / numrays;
	draw_background(w);

	ra = w->s_player.pa - (FOV / 2);
	r = 0;
	while (r++ < numrays)
	{
		ra = fmod(ra + 2 * PI, 2 * PI);

		hrayparams.w = w;
		hrayparams.ra = ra;
		hrayparams.disRay = &disH;
		hrayparams.rx = &hx;
		hrayparams.ry = &hy;
		hrayparams.wallDir = &hwalldir;
		calculatehorizontalray(&hrayparams);
		vrayparams.w = w;
		vrayparams.ra = ra;
		vrayparams.disRay = &disV;
		vrayparams.rx = &vx;
		vrayparams.ry = &vy;
		vrayparams.wallDir = &vwalldir;
		calculateverticalray(&vrayparams);
		if (disH < disV)
		{
			disT = disH;
			color = 0xFF0000;
			rayparams.wallDir = hwalldir;
			rayparams.rx = hx;
			rayparams.ry = hy;
   		}
		else
		{
			disT = disV;
			color = 0x00FF00;
			rayparams.wallDir = vwalldir;
			rayparams.rx = vx;
			rayparams.ry = vy;
		}
		disT = correctFisheye(disT, ra, w->s_player.pa);
		rayparams.w = w;
		rayparams.tileSize = tilesize;
		rayparams.r = r;
		rayparams.disT = disT;
		rayparams.numRays = numrays;
		rayparams.color = color;
		drawray(&rayparams);
		ra += DR;
	}
}

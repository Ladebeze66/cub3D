/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:49:42 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/22 16:15:17 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	correctfisheye(float distance, float ra, float playerAngle)
{
	float	ca;

	ca = playerAngle - ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	return (distance * cos(ca));
}

void	init_base_params(t_base_params *params, t_structure_main *w)
{
	params->tilesize = w->s_map.mapS;
	params->numrays = NUMRAY;
	params->FOV = FOVIEW * (PI / 180);
	params->DR = params->FOV / params->numrays;
	params->ra = w->s_player.pa - (params->FOV / 2);
	printf("init_base_params: Player Position: x = %f, y = %f, Angle = %f\n", w->s_player.px, w->s_player.py, w->s_player.pa);
	draw_background(w);
}

void	calculate_ray(t_base_params *base, t_ray_state *state,
		t_ray_calc *calc, t_ray_params *rayparams)
{
	if (state->disH < state->disV)
	{
		rayparams->disT = state->disH;
		calc->color = 0xFF0000;
		rayparams->wallDir = state->hwalldir;
		rayparams->rx = state->hx;
		rayparams->ry = state->hy;
	}
	else
	{
		rayparams->disT = state->disV;
		calc->color = 0x00FF00;
		rayparams->wallDir = state->vwalldir;
		rayparams->rx = state->vx;
		rayparams->ry = state->vy;
	}
	rayparams->disT = correctfisheye(rayparams->disT,
			base->ra, calc->w->s_player.pa);
	rayparams->w = calc->w;
	rayparams->tileSize = base->tilesize;
	rayparams->r = calc->r;
	rayparams->numRays = base->numrays;
	rayparams->color = calc->color;
	printf("calculate_ray: Ray #%d, Distance = %f, rx = %f, ry = %f, Wall Direction = %d\n", calc->r, rayparams->disT, rayparams->rx, rayparams->ry, rayparams->wallDir);
}

void drawrays2d(t_structure_main *w) {
    t_drawrays2d_params params;

    init_base_params(&params.base_params, w);
    params.ray_calc.w = w;
    params.ray_calc.r = 0;
    while (params.ray_calc.r++ < params.base_params.numrays) {
        params.base_params.ra = fmod(params.base_params.ra + 2 * PI, 2 * PI);

        // Ajout de logs pour les paramètres du rayon
        //printf("drawrays2d BEFORE: Ray #%d, Angle (ra) = %f\n", params.ray_calc.r, params.base_params.ra);

        params.hrayparams = (t_ray_calc_params){w, params.base_params.ra,
            &params.ray_state.disH, &params.ray_state.hx,
            &params.ray_state.hy, &params.ray_state.hwalldir};
        params.vrayparams = (t_ray_calc_params){w, params.base_params.ra,
            &params.ray_state.disV, &params.ray_state.vx,
            &params.ray_state.vy, &params.ray_state.vwalldir};
        calculatehorizontalray(&params.hrayparams);
        calculateverticalray(&params.vrayparams);
        calculate_ray(&params.base_params, &params.ray_state,
            &params.ray_calc, &params.rayparams);
		printf("drawrays2d AFTER : Ray #%d, ra: %f\n", params.ray_calc.r, params.base_params.ra);

        //Plus de logs après les calculs des rayons
		//printf("drawrays2d: Ray #%d, Player Position: x = %f, y = %f, Angle (ra) = %f\n",
        //       params.ray_calc.r, w->s_player.px, w->s_player.py, params.base_params.ra);
        //printf("Horizontal Ray: Distance = %f, x = %f, y = %f\n", params.ray_state.disH, params.ray_state.hx, params.ray_state.hy);
        //printf("Vertical Ray: Distance = %f, x = %f, y = %f\n", params.ray_state.disV, params.ray_state.vx, params.ray_state.vy);
		//printf("Drawray start\n");
        drawray(&params.rayparams);
        params.base_params.ra += params.base_params.DR;
    }
}

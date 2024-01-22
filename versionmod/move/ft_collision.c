/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:09:52 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/22 13:25:35 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void calculate_future_position(t_position_params *params) {
    *(params->future_px) = params->px + params->pdx + params->collisionBuffer;
    *(params->future_py) = params->py + params->pdy + params->collisionBuffer;

    //printf("calculate_future_position: Current px = %d, pdx = %d, collisionBuffer = %d\n", params->px, params->pdx, params->collisionBuffer);
    //printf("calculate_future_position: Current py = %d, pdy = %d, collisionBuffer = %d\n", params->py, params->pdy, params->collisionBuffer);
    //printf("calculate_future_position: Calculated Future Position: x = %d, y = %d\n", *(params->future_px), *(params->future_py));
}

int check_collision(t_structure_main *w, int future_px, int future_py) {
    int future_ipx = future_px / w->s_map.mapS;
    int future_ipy = future_py / w->s_map.mapS;

    //printf("check_collision: Checking Collision at Future Map Index: x = %d, y = %d\n", future_ipx, future_ipy);
    //printf("check_collision: Collision Status: %s\n", w->s_map.map[future_ipy * w->s_map.mapX + future_ipx] == '0' ? "No Collision" : "Collision Detected");

    return (w->s_map.map[future_ipy * w->s_map.mapX + future_ipx] == '0');
}

void calculate_future_position_right_left(t_position_params *params) {
    double angle = params->pa;
    int collision_px;
    int collision_py;

    if (params->direction == 'd')
        angle += M_PI_2;
    else
        angle -= M_PI_2;

    *(params->future_px) = params->px + (int)(cos(angle) * 5);
    *(params->future_py) = params->py + (int)(sin(angle) * 5);
    collision_px = *(params->future_px) + (int)(cos(params->pa) * params->collisionBuffer);
    collision_py = *(params->future_py) + (int)(sin(params->pa) * params->collisionBuffer);
    *(params->future_px) = collision_px;
    *(params->future_py) = collision_py;

    //printf("calculate_future_position_right_left: Current px = %d, py = %d, direction = %c\n", params->px, params->py, params->direction);
    //printf("calculate_future_position_right_left: Calculated Future Position: x = %d, y = %d\n", collision_px, collision_py);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:09:52 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/25 20:43:43 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int can_move_to(t_structure_main *w, double future_x, double future_y) {
    int map_x, map_y;

    // Vérification manuelle de chaque position autour de la future position
    int dx[] = {0, 0, -COLBUF, COLBUF, -COLBUF, COLBUF, -COLBUF, COLBUF};
    int dy[] = {-COLBUF, COLBUF, 0, 0, -COLBUF, -COLBUF, COLBUF, COLBUF};

    for (int i = 0; i < 8; i++) {
        map_x = (int)((future_x + dx[i]) / w->s_map.mapS);
        map_y = (int)((future_y + dy[i]) / w->s_map.mapS);
        char map_position = w->s_map.map[map_y * w->s_map.mapX + map_x];
        if (map_position != '0' && map_position != '3') {
            printf("Collision détectée à x = %d, y = %d\n", map_x, map_y);
            return 0; // Collision détectée, ne peut pas se déplacer
        }
    }

    printf("Pas de collision, peut se déplacer\n");
    return 1; // Pas de collision, peut se déplacer
}

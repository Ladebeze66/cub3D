/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:08:25 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/25 18:33:49 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void move_forward(t_structure_main *w, int key) {
    double future_px;
    double future_py;

    if (key == 119) { // Touche 'w' pour avancer
        future_px = w->s_player.px + cos(w->s_player.pa) * w->s_map.mapS;
        future_py = w->s_player.py + sin(w->s_player.pa) * w->s_map.mapS;

        if (can_move_to(w, future_px, future_py)) {
            w->s_player.px = future_px;
            w->s_player.py = future_py;
        }
    }
}

void move_backward(t_structure_main *w, int key) {
    double future_px;
    double future_py;

    if (key == 115) { // Touche 's' pour reculer
        future_px = w->s_player.px - cos(w->s_player.pa) * w->s_map.mapS;
        future_py = w->s_player.py - sin(w->s_player.pa) * w->s_map.mapS;

        if (can_move_to(w, future_px, future_py)) {
            w->s_player.px = future_px;
            w->s_player.py = future_py;
        }
    }
}

void move_right(t_structure_main *w, int key) {
    double future_px;
    double future_py;

    if (key == 100) { // Touche 'd' pour aller à droite
        future_px = w->s_player.px + cos(w->s_player.pa + (PI/2)) * w->s_map.mapS;
        future_py = w->s_player.py + sin(w->s_player.pa + (PI/2)) * w->s_map.mapS;

        if (can_move_to(w, future_px, future_py)) {
            w->s_player.px = future_px;
            w->s_player.py = future_py;
        }
    }
}

void move_left(t_structure_main *w, int key) {
    double future_px;
    double future_py;

    if (key == 97) { // Touche 'a' pour aller à gauche
        future_px = w->s_player.px + cos(w->s_player.pa - (PI/2)) * w->s_map.mapS;
        future_py = w->s_player.py + sin(w->s_player.pa - (PI/2)) * w->s_map.mapS;

        if (can_move_to(w, future_px, future_py)) {
            w->s_player.px = future_px;
            w->s_player.py = future_py;
        }
    }
}

void	move(int key, t_structure_main *w)
{
	move_forward(w, key);
	move_backward(w, key);
	move_right(w, key);
	move_left(w, key);
}

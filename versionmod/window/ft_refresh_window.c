/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refresh_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:50:24 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/22 15:41:55 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void rescale_sprite(t_structure_main *w, t_state *state) {
    t_rescale_params params;

    params.original_img = w->s_img.roomadslam[state->jkl];
    params.original_width = 112;
    params.original_height = 112;
    params.new_width = w->s_map.mapS;
    params.new_height = w->s_map.mapS;
    params.px = w->s_player.px - w->s_map.mapS / 2; // Ajustez cette ligne si nécessaire
    params.py = w->s_player.py - w->s_map.mapS / 2; // Ajustez cette ligne si nécessaire
    //Sprintf("rescale_sprite: Player sprite position: x = %d, y = %d\n", params.px, params.py);
    rescale_image(&params, w);
}


void	refresh_window(t_structure_main *w, t_state *state)
{
	//printf("refresh_window: Destroying old image\n");
	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	//printf("refresh_window: Creating new image\n");
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.width,
			w->s_win.height);
	printf("refresh_window: Getting data address\n");
	w->s_img.addr = mlx_get_data_addr(w->s_img.buffer,
			&(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	printf("refresh_window: Drawing map\n");
	draw_map(w);
	printf("refresh_window: Drawing rays 2D\n");
	drawrays2d(w);
	//printf("refresh_window: Putting image to window\n");
	mlx_put_image_to_window(w->s_win.mlx, w->s_win.win, w->s_img.buffer, 0, 0);
	//printf("refresh_window: Rescaling sprite\n");
	rescale_sprite(w, state);
	//printf("refresh_window: Window refreshed\n");
}

void	handle_mouse_movement(t_structure_main *w)
{
	int	x;
	int	y;


	mlx_mouse_get_pos(w->s_win.mlx, w->s_win.win, &x, &y);
	if ((x > 0 && x < w->s_win.height) && (y > 0 && y < w->s_win.width))
	{
		if (x != w->s_win.height / 2)
		{
			if (x < w->s_win.height / 2)
				deal_key(65361, w);
			else
				deal_key(65363, w);
		}
	}
	//printf("handle_mouse_movement: Mouse position: x = %d, y = %d\n", x, y);
}

void	r_window(t_structure_main *w, t_state *state)
{
	refresh_window(w, state);
}

void	sleep_mouse(t_global_struct *global_struct)
{
	if (global_struct->state.yui < 10)
	{
		usleep(1000);
		global_struct->state.yui++;
	}
	else
	{
		global_struct->state.yui = 0;
		global_struct->state.jkl++;
		//printf("sleep_mouse: Iteration %d - Updating window and handling mouse movement\n", global_struct->state.jkl);
		r_window(global_struct->w, &global_struct->state);
		handle_mouse_movement(global_struct->w);
	}
	if (global_struct->state.jkl == 10)
	{
		//printf("sleep_mouse: Resetting state.jkl to -1\n");
        global_struct->state.jkl = -1;
	}
}

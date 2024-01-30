/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:06:24 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 16:07:27 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_texture_images(t_structure_main *w)
{
	int	i;

	i = 0;
	while (++i <= 10)
	{
		if (w->s_img.roomadslam[i])
			mlx_destroy_image(w->s_win.mlx, w->s_img.roomadslam[i]);
	}
}

static void	free_textures(t_texture *t)
{
	if (t->north)
		free(t->north);
	if (t->south)
		free(t->south);
	if (t->west)
		free(t->west);
	if (t->east)
		free(t->east);
}

static void	destroy_images(t_structure_main *w)
{
	if (w->s_win.mlx)
	{
		mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
		mlx_destroy_image(w->s_win.mlx, w->s_img.img_player);
		mlx_destroy_image(w->s_win.mlx, w->s_img.img_wall);
		mlx_destroy_image(w->s_win.mlx, w->s_img.pedro_wall);
		mlx_destroy_image(w->s_win.mlx, w->s_img.north_texture);
		mlx_destroy_image(w->s_win.mlx, w->s_img.south_texture);
		mlx_destroy_image(w->s_win.mlx, w->s_img.west_texture);
		mlx_destroy_image(w->s_win.mlx, w->s_img.east_texture);
		mlx_destroy_image(w->s_win.mlx, w->s_img.door_texture);
		free_texture_images(w);
	}
}

void	exit_error(t_structure_main *w)
{
	if (w->s_win.mlx)
	{
		mlx_destroy_window(w->s_win.mlx, w->s_win.win);
		destroy_images(w);
		mlx_destroy_display(w->s_win.mlx);
		free(w->s_win.mlx);
	}
	if (w->s_map.map && (w->error != 1))
		free(w->s_map.map);
	if (w->t)
	{
		free_textures(w->t);
		free(w->t);
	}
	exit(1);
}

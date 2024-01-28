/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:39:11 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/25 20:34:32 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_texture_line(t_texture_params *params, float y, int textureY)
{
	int	x;
	int	texturewidth;
	int	texturex;
	int	color;

	texturewidth = params->w->s_img.texture_width;
	x = params->startX;
	while (x < params->endX)
	{
		if (params->wallDir == NORTH || params->wallDir == SOUTH)
			texturex = (int)(params->rx * texturewidth
					/ params->w->s_map.mapS) % texturewidth;
		else
			texturex = (int)(params->ry * texturewidth
					/ params->w->s_map.mapS) % texturewidth;
		if (texturex >= texturewidth)
			texturex = texturewidth - 1;
		color = get_texture_color(params->w,
				params->wallDir, texturex, textureY);
		put_pixel_img(params->w, x, y, color);
		x++;
	}
}

void	draw_texture(t_texture_params *params)
{
	int		textureheight;
	float	y;
	float	perspectivefactor;
	int		texturey;

	textureheight = params->w->s_img.texture_height;
	y = params->lineOff;
	while (y < params->lineOff + params->lineH)
	{
		perspectivefactor = (y - params->lineOff) / params->lineH;
		texturey = perspectivefactor * textureheight;
		if (texturey >= textureheight)
			texturey = textureheight - 1;
		draw_texture_line(params, y, texturey);
		y++;
	}
}

void	*get_selected_texture(t_structure_main *w, WallDirection wallDir)
{
	void *texture = NULL;
	if (w->current_wall_type == '2') {
        return w->s_img.door_texture; // Texture pour porte fermée
    } /*else if (w->current_wall_type == '3') {
        return w->s_img.open_door_texture; // Texture pour porte ouverte
    }*/
	else if (wallDir == NORTH)
		return (w->s_img.north_texture);
	else if (wallDir == SOUTH)
		return (w->s_img.south_texture);
	else if (wallDir == WEST)
		return (w->s_img.west_texture);
	else if (wallDir == EAST)
		return (w->s_img.east_texture);
	else
	{
		fprintf(stderr, "Invalid wall direction.\n");
		exit_error(w);
		return (NULL);
	}
	 if (texture == NULL)
		fprintf(stderr, "get_selected_texture: selected texture is NULL\n");
	else
		printf("get_selected_texture: selected texture = %p\n", texture);
}

t_texture_data	get_texture_data(void *texture)
{
	t_texture_data	texture_data;

	texture_data.data = mlx_get_data_addr(texture, &texture_data.bpp,
			&texture_data.size_line, &texture_data.endian);
	return (texture_data);
}

int	get_texture_color(t_structure_main *w, WallDirection wallDir,
		int textureX, int textureY)
{
	void			*selected_texture;
	t_texture_data	texture_data;
	int				pixel_pos;

	selected_texture = get_selected_texture(w, wallDir);
	if (selected_texture == NULL)
	{
		fprintf(stderr, "No texture selected for color retrieval\n");
		return (0);
	}

	texture_data = get_texture_data(selected_texture);
	pixel_pos = (textureX + textureY * w->s_img.texture_width)
		* (texture_data.bpp / 8);
	return (*(int *)(texture_data.data + pixel_pos));
}

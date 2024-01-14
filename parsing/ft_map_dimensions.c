/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_dimensions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:17:19 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/11 22:19:14 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_max_dimensions(t_map_params *params)
{
	(*(params->height))++;
	if (*(params->currentWidth) > *(params->maxWidth))
	{
		*(params->maxWidth) = *(params->currentWidth);
	}
	*(params->currentWidth) = 0;
	*(params->isNewLine) = 1;
}

void	process_character(t_map_params *params, int *i)
{
	if (params->buffer[*i] == '\n')
	{
		update_max_dimensions(params);
	}
	else if (params->buffer[*i] != '\r')
	{
		(*(params->currentWidth))++;
		*(params->isNewLine) = 0;
	}
	(*i)++;
}

void	get_map_dimensions(t_map_params *params)
{
	int	i;
	int	currentwidth;
	int	isnewline;

	i = 0;
	currentwidth = 0;
	isnewline = 1;
	*(params->maxWidth) = 0;
	*(params->height) = 0;
	params->currentWidth = &currentwidth;
	params->isNewLine = &isnewline;
	while (i < params->length)
		process_character(params, &i);
	if (!*(params->isNewLine))
		update_max_dimensions(params);
	printf("Map dimensions: maxWidth=%d, height=%d\n",
		*(params->maxWidth), *(params->height));
}

void	fill_map_space(t_structure_map *map_info, int maxWidth, int height)
{
	int	i;
	int	totalsize;

	totalsize = maxWidth * height;
	i = 0;
	while (i < totalsize)
	{
		map_info->map[i] = ' ';
		i++;
	}
}

void	copy_map_data(t_map_params *params)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	while (i < params->length)
	{
		if (params->buffer[i] == '\n')
		{
			y++;
			x = 0;
		}
		else if (params->buffer[i] != '\r' && x < *params->maxWidth)
		{
			params->map_info->map[y * *params->maxWidth + x]
				= params->buffer[i];
			x++;
		}
		i++;
	}
}

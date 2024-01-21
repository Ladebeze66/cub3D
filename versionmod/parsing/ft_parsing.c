/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:46 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/21 13:21:28 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_map_scale(t_structure_map *map_info)
{
	int	maps_x;
	int	maps_y;

	map_info->wd.width = WIDTH;
	map_info->wd.height = HEIGHT;
		if (map_info->mapX == 0 || map_info->mapY == 0)
		{
			fprintf(stderr, "Erreur: mapX ou mapY est zéro.\n");
		map_info->mapS = 0;
		return ;
	}
	maps_x = map_info->wd.width / (map_info->mapX * 4);
	maps_y = map_info->wd.height / (map_info->mapY * 2);
	if (maps_x < maps_y)
		 map_info->mapS = maps_x;
	else
		 map_info->mapS = maps_y;
}

bool	init_map_info(t_structure_map *map_info, int maxWidth, int height)
{
	map_info->mapX = maxWidth;
	map_info->mapY = height;
	map_info->map = malloc(maxWidth * height);
	if (!map_info->map)
	{
		perror("Failed to allocate memory for map");
		return (false);
	}
	fill_map_space(map_info, maxWidth, height);
	return (true);
}

bool	copy_map_data_and_check(t_map_params *params)
{
	copy_map_data(params);
	if (!is_map_closed(params->map_info->map,
			*params->maxWidth, *params->height))
	{
		printf("Map is not closed!\n");
		free(params->map_info->map);
		return (false);
	}
	return (true);
}

bool	find_player_position_and_direction(const char *map_content, int length, t_structure_map *map_info)
{
	int		i;
	int		line_number;
	int		column_number;
	bool	found_player;
	char	current_char;

	i = 0;
	line_number = 0;
	column_number = 0;
	found_player = false;
	calculate_map_scale(map_info);
	while (i < length)
	{
		current_char = map_content[i];
		if (current_char == 'N' || current_char == 'S' || current_char == 'E' || current_char == 'W')
		{
			if (found_player)
			{
				printf("Multiple player start positions found. Invalid map.\n");
				return (false);
			}
			found_player = true;
			map_info->player_x = column_number * map_info->mapS + map_info->mapS / 2;
			map_info->player_y = line_number * map_info->mapS + map_info->mapS / 2;
			map_info->player_direction = current_char;
		}
		if (current_char == '\n')
		{
			line_number++;
			column_number = 0;
		}
		else
			column_number++;
		i++;
	}
	if (!found_player)
	{
		printf("Player start position not found. Invalid map.\n");
		return (false);
	}
	return (true);
}

bool	parse_map(const char *buffer, int length, t_structure_map *map_info)
{
	int				maxwidth;
	int				height;
	t_map_params	map_params;

	maxwidth = 0;
	height = 0;
	map_params.map_info = map_info;
	map_params.buffer = buffer;
	map_params.length = length;
	map_params.maxWidth = &maxwidth;
	map_params.height = &height;
	map_params.currentWidth = NULL;
	map_params.isNewLine = NULL;
	get_map_dimensions(&map_params);
	if (maxwidth <= 0 || height <= 0)
	{
		printf("Invalid map dimensions: maxWidth=%d, height=%d\n",
			maxwidth, height);
		return (false);
	}
	if (!init_map_info(map_info, maxwidth, height))
		return (false);
	if (!find_player_position_and_direction(buffer, length, map_info))
		return (false);
	return (copy_map_data_and_check(&map_params));
}

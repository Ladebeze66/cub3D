/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:46 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/15 22:22:00 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

bool	read_and_verify_map(const char *filename, char **buffer, int *length)
{
	*length = 0;
	*buffer = read_map(filename, length);
	if (!(*buffer))
	{
		printf("Failed to read the map file.\n");
		return (false);
	}
	return (true);
}

bool	process_map(const char *buffer, int length, t_structure_map *map_info)
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
	{
		return (false);
	}
	return (copy_map_data_and_check(&map_params));
}

bool parse_map(const char *map_content, int length, t_structure_map *map_info)
{
    t_map_params map_params;
    int max_width = 0;
    int height = 0;
	printf("Received map content (length = %d): \n%s\n", length, map_content);
    // Initialisation de la structure de paramètres pour le traitement de la carte
    map_params.map_info = map_info;
    map_params.buffer = map_content;
    map_params.length = length;

map_params.maxWidth = &max_width;
map_params.height = &height;
map_params.currentWidth = NULL;
map_params.isNewLine = NULL;
// Obtenir les dimensions de la carte
get_map_dimensions(&map_params);
if (max_width <= 0 || height <= 0)
{
    printf("Invalid map dimensions: maxWidth=%d, height=%d\n", max_width, height);
    return (false);
}

// Initialiser les informations de la carte
if (!init_map_info(map_info, max_width, height))
{
    return (false);
}

// Copier les données de la carte et vérifier si la carte est fermée
return copy_map_data_and_check(&map_params);
}

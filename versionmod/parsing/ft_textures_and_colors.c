/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures_and_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:19:13 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/16 17:31:12 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	parse_texture_line(const char *line, t_texture *textures)
{
	char	direction[3];
	char	path[MAX_LINE_LENGTH];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != ' ' && line[i] != '\0' && i < 2)
		direction[i++] = line[i];
	direction[i] = '\0';
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i] != ' ' && line[i] != '\0' && j < MAX_LINE_LENGTH - 1)
		path[j++] = line[i++];
	path[j] = '\0';
	if (ft_strcmp(direction, "NO") == 0)
		textures->north = ft_strdup(path);
	else if (ft_strcmp(direction, "SO") == 0)
		textures->south = ft_strdup(path);
	else if (ft_strcmp(direction, "WE") == 0)
		textures->west = ft_strdup(path);
	else if (ft_strcmp(direction, "EA") == 0)
		textures->east = ft_strdup(path);
		printf("parse texture %s\n", textures->north);
	return (true);
}

bool	handle_map(int fd, char **map_buffer, int *map_length)
{
	char	line[MAX_LINE_LENGTH];
	int		bytes_read;

	*map_length = 0;
	bytes_read = read(fd, line, MAX_LINE_LENGTH - 1);
	while (bytes_read > 0)
	{
		printf("bytes read %d\n", bytes_read);
		line[bytes_read] = '\0';
		*map_buffer = realloc(*map_buffer, *map_length + bytes_read + 1);
		if (!*map_buffer)
		{
			perror("Error reallocating memory for map buffer");
			return (false);
		}
		ft_memcpy(*map_buffer + *map_length, line, bytes_read);
		*map_length += bytes_read;
		(*map_buffer)[*map_length] = '\0';
		bytes_read = read(fd, line, MAX_LINE_LENGTH - 1);
	}
	return (true);
}

bool	parse_color_line(const char *line, unsigned int *color)
{
	int	r;
	int	g;
	int	b;
	int	i;

	r = 0;
	g = 0;
	b = 0;
	i = 0;
	while (line[i] != ',' && line[i] != '\0')
		r = r * 10 + (line[i++] - '0');
	i++;
	while (line[i] != ',' && line[i] != '\0')
		g = g * 10 + (line[i++] - '0');
	i++;
	while (line[i] != ' ' && line[i] != '\0')
		b = b * 10 + (line[i++] - '0');
	*color = (r << 16) | (g << 8) | b;
	return (true);
}

bool	is_valid_texture(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}

bool	handle_textures(int fd, t_texture *textures)
{
	char	line[MAX_LINE_LENGTH];
	int		bytes_read;
	int		texture_count;
	char	ch;
	int		i;

	texture_count = 0;
	i = 0;
	while (texture_count < 4 && read(fd, &ch, 1) > 0)
	{
		if (ch != '\n')
			line[i++] = ch;
		else
		{
			line[i] = '\0';
			if (is_valid_texture(line))
			{
				parse_texture_line(line, textures);
				texture_count++;
				printf("Texture reconnue et traitée: '%s'\n", line);
			}
			i = 0;
		}
	}
	return (texture_count == 4);
}

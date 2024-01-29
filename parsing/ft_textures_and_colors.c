/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures_and_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:19:13 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 20:17:57 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	handle_map(int fd, char **map_buffer, int *map_length)
{
	char	*line;
	size_t	len;
	ssize_t	read;
	bool	start_copying;
	FILE *stream;

	stream = fdopen(fd, "r");
	line = NULL;
	len = 0;
	start_copying = false;
	*map_length = 0;
	*map_buffer = NULL;
	if (!stream)
	{
		perror("Error converting file descriptor to FILE *");
		return (false);
	}
	while ((read = getline(&line, &len, stream)) != -1)
	{
		if (!start_copying && (ft_strchr(line, '1') || ft_strchr(line, '0')))
			start_copying = true;
		if (start_copying)
		{
			*map_buffer = realloc(*map_buffer, *map_length + read + 1);
			if (!*map_buffer)
			{
				perror("Error reallocating memory for map buffer");
				free(line);
				fclose(stream);
				return (false);
			}
			ft_memcpy(*map_buffer + *map_length, line, read);
			*map_length += read;
			(*map_buffer)[*map_length] = '\0';
		}
	}
	free(line);
	fclose(stream);
	return (*map_buffer != NULL);
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

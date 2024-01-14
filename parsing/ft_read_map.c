/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:28:43 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/11 20:02:52 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*read_map(const char *filename, int *length)
{
	char	*buffer;
	FILE	*file;

	file = fopen(filename, "r");
	if (!file)
	{
		perror("Error opening file");
		return (NULL);
	}
	fseek(file, 0, SEEK_END);
	*length = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = malloc(*length + 1);
	if (!buffer)
	{
		perror("Error allocating memory for map");
		fclose(file);
		return (NULL);
	}
	fread(buffer, 1, *length, file);
	buffer[*length] = '\0';
	fclose(file);
	return (buffer);
}

static int	check_line(char *map, int maxWidth, int y, int linelength)
{
	int		x;
	char	c;

	x = 1;
	while (x < linelength - 1)
	{
		c = map[y * maxWidth + x];
		if (c == ' ' && (map[y * maxWidth + (x - 1)] != '1'
				|| map[y * maxWidth + (x + 1)] != '1'
				|| (y > 0 && map[(y - 1) * maxWidth + x] != '1')
				|| (y < maxWidth - 1 && map[(y + 1) * maxWidth + x] != '1')))
			return (0);
		x++;
	}
	return (1);
}

static int	check_row(char *map, int maxWidth, int y)
{
	int		x;
	int		linelength;

	x = 0;
	linelength = 0;
	while (x < maxWidth && map[y * maxWidth + x] != ' ')
	{
		linelength++;
		x++;
	}
	return (check_line(map, maxWidth, y, linelength));
}

int	check_interior(char *map, int maxWidth, int height)
{
	int		y;

	y = 0;
	while (y < height)
	{
		if (!check_row(map, maxWidth, y))
			return (0);
		y++;
	}
	return (1);
}

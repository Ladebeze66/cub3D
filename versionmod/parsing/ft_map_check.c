/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:49:45 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/11 20:02:42 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_map_closed(char *map, int maxWidth, int height)
{
	if (!check_borders(map, maxWidth, height))
		return (0);
	if (!check_interior(map, maxWidth, height))
		return (0);
	return (1);
}

int	check_line_border(char *line, int lineLength, int y)
{
	if (lineLength == 0)
		return (1);
	if (line[0] != '1')
		return (0);
	if (line[lineLength - 1] != '1')
		return (0);
	return (1);
}

int	check_horizontal_borders(char *map, int maxWidth, int height)
{
	int	x;

	x = 0;
	while (x < maxWidth)
	{
		if (map[x] != '1' && map[x] != ' ')
		{
			printf("Border issue detected at top edge at (%d,0)\n", x);
			return (0);
		}
		if (map[(height - 1) * maxWidth + x] != '1'
			&& map[(height - 1) * maxWidth + x] != ' ')
			return (0);
		x++;
	}
	return (1);
}

int	check_vertical_borders(char *map, int maxWidth, int height)
{
	int	x;
	int	columnheight;

	x = 0;
	while (x < maxWidth)
	{
		columnheight = 0;
		while (columnheight < height && map[columnheight * maxWidth + x] != ' ')
		{
			columnheight++;
		}
		if (columnheight > 0)
		{
			if (map[x] != '1')
			{
				printf("Border issue detected at top of column at (%d,0)\n", x);
				return (0);
			}
			if (map[(columnheight - 1) * maxWidth + x] != '1')
				return (0);
		}
		x++;
	}
	return (1);
}

int	check_borders(char *map, int maxWidth, int height)
{
	int	y;
	int	linelength;
	int	x;

	y = 0;
	while (y < height)
	{
		linelength = 0;
		x = 0;
		while (x < maxWidth && map[y * maxWidth + x] != ' ')
		{
			linelength++;
			x++;
		}
		if (!check_line_border(&map[y * maxWidth], linelength, y))
		{
			return (0);
		}
		y++;
	}
	if (!check_horizontal_borders(map, maxWidth, height))
	{
		return (0);
	}
	return (check_vertical_borders(map, maxWidth, height));
}

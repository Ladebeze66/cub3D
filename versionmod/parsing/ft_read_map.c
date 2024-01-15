/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:28:43 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/15 21:48:46 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char *read_map(const char *filename, int *length)
{
    int file;
    char buffer[1024]; // Taille de tampon temporaire pour la lecture
    int total_length = 0;
    int bytes_read;
    char *map_content;

    // Ouvrir le fichier pour la première lecture
    file = open(filename, O_RDONLY);
    if (file < 0)
    {
        perror("Error opening file");
        return (NULL);
    }

    // Lire le fichier pour déterminer sa taille
    while ((bytes_read = read(file, buffer, sizeof(buffer))) > 0)
        total_length += bytes_read;

    // Fermer le fichier après la première lecture
    close(file);

    // Allouer de la mémoire pour le contenu de la carte
    map_content = (char *)malloc(total_length + 1);
    if (!map_content)
    {
        perror("Error allocating memory for map");
        return (NULL);
    }

    // Rouvrir le fichier pour la deuxième lecture
    file = open(filename, O_RDONLY);
    if (file < 0)
    {
        perror("Error opening file");
        free(map_content);
        return (NULL);
    }

    // Lire le contenu du fichier dans le tampon
    *length = 0;
    while ((bytes_read = read(file, map_content + *length, total_length - *length)) > 0)
        *length += bytes_read;

    // Ajouter le caractère de fin de chaîne
    map_content[*length] = '\0';

    // Fermer le fichier
    close(file);

    return map_content;
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

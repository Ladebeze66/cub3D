/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:49:45 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/28 22:20:51 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_space_surrounded_by_walls(char *map, int maxWidth, int height, int x, int y) {
    // Vérifie si les cellules adjacentes à un espace sont toutes des murs ('1')
    return (x > 0 && map[y * maxWidth + (x - 1)] == '1') &&
           (x < maxWidth - 1 && map[y * maxWidth + (x + 1)] == '1') &&
           (y > 0 && map[(y - 1) * maxWidth + x] == '1') &&
           (y < height - 1 && map[(y + 1) * maxWidth + x] == '1');
}

int flood_fill_and_check(char *map, char *visitedMap, int maxWidth, int height, int x, int y, char replacement) {
    if (x < 0 || x >= maxWidth || y < 0 || y >= height) {
        return 0; // Ouverture détectée
    }

    if (visitedMap[y * maxWidth + x] == 1 || map[y * maxWidth + x] == '1') {
        return 1; // Mur ou déjà visité
    }

    if (map[y * maxWidth + x] == ' ' && !is_space_surrounded_by_walls(map, maxWidth, height, x, y)) {
        return 0; // Espace non entouré correctement par des murs, ouverture intérieure détectée
    }

    visitedMap[y * maxWidth + x] = 1; // Marquer la cellule comme visitée
    map[y * maxWidth + x] = replacement; // Marquer la cellule dans la carte principale

    // Appliquer récursivement à toutes les directions
    return flood_fill_and_check(map, visitedMap, maxWidth, height, x + 1, y, replacement) &&
           flood_fill_and_check(map, visitedMap, maxWidth, height, x - 1, y, replacement) &&
           flood_fill_and_check(map, visitedMap, maxWidth, height, x, y + 1, replacement) &&
           flood_fill_and_check(map, visitedMap, maxWidth, height, x, y - 1, replacement);
}

int is_surrounded_by_walls(char *map, int maxWidth, int height, int x, int y) {
    // Vérifier les limites
    if (x <= 0 || x >= maxWidth - 1 || y <= 0 || y >= height - 1) return 1;

    // Vérifier les cellules adjacentes
    if (map[(y - 1) * maxWidth + x] == '1' && map[(y + 1) * maxWidth + x] == '1' &&
        map[y * maxWidth + (x - 1)] == '1' && map[y * maxWidth + (x + 1)] == '1') {
        return 1;
    }

    return 0;
}

int is_map_closed(char *map, int maxWidth, int height) {

	char *copy_map = malloc(maxWidth * height);
	if (copy_map)
	{
		ft_memcpy(copy_map, map, maxWidth * height);
	}
    char *visitedMap = calloc(maxWidth * height, sizeof(char));
    if (!visitedMap) {
        printf("Erreur d'allocation mémoire pour visitedMap.\n");
        return 0;
    }

    int startX = -1, startY = -1;
    printf("Début de la vérification de fermeture de la carte.\n");

    /* Affichage de la carte avant flood_fill
    printf("Carte avant flood_fill:\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < maxWidth; x++) {
            printf("%c", map[y * maxWidth + x]);
        }
        printf("\n");
    }*/

    // Trouver un point de départ valide
    for (int y = 0; y < height && startX == -1; y++) {
        for (int x = 0; x < maxWidth && startX == -1; x++) {
            if ((map[y * maxWidth + x] == '0' || map[y * maxWidth + x] == '2') && !is_surrounded_by_walls(map, maxWidth, height, x, y)) {
                startX = x;
                startY = y;
                printf("Point de départ trouvé pour flood_fill à (%d, %d)\n", startX, startY);
                break;
            }
        }
    }

    if (startX == -1) {
        printf("Aucun point de départ valide trouvé.\n");
        free(visitedMap);
        return 1; // Si aucun point de départ n'est trouvé, la carte est considérée comme fermée
    }

    int is_closed = flood_fill_and_check(copy_map, visitedMap, maxWidth, height, startX, startY, '3');


    /*printf("Carte après flood_fill:\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < maxWidth; x++) {
            printf("%c", visitedMap[y * maxWidth + x] ? '3' : map[y * maxWidth + x]);
        }
        printf("\n");
    }*/


    free(visitedMap);
	free(copy_map);
    return is_closed;
}

/*int	is_map_closed(char *map, int maxWidth, int height)
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

int check_vertical_borders(char *map, int maxWidth, int height)
{
    int x, y, first_wall_found, last_wall_found;

    for (x = 0; x < maxWidth; x++)
    {
        first_wall_found = 0;
        last_wall_found = height - 1;

        // Trouver le premier '1' dans la colonne
        for (y = 0; y < height; y++)
        {
            if (map[y * maxWidth + x] == '1')
            {
                first_wall_found = 1;
                break;
            }
        }

        // Trouver le dernier '1' dans la colonne
        for (y = height - 1; y >= 0; y--)
        {
            if (map[y * maxWidth + x] == '1')
            {
                last_wall_found = y;
                break;
            }
        }

        // Si aucun mur trouvé, la colonne est incorrecte
        if (!first_wall_found || last_wall_found == height - 1)
        {
            printf("Border issue detected in column %d\\n", x);
            return 0;
        }

        // Vérifier que la colonne est correctement fermée
        for (y = first_wall_found; y <= last_wall_found; y++)
        {
            if (map[y * maxWidth + x] != '1' && map[y * maxWidth + x] != ' ')
            {
                printf("Border issue detected in column %d at position %d\\n", x, y);
                return 0;
            }
        }
    }

    return 1;
}

int check_horizontal_borders(char *map, int maxWidth, int height)
{
    int x, y;

    for (y = 0; y < height; y += height - 1) // Vérifier seulement la première et la dernière ligne
    {
        int first_wall_found = 0;
        int last_wall_found = 0;

        // Trouver le premier '1' dans la ligne
        for (x = 0; x < maxWidth; x++)
        {
            if (map[y * maxWidth + x] == '1')
            {
                first_wall_found = 1;
                break;
            }
        }

        // Trouver le dernier '1' dans la ligne
        for (x = maxWidth - 1; x >= 0; x--)
        {
            if (map[y * maxWidth + x] == '1')
            {
                last_wall_found = 1;
                break;
            }
        }

        // Si aucun mur '1' n'est trouvé au début ou à la fin de la ligne
        if (!first_wall_found || !last_wall_found)
        {
            printf("Border issue detected in line %d\\n", y);
            return 0;
        }
    }

    return 1;
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
}*/

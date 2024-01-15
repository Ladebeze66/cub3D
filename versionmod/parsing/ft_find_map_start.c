/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_map_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:04:23 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/15 22:38:37 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool parse_texture_line(const char *line, t_texture *textures)
{
    char direction[3];
    char path[MAX_LINE_LENGTH];
    int i = 0;
    int j = 0;

    // Extraction de la direction (NO, SO, etc.)
    while (line[i] != ' ' && line[i] != '\0' && i < 2)
    {
        direction[i] = line[i];
        i++;
    }
    direction[i] = '\0';

    // Saut des espaces
    while (line[i] == ' ' && line[i] != '\0')
        i++;

    // Extraction du chemin
    while (line[i] != ' ' && line[i] != '\0' && j < MAX_LINE_LENGTH - 1)
    {
        path[j] = line[i];
        i++;
        j++;
    }
    path[j] = '\0';

    // Assignation à la structure
    if (strcmp(direction, "NO") == 0)
        textures->north = strdup(path);
    else if (strcmp(direction, "SO") == 0)
        textures->south = strdup(path);
    else if (strcmp(direction, "WE") == 0)
        textures->west = strdup(path);
    else if (strcmp(direction, "EA") == 0)
        textures->east = strdup(path);

    return (true);
}

bool parse_color_line(const char *line, unsigned int *color)
{
    int r = 0, g = 0, b = 0;
    int i = 0;

    // Extraction des composantes de couleur
    while (line[i] != ',' && line[i] != '\0')
    {
        r = r * 10 + (line[i] - '0');
        i++;
    }
    i++; // Passer la virgule

    while (line[i] != ',' && line[i] != '\0')
    {
        g = g * 10 + (line[i] - '0');
        i++;
    }
    i++; // Passer la virgule

    while (line[i] != ' ' && line[i] != '\0')
    {
        b = b * 10 + (line[i] - '0');
        i++;
    }

    *color = (r << 16) | (g << 8) | b;
    return (true);
}

bool load_cub_file(const char *filename, t_texture *textures, t_structure_map *map_info)
{
    int fd;
    char line[MAX_LINE_LENGTH];
    char *map_buffer = NULL;
    int map_length = 0;
    int bytes_read;
    bool is_map_started = false;

    // Ouvrir le fichier
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (false);
    }

    while ((bytes_read = read(fd, line, MAX_LINE_LENGTH - 1)) > 0)
    {
        line[bytes_read] = '\0';  // Assurer que la ligne est terminée par un caractère nul
		printf("Ligne lue : %s\n", line); // Log pour vérifier chaque ligne lue
        if (!is_map_started)
        {
            // Chercher si la ligne actuelle est le début de la carte
            if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
            {
                is_map_started = true;
            }
            else
            {
                // Continuer à analyser les textures et couleurs
                if (line[0] == 'F' || line[0] == 'C')
                    parse_color_line(line + 1, line[0] == 'F' ? &textures->floor_color : &textures->ceil_color);
                else
                    parse_texture_line(line, textures);

                continue;  // Passer au tour suivant de la boucle
            }
        }

        // Si la carte a commencé, ajouter la ligne à map_buffer
        if (is_map_started)
        {
            map_buffer = realloc(map_buffer, map_length + bytes_read + 1);
            if (!map_buffer)
            {
                perror("Error reallocating memory for map buffer");
                close(fd);
                return (false);
            }
            memcpy(map_buffer + map_length, line, bytes_read);
            map_length += bytes_read;
            map_buffer[map_length] = '\0'; // Assurer que la chaîne est terminée
			printf("Carte stockée :\n%s\n", map_buffer); // Log pour voir le contenu final de la carte
    		printf("Longueur de la carte stockée : %d\n", map_length); // Log pour voir la longueur de la carte stockée
        }
    }

    close(fd);

    // Traiter la carte stockée en mémoire
    if (map_buffer)
    {
		printf("Calling parse_map with map content...\n");
        bool result = parse_map(map_buffer, map_length, map_info);
		printf("Result of parse_map: %s\n", result ? "Success" : "Failure");
        free(map_buffer);  // Libérer la mémoire allouée pour map_buffer
        return result;
    }
    else
    {
        printf("No map data found in file.\n");
        return (false);
    }
}

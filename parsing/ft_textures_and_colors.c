/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures_and_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:19:13 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/28 18:06:00 by fgras-ca         ###   ########.fr       */
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
	return (true);
}

bool handle_map(int fd, char **map_buffer, int *map_length) {
    FILE *stream = fdopen(fd, "r");
    if (!stream) {
        perror("Error converting file descriptor to FILE *");
        return false;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    bool start_copying = false;

    *map_length = 0;
    *map_buffer = NULL;

    while ((read = getline(&line, &len, stream)) != -1) {
        // Vérifier si la ligne contient '1' ou '0'
        if (!start_copying && (ft_strchr(line, '1') || ft_strchr(line, '0'))) {
            start_copying = true;
        }

        // Commencer la copie si on a trouvé une ligne contenant '1' ou '0'
        if (start_copying) {
            *map_buffer = realloc(*map_buffer, *map_length + read + 1);
            if (!*map_buffer) {
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



bool parse_number_from_str(const char **str, int *number)
{
	*number = 0;
	while (**str >= '0' && **str <= '9')
	{
		*number = *number * 10 + (**str - '0');
		(*str)++;
	}
	if (**str != ',' && **str != ' ' && **str != '\0')
	{
		return (false);
	}
	return (true);
}

bool	parse_color_line(const char *line, unsigned int *color)
{
	int r;
	int	g;
	int	b;
	const char *ptr;

	r = 0;
	g = 0;
	b = 0;
	ptr = line;
	while (*ptr == ' ') ptr++;
	if (!parse_number_from_str(&ptr, &r) || *ptr++ != ',')
		return (false);
	while (*ptr == ' ') ptr++;
	if (!parse_number_from_str(&ptr, &g) || *ptr++ != ',')
		return (false);
	while (*ptr == ' ') ptr++;
	if (!parse_number_from_str(&ptr, &b))
		return (false);
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

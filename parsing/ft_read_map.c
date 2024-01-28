/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:28:43 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/28 22:36:40 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*static int check_line(char *map, int maxWidth, int height, int y)
{
    int x;
    char c;

    for (x = 0; x < maxWidth; x++)
    {
        c = map[y * maxWidth + x];
        if (c == ' ' && ((x > 0 && map[y * maxWidth + (x - 1)] != '1') ||
                         (x < maxWidth - 1 && map[y * maxWidth + (x + 1)] != '1') ||
                         (y > 0 && map[(y - 1) * maxWidth + x] != '1') ||
                         (y < height - 1 && map[(y + 1) * maxWidth + x] != '1')))
            return (0);
    }
    return (1);
}


static int check_row(char *map, int maxWidth, int height, int y)
{
    return check_line(map, maxWidth, height, y);
}

int check_interior(char *map, int maxWidth, int height)
{
    int y;

    for (y = 0; y < height; y++)
    {
        if (!check_row(map, maxWidth, height, y))
            return (0);
    }
    return (1);
}*/

void load_sprite_frames(t_sprite *sprite, void *mlx_ptr) {
    sprite->frames[0] = mlx_xpm_file_to_image(mlx_ptr, "sprite/pnj/pnj01.xpm", &sprite->width, &sprite->height);
    if (sprite->frames[0] == NULL) {
        printf("Erreur de chargement de sprite/pnj/pnj01.xpm\n");
    } else {
        printf("Sprite pnj01.xpm chargé avec succès. Dimensions: %d x %d\n", sprite->width, sprite->height);
    }
	sprite->frames[1] = mlx_xpm_file_to_image(mlx_ptr, "sprite/pnj/pnj02.xpm", &sprite->width, &sprite->height);
    if (sprite->frames[1] == NULL) {
        printf("Erreur de chargement de sprite/pnj/pnj01.xpm\n");
    } else {
        printf("Sprite pnj02.xpm chargé avec succès. Dimensions: %d x %d\n", sprite->width, sprite->height);
    }
	sprite->frames[2] = mlx_xpm_file_to_image(mlx_ptr, "sprite/pnj/pnj03.xpm", &sprite->width, &sprite->height);
    if (sprite->frames[2] == NULL) {
        printf("Erreur de chargement de sprite/pnj/pnj01.xpm\n");
    } else {
        printf("Sprite pnj03.xpm chargé avec succès. Dimensions: %d x %d\n", sprite->width, sprite->height);
    }
}

void update_sprite_frame(t_sprite *sprite) {
    static int counter = 0;
    counter = (counter + 1) % 60;
    if (counter == 0) {
        sprite->current_frame = (sprite->current_frame + 1) % 3;
        printf("Frame du sprite mise à jour : %d\n", sprite->current_frame);
    }
}

void draw_sprite(t_sprite *sprite, void *mlx_ptr, void *win_ptr, int win_width, int win_height) {
    if (sprite->frames[sprite->current_frame] != NULL) {
        float posX = 170;
        float posY = 30;

        // Logs pour débogage
        printf("Dessin du sprite (frame %d)...\n", sprite->current_frame);
        printf("Dimensions du sprite : largeur = %d, hauteur = %d\n", sprite->width, sprite->height);
        printf("Coordonnées de dessin du sprite : X = %f, Y = %f\n", posX, posY);

        // Dessiner le sprite
        mlx_put_image_to_window(mlx_ptr, win_ptr, sprite->frames[sprite->current_frame], posX, posY);
        printf("Sprite dessiné aux coordonnées: %f, %f\n", posX, posY);
    } else {
        // Log en cas d'erreur
        printf("Erreur lors du dessin du sprite (frame %d)\n", sprite->current_frame);
    }
}

#include "cub3d.h"

void	put_pixel_img(t_structure_main *w,int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < w->s_win.height && y < w->s_win.width)
	{
		dst = w->s_img.addr + (y * w->s_img.line_len + x * (w->s_img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void draw_square_raw(t_structure_main *w, int x, int y, int xo, int yo, int color)
{
	int i;
	int j;

	int size_x = abs(xo - x);
	int size_y = abs(yo - y);

	for (i = 0; i < size_y; i++)
	{
		for (j = 0; j < size_x; j++)
		{
			put_pixel_img(w, (x) + j, (y) + i, color);
		}
	}
}

void draw_square(t_structure_main *w, int x, int y, int color) {
    int xo = x * w->s_map.mapS;  // Coordonnée X en pixels
    int yo = y * w->s_map.mapS;  // Coordonnée Y en pixels
    int size = w->s_map.mapS;    // Taille du carré

    // Dessiner le carré en utilisant la taille et les coordonnées calculées
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            put_pixel_img(w, xo + j, yo + i, color);
        }
    }
}



void draw_line(t_structure_main *w, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx, sy;

	if (x0 < x1)
		sx = 1;
	else
		sx = -1;

	if (y0 < y1)
		sy = 1;
	else
		sy = -1;

	int err = dx - dy;

	while (1)
	{
		put_pixel_img(w, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

float dist(float ax, float ay, float bx, float by)
{
	return ( sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)));
}

void rescale_image(void *mlx, void *win, void *original_img, int original_width, int original_height, int new_width, int new_height, int px, int py, t_structure_main *w)
{
	// Créez une nouvelle image avec la taille souhaitée
	void *rescaled_img = mlx_new_image(w->s_win.mlx, new_width, new_height);
	if (!rescaled_img)
	{
		// Gestion de l'erreur
		perror("Erreur lors de la création de la nouvelle image");
		return;
	}

	// Obtenez les adresses des données des images
	char *original_data = mlx_get_data_addr(original_img, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	char *rescaled_data = mlx_get_data_addr(rescaled_img, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));

	// Facteurs de redimensionnement
	float x_ratio = (float)original_width / new_width;
	float y_ratio = (float)original_height / new_height;

	// Parcourez chaque pixel de la nouvelle image
	for (int y = 0; y < new_height; ++y)
	{
		for (int x = 0; x < new_width; ++x)
		{
			// Calculez les coordonnées correspondantes dans l'image d'origine
			int original_x = x_ratio * x;
			int original_y = y_ratio * y;

			// Copiez la couleur du pixel de l'image d'origine vers la nouvelle image
			// Vous devrez ajuster les offsets en fonction de votre format de pixel
			// et de la profondeur des couleurs
			rescaled_data[y * new_width * 4 + x * 4 + 0] = original_data[original_y * original_width * 4 + original_x * 4 + 0];
			rescaled_data[y * new_width * 4 + x * 4 + 1] = original_data[original_y * original_width * 4 + original_x * 4 + 1];
			rescaled_data[y * new_width * 4 + x * 4 + 2] = original_data[original_y * original_width * 4 + original_x * 4 + 2];
			rescaled_data[y * new_width * 4 + x * 4 + 3] = original_data[original_y * original_width * 4 + original_x * 4 + 3];
		}
	}

	// Affichez la nouvelle image
	mlx_put_image_to_window(w->s_win.mlx, w->s_win.win, rescaled_img, px,py);

	// Libérez la mémoire de la nouvelle image (si vous n'en avez plus besoin)
	mlx_destroy_image(w->s_win.mlx, rescaled_img);
}

float correctFisheye(float distance, float ra, float playerAngle) {
    float ca = playerAngle - ra;
    if (ca < 0) ca += 2 * PI;
    if (ca > 2 * PI) ca -= 2 * PI;
    return distance * cos(ca);
}

void calculateVerticalRay(t_structure_main *w, float ra, float *disV, float *vx, float *vy, WallDirection *wallDir) {
    int dof = 0, mx, my, mp;
    float rx, ry, xo, yo;
    int tileSize = w->s_map.mapS;
    *disV = 1000000;  // Distance initialement grande
	*wallDir = NONE;
    float nTan = -tan(ra);

    if (ra > P2 && ra < P3) {
        rx = (((int)w->s_player.px / tileSize) * tileSize) - 0.0001;
        ry = (w->s_player.px - rx) * nTan + w->s_player.py;
        xo = -tileSize;
        yo = -xo * nTan;
    } else if (ra < P2 || ra > P3) {
        rx = (((int)w->s_player.px / tileSize) * tileSize) + tileSize;
        ry = (w->s_player.px - rx) * nTan + w->s_player.py;
        xo = tileSize;
        yo = -xo * nTan;
    } else {  // Rayon directement en haut ou en bas
        rx = w->s_player.px;
        ry = w->s_player.py;
        dof = 25;
    }

    while (dof < 25) {
        mx = (int)(rx) / tileSize;
        my = (int)(ry) / tileSize;
        mp = my * w->s_map.mapX + mx;
        if (mp >= 0 && mp < w->s_map.mapX * w->s_map.mapY && w->s_map.map[mp] == '1') {
            dof = 25;
            *vx = rx;
            *vy = ry;
            *disV = dist(w->s_player.px, w->s_player.py, rx, ry);
			  if (ra > P2 && ra < P3) {
                *wallDir = WEST;
            } else {
                *wallDir = EAST;
            }
        } else {
            rx += xo;
            ry += yo;
            dof += 1;
        }
    }
}


void calculateHorizontalRay(t_structure_main *w, float ra, float *disH, float *hx, float *hy, WallDirection *wallDir) {
    int dof = 0, mx, my, mp;
    float rx, ry, xo, yo;
    int tileSize = w->s_map.mapS;
    *disH = 1000000;  // Distance initialement grande
	*wallDir = NONE;

    float aTan = -1 / tan(ra);

    if (ra > PI) {
        ry = (((int)w->s_player.py / tileSize) * tileSize) - 0.0001;
        rx = (w->s_player.py - ry) * aTan + w->s_player.px;
        yo = -tileSize;
        xo = -yo * aTan;
    } else if (ra < PI) {
        ry = (((int)w->s_player.py / tileSize) * tileSize) + tileSize;
        rx = (w->s_player.py - ry) * aTan + w->s_player.px;
        yo = tileSize;
        xo = -yo * aTan;
    } else {  // Rayon directement à gauche ou à droite
        rx = w->s_player.px;
        ry = w->s_player.py;
        dof = 25;
    }

    while (dof < 25) {
        mx = (int)(rx) / tileSize;
        my = (int)(ry) / tileSize;
        mp = my * w->s_map.mapX + mx;
        if (mp >= 0 && mp < w->s_map.mapX * w->s_map.mapY && w->s_map.map[mp] == '1') {
            dof = 25;
            *hx = rx;
            *hy = ry;
            *disH = dist(w->s_player.px, w->s_player.py, rx, ry);
			 if (ra > PI) {
                *wallDir = NORTH;
            } else {
                *wallDir = SOUTH;
            }
        } else {
            rx += xo;
            ry += yo;
            dof += 1;
        }
    }
}

void load_wall_textures(t_structure_main *w) {
    // Initialiser la largeur et la hauteur des textures
    int width = 0;
    int height = 0;

    // Charger la texture Nord et vérifier si elle est chargée correctement
    w->s_img.north_texture = mlx_xpm_file_to_image(w->s_win.mlx, "textures/NO.xpm", &width, &height);
    if (!w->s_img.north_texture) {
        fprintf(stderr, "Failed to load North texture.\n");
        exit_error(w);  // Remplacez par votre propre gestion des erreurs
    }

    // Charger la texture Sud et vérifier si elle est chargée correctement
    w->s_img.south_texture = mlx_xpm_file_to_image(w->s_win.mlx, "textures/SO.xpm", &width, &height);
    if (!w->s_img.south_texture) {
        fprintf(stderr, "Failed to load South texture.\n");
        exit_error(w);
    }

    // Charger la texture Ouest et vérifier si elle est chargée correctement
    w->s_img.west_texture = mlx_xpm_file_to_image(w->s_win.mlx, "textures/WE.xpm", &width, &height);
    if (!w->s_img.west_texture) {
        fprintf(stderr, "Failed to load West texture.\n");
        exit_error(w);
    }

    // Charger la texture Est et vérifier si elle est chargée correctement
    w->s_img.east_texture = mlx_xpm_file_to_image(w->s_win.mlx, "textures/EA.xpm", &width, &height);
    if (!w->s_img.east_texture) {
        fprintf(stderr, "Failed to load East texture.\n");
        exit_error(w);
    }

    // Stocker la largeur et la hauteur pour une utilisation ultérieure
    w->s_img.texture_width = width;
    w->s_img.texture_height = height;

    printf("All wall textures loaded successfully.\n");
}

void exit_error(t_structure_main *w) {
    // Libérer les ressources, fermer la fenêtre, etc.
    // ...
    exit(1);
}

void draw_background(t_structure_main *w) {
    int start3DHeight = w->s_win.height / 2; // Le début de la vue 3D à la moitié de la fenêtre
    int end3DHeight = w->s_win.height; // La fin de la vue 3D est le bas de la fenêtre
    int half3DHeight = (end3DHeight - start3DHeight) / 2; // La moitié de l'espace 3D

    // Définir la hauteur où le ciel se termine et le sol commence
    int skyEndHeight = start3DHeight + half3DHeight;

    // Dessiner le ciel
    draw_square_raw(w, 0, start3DHeight, w->s_win.width, skyEndHeight, 0xB2FFFF);

    // Dessiner le sol avec texture
    if (w->s_img.ground) {
        for (int y = skyEndHeight; y < end3DHeight; y += w->s_img.ground_height) {
            for (int x = 0; x < w->s_win.width; x += w->s_img.ground_width) {
                mlx_put_image_to_window(w->s_win.mlx, w->s_win.win, w->s_img.ground, x, y);
            }
        }
    } else {
        // Dessiner le sol uni si la texture n'est pas chargée
        draw_square_raw(w, 0, skyEndHeight, w->s_win.width, end3DHeight, 0x280000);
    }
}


void drawRay(t_structure_main *w, int r, float rx, float ry, float disT, WallDirection wallDir, int numRays) {
    int tileSize = w->s_map.mapS;
    int start3DHeight = w->s_win.height / 2; // Début de la vue 3D à la moitié de la fenêtre
    int max3DHeight = w->s_win.height / 2; // Hauteur maximale pour la vue 3D

    float lineH = (tileSize * max3DHeight) / disT;
    if (lineH > max3DHeight) lineH = max3DHeight; // Limiter la hauteur

    float lineOff = start3DHeight + ((max3DHeight - lineH) / 2); // Décaler le début de la ligne pour centrer verticalement

    int rayWidth = w->s_win.width / numRays; // Largeur de chaque rayon
    int startX = r * rayWidth;
    int endX = (r + 1) * rayWidth;

    void *selected_texture = NULL;
    switch (wallDir) {
        case NORTH:
            selected_texture = w->s_img.north_texture;
            break;
        case SOUTH:
            selected_texture = w->s_img.south_texture;
            break;
        case WEST:
            selected_texture = w->s_img.west_texture;
            break;
        case EAST:
            selected_texture = w->s_img.east_texture;
            break;
    }

 if (selected_texture) {
    int texture_offset = (int)(rx * w->s_img.texture_width) % w->s_img.texture_width; // Exemple d'offset, ajustez selon les besoins
    char *texture_data = mlx_get_data_addr(selected_texture, &w->s_img.bpp, &w->s_img.line_len, &w->s_img.endian);

    for (int y = lineOff; y < lineOff + lineH; y++) {
        // Calculez la position Y dans la texture. Ajustez selon les besoins.
        int texture_y = ((y - lineOff) * w->s_img.texture_height) / lineH;

        for (int x = startX; x < endX; x++) {
            // Calculez la position X dans la texture. Ajustez selon les besoins.
            int texture_x = texture_offset;

            // Obtenez la couleur du pixel de la texture
            int color = *(int *)(texture_data + (texture_x + texture_y * w->s_img.texture_width) * (w->s_img.bpp / 8));

            // Dessinez le pixel sur l'écran
            put_pixel_img(w, x, y, color);
        }
    }
} else {
    // Aucune texture sélectionnée, dessinez une couleur unie
    draw_square_raw(w, startX, lineOff, endX, lineOff + lineH, 0x00FF00); // Utilisez la couleur par défaut
}
}




void drawRays2D(t_structure_main *w) {
    int r, color;
    float ra, disH, disV, disT, hx, hy, vx, vy;
	WallDirection hWallDir, vWallDir;
    int tileSize = w->s_map.mapS;
	int numRays = 240;
	float FOV = PI / 3;
	float DR = FOV / numRays;

    draw_background(w); // Fonction pour dessiner le fond

    ra = w->s_player.pa - (FOV / 2);
    for (r = 0; r <= numRays; r++) {
        if (ra < 0) ra += 2 * PI;
        if (ra > 2 * PI) ra -= 2 * PI;

        calculateHorizontalRay(w, ra, &disH, &hx, &hy, &hWallDir);
        calculateVerticalRay(w, ra, &disV, &vx, &vy, &vWallDir);

        disT = (disH < disV) ? disH : disV;  // Choisir la distance la plus courte
		WallDirection wallDir = (disH < disV) ? hWallDir : vWallDir;
        color = (disH < disV) ? 0xFF0000 : 0x00FF00;  // Rouge pour horizontal, Vert pour vertical
		      switch(wallDir) {
            case NORTH:
                // Utiliser la texture du mur Nord
                break;
            case SOUTH:
                // Utiliser la texture du mur Sud
                break;
            case WEST:
                // Utiliser la texture du mur Ouest
                break;
            case EAST:
                // Utiliser la texture du mur Est
                break;
            default:
                color = 0x00FF00; // Couleur par défaut (ou texture)
                break;
        }
        disT = correctFisheye(disT, ra, w->s_player.pa);  // Corriger l'effet fisheye

        drawRay(w, r, (disH < disV) ? hx : vx, (disH < disV) ? hy : vy, disT, color, numRays);
        ra += DR;
    }
}

void draw_map(t_structure_main *w) {
    // Log pour vérifier la taille de la carte
    printf("Drawing map of size: %d x %d\n", w->s_map.mapX, w->s_map.mapY);


    int x;
    int y;
    int color;

    for (y = 0; y < w->s_map.mapY; y++) {
        for (x = 0; x < w->s_map.mapX; x++) {
            if (w->s_map.map[y * w->s_map.mapX + x] == '1')
                color = 0xFFFFFF;  // Couleur pour les murs
            else if (w->s_map.map[y * w->s_map.mapX + x] == ' ')
                color = 0x000000;  // Couleur pour l'espace vide
            else
                color = 0x666666;  // Couleur par défaut

            draw_square(w, x, y, color);
        }
		printf("x: %d, y: %d, char: %c\n", x, y, w->s_map.map[y * w->s_map.mapX + x]);
    }
}



int jkl = -1;
int yui = 0;

void test2(t_structure_main *w) {
    mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
    w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.height, w->s_win.width);
    w->s_img.addr = mlx_get_data_addr(w->s_img.buffer, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
    draw_map(w);
    drawRays2D(w);
    mlx_put_image_to_window(w->s_win.mlx, w->s_win.win, w->s_img.buffer, 0, 0);

    int new_sprite_width = w->s_map.mapS;
    int new_sprite_height = w->s_map.mapS;
    int sprite_x = w->s_player.px - new_sprite_width / 2;
    int sprite_y = w->s_player.py - new_sprite_height / 2;

    // Log des valeurs pour le débogage
    printf("Sprite (x, y): (%d, %d), Size (w, h): (%d, %d), MapS: %d\n",
           sprite_x, sprite_y, new_sprite_width, new_sprite_height, w->s_map.mapS);

    // Redimensionner et dessiner le sprite du personnage
    rescale_image(w->s_win.mlx, w->s_win.win, w->s_img.roomadslam[jkl],
                  112, 112, new_sprite_width, new_sprite_height, sprite_x, sprite_y, w);
}


void test(t_structure_main *w)
{
	int	x;
	int y;

	//////////gettimeofday(&(w->start_time), NULL);
	if (yui < 10)
	{
		usleep(1000);
		yui++;
	}
	else
	{
		yui = 0;
		jkl++;
		test2(w);
		//mlx_mouse_move(w->s_win.mlx, w->s_win.win, w->s_win.height/2, w->s_win.width/2);
		mlx_mouse_get_pos(w->s_win.mlx, w->s_win.win, &x, &y);
		if ((x > 0 && x < w->s_win.height) && (y > 0 && y < w->s_win.width))
			if (x != w->s_win.height/2)
			{
				if (x < w->s_win.height/2)
					deal_key(65361,w);
				else
					deal_key(65363,w);
			}
	}
	if (jkl == 10)
		jkl = -1;
}

void	init_windows(t_structure_main *w)
{
	int temp;
	w->s_win.height = 1018;
	w->s_win.width = 1024;
	w->s_win.mlx = mlx_init();
	w->s_win.win = mlx_new_window(w->s_win.mlx, w->s_win.height, w->s_win.width, "WF99");
	w->s_player.px = 250;
	w->s_player.py = 200;
	w->s_player.pa = 0.1;
	w->s_player.pdx = cos(w->s_player.pa) * 5;
	w->s_player.pdy = sin(w->s_player.pa) * 5;
	load_wall_textures(w);

	w->s_img.img_player = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/player.xpm", &temp,&temp);
	w->s_img.img_wall = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/wall.xpm", &temp,&temp);
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.height, w->s_win.width);
	// Initialiser le compteur de FPS
	gettimeofday(&(w->start_time), NULL);
	w->end_time = w->start_time;
	w->frame_count = 0;

    int mapS_x = w->s_win.width / (w->s_map.mapX * 2);
    int mapS_y = w->s_win.height / w->s_map.mapY;
    w->s_map.mapS = (mapS_x < mapS_y) ? mapS_x : mapS_y;


	w->s_img.roomadslam[0] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_02_delay-0.1s.xpm", &temp,&temp);
	w->s_img.roomadslam[1] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_03_delay-0.1s.xpm", &temp,&temp);
	w->s_img.roomadslam[2] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_04_delay-0.1s.xpm", &temp,&temp);
	w->s_img.roomadslam[3] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_05_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[4] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_06_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[5] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_07_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[6] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_08_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[7] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_09_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[8] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_10_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[9] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_11_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[10] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_12_delay-0.05s.xpm", &temp,&temp);

	w->s_img.pedro_wall = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/pedrop/frame_061_delay-0.03s.xpm", &temp,&temp);
	//if (!w->s_img.pedro_wall)
	//	printf("nop\n");

}

#include "cub3d.h"

int main(int argc, char **argv) {
    t_structure_main w;

    // Vérifier si un nom de fichier a été fourni
    if (argc < 2) {
        printf("Usage: %s <path to map file>\n", argv[0]);
        return 1;
    }

    // Parser la carte
    parse_map(argv[1], &w.s_map);
	   if (!parse_map(argv[1], &w.s_map)) {
        printf("Failed to load the map or map is not closed. Exiting...\n");
        return 1;  // Quitter avec un code d'erreur
    }

    // Vérifier si la carte a été chargée correctement
    if (w.s_map.map == NULL) {
        printf("Failed to load the map.\n");
        return 1;
    }

    // Initialiser la fenêtre et d'autres composants
    init_windows(&w);

    // Configurer les hooks et entrer dans la boucle principale
    mlx_loop_hook(w.s_win.mlx, (void *)test, &w);
    mlx_hook(w.s_win.win, 2, 1L<<0, deal_key, &w);
    mlx_hook(w.s_win.win,  17, 0, (void *)kill_prog, &w);
    mlx_loop(w.s_win.mlx);

    // Libérer la carte une fois que vous avez terminé
    if (w.s_map.map) {
        free(w.s_map.map);
    }

    return 0;
}

#include "cub3d.h"

int *kill_prog(t_structure_main *w) {
    mlx_destroy_window(w->s_win.mlx, w->s_win.win);
    mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
    mlx_destroy_image(w->s_win.mlx, w->s_img.img_player);
    mlx_destroy_image(w->s_win.mlx, w->s_img.img_wall);
    mlx_destroy_image(w->s_win.mlx, w->s_img.pedro_wall);

    // Libérer les images de roomadslam
    int i = -1;
    while (++i <= 10)
        mlx_destroy_image(w->s_win.mlx, w->s_img.roomadslam[i]);

    // Libérer la carte si elle a été allouée
    if (w->s_map.map) {
        free(w->s_map.map);
        w->s_map.map = NULL; // Sécurité supplémentaire après la libération
    }

    mlx_destroy_display(w->s_win.mlx);
    free(w->s_win.mlx);
    exit(0);
    return (0);
}

void move(int key, t_structure_main *w) {
    int xo = 0;
    if (w->s_player.pdx < 0) { xo = -w->s_map.mapS / 2; } else { xo = w->s_map.mapS / 2; }
    int yo = 0;
    if (w->s_player.pdy < 0) { yo = -w->s_map.mapS / 2; } else { yo = w->s_map.mapS / 2; }

    // Convertir la position du joueur en coordonnées de grille
    int ipx = w->s_player.px / w->s_map.mapS;
    int ipy = w->s_player.py / w->s_map.mapS;

    // Calculer les positions potentielles après le mouvement
    int ipx_add_xo = (w->s_player.px + xo) / w->s_map.mapS;
    int ipy_add_yo = (w->s_player.py + yo) / w->s_map.mapS;

    int ipx_sub_xo = (w->s_player.px - xo) / w->s_map.mapS;
    int ipy_sub_yo = (w->s_player.py - yo) / w->s_map.mapS;

    int collisionBuffer = 2; // Marge de collision pour éviter de coller aux murs

    // Déplacement vers l'avant
   if (key == 119) {
    int future_py = (int)(w->s_player.py + w->s_player.pdy + collisionBuffer); // Calculez la position future en y avec la marge
    int future_px = (int)(w->s_player.px + w->s_player.pdx + collisionBuffer); // Calculez la position future en x
    int future_ipy = future_py / w->s_map.mapS; // Convertissez en coordonnées de grille
    int future_ipx = future_px / w->s_map.mapS; // Convertissez en coordonnées de grille

    if (w->s_map.map[future_ipy * w->s_map.mapX + future_ipx] == '0') {
        w->s_player.px += w->s_player.pdx;
        w->s_player.py += w->s_player.pdy;
    }
    }
 // Déplacement vers la droite
else if (key == 100) {
    int future_px = w->s_player.px + (int)(cos(w->s_player.pa + M_PI_2) * 5);
    int future_py = w->s_player.py + (int)(sin(w->s_player.pa + M_PI_2) * 5);
    int collision_px = future_px + (int)(cos(w->s_player.pa) * collisionBuffer);
    int collision_py = future_py + (int)(sin(w->s_player.pa) * collisionBuffer);
    int future_ipx = collision_px / w->s_map.mapS;
    int future_ipy = collision_py / w->s_map.mapS;

    if (w->s_map.map[future_ipy * w->s_map.mapX + future_ipx] == '0') {
        w->s_player.px = future_px;
        w->s_player.py = future_py;
    }
}

    // Déplacement vers l'arrière (s)
    // Déplacement vers l'arrière
	else if (key == 115) {
    int future_px = w->s_player.px - (int)(w->s_player.pdx * collisionBuffer);
    int future_py = w->s_player.py - (int)(w->s_player.pdy * collisionBuffer);
    int future_ipx = future_px / w->s_map.mapS;
    int future_ipy = future_py / w->s_map.mapS;

    if (w->s_map.map[future_ipy * w->s_map.mapX + future_ipx] == '0') {
        w->s_player.px -= w->s_player.pdx;
        w->s_player.py -= w->s_player.pdy;
    }
}
// Déplacement vers la gauche
else if (key == 97) {
    int future_px = w->s_player.px + (int)(cos(w->s_player.pa - M_PI_2) * 5);
    int future_py = w->s_player.py + (int)(sin(w->s_player.pa - M_PI_2) * 5);
    int collision_px = future_px + (int)(cos(w->s_player.pa) * collisionBuffer);
    int collision_py = future_py + (int)(sin(w->s_player.pa) * collisionBuffer);
    int future_ipx = collision_px / w->s_map.mapS;
    int future_ipy = collision_py / w->s_map.mapS;

    if (w->s_map.map[future_ipy * w->s_map.mapX + future_ipx] == '0') {
        w->s_player.px = future_px;
        w->s_player.py = future_py;
    }
}

}



int	deal_key(int key, t_structure_main *w)
{
	//printf("key pressed = %d\n", key);
	if (key == 65307)
		kill_prog(w);
	else if (key == 65361)
	{
		w->s_player.pa -= 16*((PI/3)/1280);
		if (w->s_player.pa < 0)
			w->s_player.pa += 2 * PI;
		w->s_player.pdx = cos(w->s_player.pa) * 5;
		w->s_player.pdy = sin(w->s_player.pa) * 5;
	}
	else if (key == 65363)
	{
		w->s_player.pa += 16*((PI/3)/1280);
		if (w->s_player.pa > 2 * PI)
			w->s_player.pa -= 2 * PI;
		w->s_player.pdx = cos(w->s_player.pa) * 5;
		w->s_player.pdy = sin(w->s_player.pa) * 5;
	}
	else if (key == 65362)
		;
	else if (key == 65364)
		;
	else if (key == 119 || key == 100 || key == 115 || key == 97) // w, d, s, a
		move(key,w);
	else if (key == 114)
		;
	else if (key == 102)
		;
	else
		return (key);
	return (key);
}

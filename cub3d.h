/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:56:52 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/16 16:50:38 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <assert.h>
# include "include/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

# define PI 3.14159265359
# define P2 PI/2
# define P3 3*PI/2
# define COLBUF 2
# define NUMRAY 1280
# define FOVIEW 60
# define DISRAY 1000000
# define DOF 120
# define WIDTH 1780
# define HEIGHT 720
# define BOV 500
# define MAX_LINE_LENGTH 100000
typedef enum {
	NORTH,
	SOUTH,
	WEST,
	EAST,
	NONE  // Utilisé lorsqu'aucun mur n'est touché
} WallDirection;

typedef struct s_img
{
	int		height;
	int		width;
	int		ground_width;
	void	*i;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_struture_map
{
	char	*map;
	char	*buff;
	char	**temp_list;
	int		i;
	int		j;
	int		temp;
	int		mapX;
	int		mapY;
	int		mapS;
}	t_structure_map;

typedef struct s_struture_player
{
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
}	t_structure_player;

typedef struct s_struture_img
{
	void	*img_player;
	void	*img_wall;
	void	*buffer;
	char	*addr;
	int		bpp;
	int		endian;
	int		ground_height;
	int		ground_width;
	void	*ground;
	int		line_len;
	int		bpp_bis;
	int		endian_bis;
	int		line_len_bis;
	void	*test[27];
	void	*roomadslam[10];
	void	*tgsway[20];
	void	*pedro_wall;
	void	*north_texture;
	void	*south_texture;
	void	*west_texture;
	void	*east_texture;
	int		texture_width;
	int		texture_height;
}	t_structure_img;

typedef struct s_struture_windows
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_structure_windows;

typedef struct s_texture
{
    char			*north;
    char			*south;
    char			*west;
    char			*east;
    unsigned int	floor_color;
    unsigned int	ceil_color;
}   t_texture;
typedef struct s_structure_main
{
	int					fd;
	struct timeval		start_time;
	struct timeval		end_time;
	int					frame_count;
	t_structure_windows	s_win;
	t_structure_img		s_img;
	t_structure_map		s_map;
	t_structure_player	s_player;
	t_texture			*t;
}	t_structure_main;

typedef struct s_res_params {
	char	*original_data;
	void	*rescaled_img;
	char	*rescaled_data;
	float	x_ratio;
	float	y_ratio;
	int		original_x;
	int		original_y;
	int		pixel_pos_rescaled;
	int		pixel_pos_original;
} t_res_params;

typedef struct s_rescale_params {
	void			*original_img;
	int				original_width;
	int				original_height;
	int				new_width;
	int				new_height;
	int				px;
	int				py;
	t_res_params	*res;
} t_rescale_params;

typedef struct s_position_params {
	int		*future_px;
	int		*future_py;
	int		pdx;
	int		pdy;
	int		collisionBuffer;
	int		px;
	int		py;
	double	pa;
	char	direction;
} t_position_params;


typedef struct s_map_params {
	t_structure_map	*map_info;
	const char		*buffer;
	int				length;
	int				*maxWidth;
	int				*height;
	int				*currentWidth;
	int				*isNewLine;
} t_map_params;

typedef struct s_square_params {
	t_structure_main	*w;
	int					x;
	int					y;
	int					xo;
	int					yo;
	int					color;
} t_square_params;

typedef struct s_sky_ground_params {
	t_structure_main	*w;
	int					startHeight;
	int					endHeight;
	int					color;
	int					backgroundOffsetX;
} t_sky_ground_params;

typedef struct s_line_params {
	t_structure_main	*w;
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	int					color;
} t_line_params;

typedef struct s_line_deltas {
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	t_line_params	*params;
} t_line_deltas;

typedef struct s_ray_params {
	t_structure_main	*w;
	int					r;
	int					tileSize;
	float				rx;
	float				ry;
	float				disT;
	WallDirection		wallDir;
	int					numRays;
	int					color;
	int					start3DHeight;
	int					max3DHeight;
	float				lineH;
	float				lineOff;
	int					backgroundOffsetX;
	int					raywidth;
} t_ray_params;

typedef struct s_texture_params {
	t_structure_main	*w;
	int					startX;
	int					endX;
	float				lineOff;
	float				lineH;
	WallDirection		wallDir;
	float				rx;
	float				ry;
	float				disT;
} t_texture_params;

typedef struct s_ray_calc_params {
	t_structure_main	*w;
	float				ra;
	float				*disRay;
	float				*rx;
	float				*ry;
	WallDirection		*wallDir;
	float				xo;
	float				yo;
	int					dof;
} t_ray_calc_params;

typedef struct s_texture_data
{
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture_data;

typedef struct s_init_params {
	t_structure_main	*w;
	int					tilesize;
	int					numrays;
	float				FOV;
	float				DR;
} t_init_params;

typedef struct s_ray_properties {
	float			disH;
	float			disV;
	WallDirection	hwalldir;
	WallDirection	vwalldir;
	float			hx;
	float			hy;
	float			vx;
	float			vy;
} t_ray_properties;

typedef struct {
	int		tilesize;
	int		numrays;
	float	FOV;
	float	DR;
	float	ra;
} t_base_params;

typedef struct {
	float			disH;
	float			disV;
	float			disT;
	float			hx;
	float			hy;
	float			vx;
	float			vy;
	WallDirection	hwalldir;
	WallDirection	vwalldir;
} t_ray_state;

typedef struct {
	t_structure_main	*w;
	int					r;
	int					color;
} t_ray_calc;

typedef struct {
	t_base_params		base_params;
	t_ray_state			ray_state;
	t_ray_calc			ray_calc;
	t_ray_params		rayparams;
	t_ray_calc_params	hrayparams;
	t_ray_calc_params	vrayparams;
} t_drawrays2d_params;

typedef struct {
    int	jkl;
    int	yui;
} t_state;

typedef struct {
    t_structure_main	*w;
    t_state				state;
} t_global_struct;

//ft_utils_split.c 5 / 5
char	**ft_split(char const *s, char c);
//ft_utils_gnl.c 4 / 5
char	*get_next_line(int fd);
/*ft_key.c 3/5*/
int		*kill_prog(t_structure_main *w);
void	move(int key, t_structure_main *w);
int		deal_key(int key, t_structure_main *w);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *left_str, char *buff);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
/*collision*/
void	calculate_future_position(t_position_params *params);
int		check_collision(t_structure_main *w, int future_px, int future_py);
void	calculate_future_position_right_left(t_position_params *params);
//ft_utils_convert.c 1/5
char	*ft_itoa(int nb);
/*parsing*/
int		is_map_closed(char* map, int width, int height);
bool	parse_map(const char *map_content, int length, t_structure_map *map_info);
int		check_borders(char *map, int maxWidth, int height);
int		check_interior(char *map, int maxWidth, int height);
void	exit_error(t_structure_main *w);
void	update_max_dimensions(t_map_params *params);
void	process_character(t_map_params *params, int *i);
void	get_map_dimensions(t_map_params *params);
void	fill_map_space(t_structure_map *map_info, int maxWidth, int height);
void	copy_map_data(t_map_params *params);
bool	load_cub_file(const char *filename, t_texture *textures, t_structure_map *map_info);
bool	parse_texture_line(const char *line, t_texture *textures);
bool	handle_map(int fd, char **map_buffer, int *map_length);
bool	parse_color_line(const char *line, unsigned int *color);
bool	is_valid_texture(const char *line);
bool	handle_textures(int fd, t_texture *textures);
/*textures*/
void	load_wall_textures(t_structure_main *w);
void	draw_texture(t_texture_params *tex_params);
int		get_texture_color(t_structure_main *w, WallDirection wallDir, int textureX, int textureY);
/*3D view*/
void	drawray(t_ray_params *ray_params);
void	draw_background(t_structure_main *w);
float	correctFisheye(float distance, float ra, float playerAngle);
//2D map
void	rescale_image(t_rescale_params *params, t_structure_main *w);
void	draw_square(t_structure_main *w, int x, int y, int color);
void	draw_map(t_structure_main *w);
void	put_pixel_img(t_structure_main *w, int x, int y, int color);
void	draw_square_raw(t_square_params *params);
void	draw_line(t_line_params *params);
void	drawrays2d(t_structure_main *w);
//Ray
void	calculateverticalray(t_ray_calc_params *params);
void	handle_ra_vertical(t_ray_calc_params *params, float nTan, int tileSize);
void	calculatehorizontalray(t_ray_calc_params *params);
void	handle_ra_not_equal_pi(t_ray_calc_params *params, float atan, int tilesize);
float	dist(float ax, float ay, float bx, float by);
//window
void	init_windows(t_structure_main *w);
void	init_player(t_structure_main *w);
void	init_mlx_and_window(t_structure_main *w);
void	sleep_mouse(t_global_struct *global_struct);

#endif

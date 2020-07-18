/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:36:57 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/18 21:06:31 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <math.h>
# include <X11/X.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# define FOV 60
# define PI 3.1415926535f
# define TWO_PI 6.2831853071f
# define KEY_A 97
# define KEY_D 100
# define KEY_S 115
# define KEY_W 119
# define KEY_Q 113
# define KEY_ESC 65307
# define KEY_AR_L 65361
# define KEY_AR_R 65363
# define WINDOW_TITLE "cub3d"
# define MINIMAP_SCALE 0.3f
# define WALK_SPEED 1.0f
# define TURN_SPEED 1.0f
# define TRUE 1
# define FALSE 0
# define TEXTURES 5

enum	e_texture
{
	EAST,
	WEST,
	SOUTH,
	NORTH,
	SPRITE
};

typedef struct	s_bitmap_file_header
{
	unsigned int	bf_size;
	unsigned short	bf_reverved1;
	unsigned short	bf_reserved2;
	unsigned int	bf_off_bits;
}				t_bitmap_file_header;

typedef struct	s_bitmap_info_header
{
	unsigned int	bi_size;
	int				bi_width;
	int				bi_height;
	unsigned short	bi_planes;
	unsigned short	bi_bit_count;
	unsigned int	bi_compression;
	unsigned int	bi_size_image;
	int				bi_x_pels_per_meter;
	int				bi_y_pels_per_meter;
	unsigned int	bi_clr_used;
	unsigned int	bi_clr_important;
}				t_bitmap_info_header;

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_line_var
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int error;
	int error2;
}				t_line_var;

typedef struct	s_player
{
	float	x;
	float	y;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
	int		turn_direction;
	int		walk_direction;
	int		strafe_direction;
}				t_player;

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_image;

typedef struct	s_sprite
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	sprite_dir;
	float	player_dist;
	int		texture_id;
}				t_sprite;

typedef	struct	s_map
{
	t_player	player;
	char		**grid;
	int			width;
	int			height;
	int			tile_width;
	int			tile_height;
	int			ceil_color;
	int			floor_color;
	int			color;
	int			sprites;
}				t_map;

typedef struct	s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vert;
	int		was_hit_horz;
	int		wall_hit_content;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_right;
	int		is_ray_facing_left;
}				t_ray;

typedef struct	s_texture
{
	t_image image;
	int		width;
	int		height;
}				t_texture;

typedef struct	s_cube
{
	t_image		image;
	t_map		map;
	t_ray		*rays;
	t_texture	texture[TEXTURES];
	t_sprite	*sprites;
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	float		fov_angle;
	float		half_fov_angle;
	float		angle_step;
	float		dist_proj_plane;
}				t_cube;

/*
** Utility functions
*/

void			pixel_put(t_image *img, int x, int y, int color);
int				pixel_get(t_image *img, int x, int y);
void			draw_rectangle(t_cube *cube, t_point start,
				t_point end, int color);
void			draw_line(t_cube *cube, t_point start, t_point end, int color);
void			save_bitmap(t_cube *cube);
void			quit_cube(t_cube *cube, int exit_code);

/*
** Color functions
*/

int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				add_shade(double distance, int trgb);
int				add_tint(double distance, int trgb);
int				get_oposite(int trgb);

#endif

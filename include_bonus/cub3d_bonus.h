/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:36:57 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/31 01:29:21 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include "libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <math.h>
# include <limits.h>
# include <sys/stat.h>
# include <fcntl.h>
# define FOV 60
# define PI 3.1415926535f
# define TWO_PI 6.2831853071f
# define TITLE "cub3D"
# define MINIMAP_SCALE 0.2f
# define WALK_SPEED 3.0f
# define TURN_SPEED 2.0f
# define TEXTURES 5
# define VALID_MAP_CHARS "012NSWE "
# define SPAWN_ORIENTATION "NSWE"
# define TILE_SIZE 64
# define ERR_IDENT "Invalid identifier."
# define ERR_CUB "Invalid .cub file."
# define ERR_MAP "Invalid map."
# define ERR_MEM "Memory allocation error."
# define ERR_WR "Write error."
# ifdef __APPLE__
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_S 1
#  define KEY_W 13
#  define KEY_Q 12
#  define KEY_ESC 53
#  define KEY_AR_L 123
#  define KEY_AR_R 124
#  define KEY_M 46
# elif __linux
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_S 115
#  define KEY_W 119
#  define KEY_Q 113
#  define KEY_ESC 65307
#  define KEY_AR_L 65361
#  define KEY_AR_R 65363
#  define KEY_M 109
# endif

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_grid
{
	EMPTY,
	WALL,
	SPACE,
	FILL
};

enum	e_textures
{
	EAST,
	WEST,
	SOUTH,
	NORTH,
	SPRITE
};

enum	e_colors
{
	RAYS_COL = 0xffffff00,
	SPRITE_COL = 0xffffa500,
	PLAYER_COL = 0xff101010,
	PLAYER_DIR_COL = 0xff333333,
	EMPTY_COL = 0xffffffff,
	SPACE_COL = 0xff000000,
	WALL_COL = 0xff003366
};

enum	e_flags
{
	RESOLUTION = 1,
	NORTH_TEX = (1 << 1),
	SOUTH_TEX = (1 << 2),
	WEST_TEX = (1 << 3),
	EAST_TEX = (1 << 4),
	SPRITE_TEX = (1 << 5),
	FLOOR_COL = (1 << 6),
	CEIL_COL = (1 << 7),
	IDENTIFIERS = ((1 << 8) - 1)
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
	int		map_x;
	int		map_y;
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
	float	direction;
	float	player_dist;
	int		size;
	int		y_off;
	int		x_off;
	int		map_x;
	int		map_y;
	int		tex_id;
}				t_sprite;

typedef struct	s_wall_strip
{
	int		strip_height;
	float	proj_height;
	float	perp_dist;
	int		top_pix;
	int		bot_pix;
	int		color;
	int		tex_off_x;
	int		tex_off_y;
	int		top_dist;
	int		side;
}				t_wall_strip;

typedef	struct	s_map
{
	t_player	player;
	char		*paths[TEXTURES];
	int			**grid;
	int			player_found;
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
	float	dist;
	int		was_hit_vert;
	int		was_hit_horz;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_right;
	int		is_ray_facing_left;
}				t_ray;

typedef struct	s_raycast
{
	int		wall_hit;
	float	wall_hit_x;
	float	wall_hit_y;
	float	next_touch_x;
	float	next_touch_y;
	float	hit_dist;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	y_to_check;
	float	x_to_check;
}				t_raycast;

typedef struct	s_texture
{
	t_image image;
	int		width;
	int		height;
}				t_texture;

typedef struct	s_cub
{
	t_image		image;
	t_map		map;
	t_ray		*rays;
	t_texture	texture[TEXTURES];
	t_sprite	*sprites;
	char		**info;
	char		*row;
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			minimap;
	int			savebmp;
	float		fov_angle;
	float		half_fov_angle;
	float		angle_step;
	float		dist_proj_plane;
}				t_cub;

/*
** Utility
*/

void			pixel_put(t_image *img, int x, int y, int color);
int				pixel_get(t_image *img, int x, int y);
void			draw_rectangle(t_cub *cub, t_point start,
				t_point end, int color);
void			draw_line(t_cub *cub, t_point start, t_point end, int color);
float			points_dist(float x1, float x2, float y1, float y2);
float			normalize_angle(float angle);
int				grid_color(int row, int col, t_cub *cub);
int				wall_side(t_ray *ray);
int				is_wall(int x, int y, t_map *map);
int				strlen_isdigit(char *str);
void			free_info_lst_quit(char **info, t_list *head, t_cub *cub,
				char *err_msg);
void			free_lst_quit(t_list *head, t_cub *cub, char *error_msg);

/*
** Others
*/

void			quit_cub(t_cub *cub, int exit_code, char *error_message);
int				check_args(int argc, char **argv, t_cub *cub);

/*
** Move player
*/

void			move_player(t_player *player, t_cub *cub);

/*
** Draw
*/

void			draw_sprites(t_cub *cub);
void			project_walls(t_cub *cub);
void			draw_floor(int x, t_wall_strip *wall, t_cub *cub);
void			draw_ceiling(int x, t_wall_strip *wall, t_cub *cub);

/*
** Draw minimap
*/

void			draw_minimap(t_cub *cub);
void			draw_rays_minimap(t_ray *rays, t_cub *cub);
void			draw_player_minimap(t_cub *cub, t_player *player);
void			draw_sprites_minimap(t_cub *cub);

/*
** Raycast
*/

void			cast_rays(t_cub *cub);
void			cast_ray_horz(t_raycast *horz, t_map *map, t_ray *ray);
void			cast_ray_vert(t_raycast *vert, t_map *map, t_ray *ray);

/*
** Save to bitmap
*/

void			save_bitmap(t_cub *cub);

/*
** Parse .cub file
*/

void			parse_cub(char *path, t_cub *cub);
void			parse_grid(t_list *trav, t_list *head, t_cub *cub);
void			boundary_fill(int x, int y, int *open, t_cub *cub);
void			rev_boundary_fill(t_cub *cub);
int				save_map(t_list *trav, t_cub *cub);
int				parse_resolution(int *flags, t_cub *cub);
int				parse_color(int *flags, t_cub *cub);
int				parse_texture(int *flags, t_cub *cub);

/*
** Initialize
*/

void			initialize(t_cub *cub);

/*
** Set mouse and keyboard hooks
*/

void			set_hooks(t_cub *cub);

#endif

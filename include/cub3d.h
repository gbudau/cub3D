/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:36:57 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/12 13:13:13 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <X11/X.h>
# include <stdlib.h>
# define FOV 60
# define HALFFOV 30
# define PI_2 1.5707963267f
# define PI 3.1415926535f
# define TWO_PI 6.2831853071f
# define TILE_SIZE 64
# define KEY_A 97
# define KEY_D 100
# define KEY_S 115
# define KEY_W 119
# define KEY_Q 113
# define KEY_ESC 65307
# define KEY_AR_L 65361
# define KEY_AR_R 65363
# define WINDOW_TITLE "cub3d"
# define MINIMAP_SCALE 1
# define RADIAN_ANGLE 0.0174532925f
# define WALK_SPEED 0.3f

// Delete/Replace later
#define MAP_WIDTH 20
#define MAP_HEIGHT 15

typedef struct	s_position {
	int x;
	int y;
}				t_position;

typedef struct	s_line_var
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int error;
	int error2;
}				t_line_var;

typedef struct	s_player {
	float		x;
	float		y;
	float		rotation_angle;
	float		walk_speed;
	float		turn_speed;
	int			turn_direction;
	int			walk_direction;
	int			strafe_direction;
}				t_player;

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_image;

typedef struct	s_window {
	void	*win;
	int		width;
	int		height;
}				t_window;

typedef	struct	s_map {
	t_player	player;
	char		**grid;
	int			width;
	int			height;
	int			tile_width;
	int			tile_height;
	int			ceil_color;
	int			floor_color;
	int			color;
}				t_map;

typedef struct	s_cube {
	t_window	window;
	t_image		image;
	t_map		map;
	void		*mlx;
}				t_cube;

/*
** Utility functions
*/

void	pixel_put(t_image *img, int x, int y, int color);
void	draw_rectangle(t_cube *cube, t_position start, t_position end);
void	draw_line(t_cube *cube, t_position start, t_position end);

/*
** Color functions
*/

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		add_shade(double distance, int trgb);
int		add_tint(double distance ,int trgb);
int		get_oposite(int trgb);

#endif

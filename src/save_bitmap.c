/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:32:37 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/18 21:17:37 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	initialize_bit_file_header(t_bitmap_file_header *bfh, t_cube *cube)
{
	bfh->bf_reverved1 = 0;
	bfh->bf_reserved2 = 0;
	bfh->bf_off_bits = 54;
	bfh->bf_size = 2 + sizeof(t_bitmap_file_header) +
					sizeof(t_bitmap_info_header) +
					cube->width * cube->height * 4;
}

static void	initialize_bit_info_header(t_bitmap_info_header *bih, t_cube *cube)
{
	bih->bi_size = sizeof(t_bitmap_info_header);
	bih->bi_width = cube->width;
	bih->bi_height = cube->height;
	bih->bi_planes = 1;
	bih->bi_bit_count = 32;
	bih->bi_compression = 0;
	bih->bi_size_image = 0;
	bih->bi_x_pels_per_meter = 2835;
	bih->bi_y_pels_per_meter = 2835;
	bih->bi_clr_used = 0;
	bih->bi_clr_important = 0;
}

static void	write_bitmap_to_image(t_bitmap_file_header *bfh,
		t_bitmap_info_header *bih, int fd, t_cube *cube)
{
	unsigned short	bf_type;
	int				y;
	int				x;
	int				pixel;

	bf_type = 0x4d42;
	if ((write(fd, &bf_type, sizeof(bf_type))) < 0)
		quit_cube(cube, EXIT_FAILURE);
	if ((write(fd, bfh, sizeof(*bfh))) < 0)
		quit_cube(cube, EXIT_FAILURE);
	if ((write(fd, bih, sizeof(*bih))) < 0)
		quit_cube(cube, EXIT_FAILURE);
	y = bih->bi_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < bih->bi_width)
		{
			pixel = pixel_get(&cube->image, x, y);
			if ((write(fd, &pixel, sizeof(pixel))) < 0)
				quit_cube(cube, EXIT_FAILURE);
			x++;
		}
		y--;
	}
}

void		save_bitmap(t_cube *cube)
{
	t_bitmap_file_header	bfh;
	t_bitmap_info_header	bih;
	int						fd;

	initialize_bit_file_header(&bfh, cube);
	initialize_bit_info_header(&bih, cube);
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		quit_cube(cube, EXIT_FAILURE);
	write_bitmap_to_image(&bfh, &bih, fd, cube);
	close(fd);
}

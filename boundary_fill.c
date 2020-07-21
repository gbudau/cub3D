#include <stdio.h>

#define WIDTH 8
#define HEIGHT 8

int	grid[HEIGHT][WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 1},
	{1, 0, 1,' ', 0, 1, 0, 1},
	{1, 0, 1,' ',' ', 1, 0, 1},
	{1, 0, 1,' ',' ', 1, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 1},
	{1, 1,' ', 1, 0, 1, 1, 1}
};

static int	get_pixel(int x, int y)
{
	return grid[y][x];
}

static void	put_pixel(int x, int y, int color)
{
	grid[y][x] = color;
}

static void	boundary_fill(int x, int y, int f_color, int b_color, int *test)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT ||
			get_pixel(x, y) == ' ')
	{
		*test = 1;
		return;
	}
	if (get_pixel(x, y) != b_color && get_pixel(x, y) != f_color)
	{
		put_pixel(x, y, f_color);
		boundary_fill(x + 1, y, f_color, b_color, test);
		boundary_fill(x, y + 1, f_color, b_color, test);
		boundary_fill(x - 1, y, f_color, b_color, test);
		boundary_fill(x, y - 1, f_color, b_color, test);
	}
}

int	main(void)
{
	int test;
	test = 0;
	boundary_fill(2, 2, 5, 1, &test);
	if (test == 1)
		printf("Open\n");
	else
		printf("Close\n");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			if (grid[i][j] == ' ')
				printf("%d", 3);
			else
				printf("%d", grid[i][j]);
		printf("\n");
	}
	printf("%d\n", test);
}

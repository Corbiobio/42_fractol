#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "fractol.h"
#include "libattopng.h"

#define TWO_PI M_PI*2
#define MAX_ITER 2000
#define RGB(r, g, b) (((int)r) | (((int)g) << 8) | (((int)b) << 16))

double	calc_mandelbrot_gradient(double c_real, double c_im)
{
	double	real = 0;
	double	im = 0;
	double	index = 0;

	while (im * im + real * real < 32 && index < MAX_ITER)
	{
		const double tmp_im = im;
		im = 2 * real * im + c_im;
		real = real * real - tmp_im * tmp_im + c_real;
		index++;
	}
	if (index == MAX_ITER)
		return (index);
	return (32 + index - log2(log2(im * im + real * real)));
}

void	update_range(t_complex *comp)
{
	comp->im_range = comp->im_end - comp->im_start;
	comp->real_range = comp->real_end - comp->real_start;
	comp->im_range_per_px = comp->im_range / SCREEN_HEIGHT;
	comp->real_range_per_px = comp->real_range / SCREEN_WIDTH;
}

void init_complex(t_complex* comp)
{
	comp->real_start = -3;
	comp->real_end = 1.4;

	const double temp = 4.4 / SCREEN_RATIO / 2;
	comp->im_start = -temp;
	comp->im_end = temp;
	update_range(comp);
}

void	color_gradient(double index, double *rgb)
{
	index /= 28;
	index = index - (int)index;

	rgb[0] = 0.775 + 0.225 * cos(TWO_PI * (1.0 * index + 0.0));
	rgb[1] = 0.9 + 0.1 * cos(TWO_PI * (1.0 * index + 0.0));
	rgb[2] = 1.0 + 0.0 * cos(TWO_PI * (1.0 * index + 0.0));
	rgb[0] = rgb[0] * 255;
	rgb[1] = rgb[1] * 255;
	rgb[2] = rgb[2] * 255;
}

void	zoom(t_complex* comp, bool zoom_in, int x, int y)
{
	const double real_offset = ((double)x / SCREEN_WIDTH) * comp->real_range;
	const double im_offset = ((double)y / SCREEN_HEIGHT) * comp->im_range;

	if (zoom_in)
	{
		comp->real_start += real_offset / 10;
		comp->real_end -= (comp->real_range - real_offset) / 10;
		comp->im_start += im_offset / 10;
		comp->im_end -= (comp->im_range - im_offset) / 10;
	}
	else
	{
		comp->real_start -= real_offset / 10;
		comp->real_end += (comp->real_range - real_offset) / 10;
		comp->im_start -= im_offset / 10;
		comp->im_end += (comp->im_range - im_offset) / 10;
	}
	update_range(comp);
}

void	move(t_complex *comp, int key)
{
	double	real_offset;
	double	im_offset;

	if (key == KEY_UP)
	{
		im_offset = comp->im_range / 50;
		comp->im_start -= im_offset;
		comp->im_end -= im_offset;
	}
	else if (key == KEY_DOWN)
	{
		im_offset = comp->im_range / 50;
		comp->im_start += im_offset;
		comp->im_end += im_offset;
	}
	else if (key == KEY_LEFT)
	{
		real_offset = comp->real_range / 50;
		comp->real_start -= real_offset;
		comp->real_end -= real_offset;
	}
	else if (key == KEY_RIGHT)
	{
		real_offset = comp->real_range / 50;
		comp->real_start += real_offset;
		comp->real_end += real_offset;
	}
}


void	fill_png(t_complex* comp, libattopng_t* png)
{
	int y = 0;

	comp->im_curr = comp->im_start;
	while (y < SCREEN_HEIGHT)
	{
		int x = 0;
		comp->real_curr = comp->real_start;
		while (x < SCREEN_WIDTH)
		{
			double iteration = calc_mandelbrot_gradient(comp->real_curr, comp->im_curr);
			if (iteration == MAX_ITER)
				libattopng_set_pixel(png, x, y, 0);
			else
			{
				double rgb[3];
				color_gradient(iteration, rgb);
				libattopng_set_pixel(png, x, y, RGB(rgb[0], rgb[1], rgb[2]));
			}
			comp->real_curr += comp->real_range_per_px;
			x++;
		}
		comp->im_curr += comp->im_range_per_px;
		y++;
	}
}


int main(int ac, char** av)
{
	int fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) == -1)
	{
		printf("need a fractol output\n");
		return EXIT_FAILURE;
	}
	libattopng_t* png = libattopng_new(SCREEN_WIDTH, SCREEN_HEIGHT, PNG_RGB);
	if (png == NULL)
		return EXIT_FAILURE;

	t_complex comp;
	init_complex(&comp);

	char *buff;
	char *endptr;
	while ((buff = get_next_line(fd)) != NULL)
	{
		if (ft_isdigit(buff[0]))
			zoom(&comp, buff[0] - '0', strtol(buff + 2, &endptr, 10), strtol(endptr + 1, NULL, 10));
		else
			move(&comp, buff[0]);
		free(buff);
	}
	fill_png(&comp, png);

	libattopng_save(png, "fractol.png");
	libattopng_destroy(png);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:35:38 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/05 18:22:29 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "color.h"
#include "mlx.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>

void	draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	*(unsigned int *)(img->addr + (img->line_length * y + x * img->bits_per_pixel)) = color;
}

void	*thr_calc(void *line_data)
{
	t_line_data	*line = (t_line_data *)line_data;
	const int	max_iteration = line->max_iteration;
	const int	color_func_id = line->color_func_id;
	int			y = line->y_start;

	while (y < line->y_stop)
	{
		line->comp.real_curr = line->comp.real_start;
		double x = 0;
		while (x < SCREEN_WIDTH)
		{
			double iteration = line->fractal_func(&line->comp, max_iteration);
			if (iteration == max_iteration)
				draw_pixel(line->img, x, y, 0x000000);
			else
				draw_pixel(line->img, x, y, get_color_form_palet(iteration, color_func_id));
			line->comp.real_curr += line->comp.real_range_per_px;
			++x;
		}
		line->comp.im_curr += line->comp.im_range_per_px;
		++y;
	}
	return (NULL);
}

int	is_in_mandelbrot(double c_real, double c_im, int max_iteration)
{
	double	real = 0;
	double	im = 0;
	double	index = 0;
	double	tmp_im;

	while (im * im + real * real < 16 && index < max_iteration)
	{
		tmp_im = im;
		im = 2 * real * im + c_im;
		real = real * real - tmp_im * tmp_im + c_real;
		++index;
	}
	return (index == max_iteration);
}

void	budha_calc(t_data *data)
{
	srand(1);
	int arr[SCREEN_WIDTH][SCREEN_HEIGHT][3];
	bzero(arr, sizeof(arr));

	data->max_iteration = 5000;
	for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT) * 5; ++i)
	{
		const double c_real = fmod((rand() / 10000000.0), 4.0) - 2;
		const double c_im = fmod((rand() / 10000000.0), 4.0) - 2;

		if (is_in_mandelbrot(c_real, c_im, data->max_iteration))
			continue;

		double	real = 0;
		double	im = 0;
		for (int j = 0; j < data->max_iteration; ++j)
		{
			double tmp_im = im;
			im = 2 * real * im + c_im;
			real = real * real - tmp_im * tmp_im + c_real;

			int x;
			int y;
			fractal_coord_to_img_coord(data->comp, real, im, &x, &y);
			if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
				continue;
			arr[x][y][0]++;
		}
	}

	data->max_iteration = 500;
	for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT) * 5; ++i)
	{
		const double c_real = fmod((rand() / 10000000.0), 4.0) - 2;
		const double c_im = fmod((rand() / 10000000.0), 4.0) - 2;

		if (is_in_mandelbrot(c_real, c_im, data->max_iteration))
			continue;

		double	real = 0;
		double	im = 0;
		for (int j = 0; j < data->max_iteration; ++j)
		{
			double tmp_im = im;
			im = 2 * real * im + c_im;
			real = real * real - tmp_im * tmp_im + c_real;

			int x;
			int y;
			fractal_coord_to_img_coord(data->comp, real, im, &x, &y);
			if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
				continue;
			arr[x][y][1]++;
		}
	}

	data->max_iteration = 50;
	for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT) * 5; ++i)
	{
		const double c_real = fmod((rand() / 10000000.0), 4.0) - 2;
		const double c_im = fmod((rand() / 10000000.0), 4.0) - 2;

		if (is_in_mandelbrot(c_real, c_im, data->max_iteration))
			continue;

		double	real = 0;
		double	im = 0;
		for (int j = 0; j < data->max_iteration; ++j)
		{
			double tmp_im = im;
			im = 2 * real * im + c_im;
			real = real * real - tmp_im * tmp_im + c_real;

			int x;
			int y;
			fractal_coord_to_img_coord(data->comp, real, im, &x, &y);
			if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
				continue;
			arr[x][y][2]++;
		}
	}

	int max[3] = {0};
	for (int i = 0; i < SCREEN_WIDTH; ++i) {
		for (int j = 0; j < SCREEN_HEIGHT; ++j) {
			if (arr[i][j][0] > max[0])
				max[0] = arr[i][j][0];
			if (arr[i][j][1] > max[1])
				max[1] = arr[i][j][1];
			if (arr[i][j][2] > max[2])
				max[2] = arr[i][j][2];
		}
	}

	for (int i = 0; i < SCREEN_WIDTH; ++i) {
		for (int j = 0; j < SCREEN_HEIGHT; ++j) {
			double factor[3] =  {(double)arr[i][j][0] / max[0], (double)arr[i][j][1] / max[1], (double)arr[i][j][2] / max[2]};
			draw_pixel(data->img, i, j, create_rgb(factor[0] * 0xFF, factor[1] * 0xFF, factor[2] * 0xFF));
		}
	}

	printf("done\n");
}

#define TRH 150

void	calcul_fractal(t_data *data)
{
	const int	max_y = TRH > SCREEN_HEIGHT ? SCREEN_HEIGHT : TRH;
	const int	y_per_thr = SCREEN_HEIGHT / max_y;
	t_line_data	lines[TRH];
	pthread_t	thrs[TRH];
	int			i = 0;

	data->comp->im_curr = data->comp->im_start;
	while (i < max_y)
	{
		lines[i].img = data->img;
		lines[i].fractal_func = data->fractal_func;
		lines[i].color_func_id = data->color_func_id;
		lines[i].max_iteration = data->max_iteration;
		lines[i].comp = *data->comp;
		lines[i].y_start = i * y_per_thr;
		lines[i].comp.im_curr += y_per_thr * lines[i].comp.im_range_per_px * i;
		lines[i].y_stop = i * y_per_thr + y_per_thr;
		++i;
	}
	lines[i - 1].y_stop = SCREEN_HEIGHT;

	i = 0;
	while (i < max_y)
	{
		pthread_create(thrs + i, NULL, &thr_calc, lines + i);
		++i;
	}
	i = 0;
	while (i < max_y)
	{
		pthread_join(thrs[i], NULL);
		++i;
	}
}

void	draw_fractal(t_data *data)
{
	//struct timespec start, end;
	//clock_gettime(CLOCK_MONOTONIC, &start);

	calcul_fractal(data);
	//budha_calc(data);
	mlx_put_image_to_window(data->mlx, data->mlx_wind,
		data->img->img, 0, 0);

	//clock_gettime(CLOCK_MONOTONIC, &end);
	//double tdiff = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
	//printf("%f\n", tdiff);
}

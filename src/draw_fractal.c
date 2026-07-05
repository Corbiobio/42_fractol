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

#define TRH 1

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
	mlx_put_image_to_window(data->mlx, data->mlx_wind,
		data->img->img, 0, 0);

	//clock_gettime(CLOCK_MONOTONIC, &end);
	//double tdiff = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
	//printf("%f\n", tdiff);
}

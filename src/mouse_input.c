/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:11:53 by edarnand          #+#    #+#             */
/*   Updated: 2026/06/30 03:02:36 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	count_same(int x, int y)
{
	static int old_x = 0;
	static int old_y = 0;
	static int count = 1;

	if (x == old_x && y == old_y)
		++count;
	else
	{
		printf("x: %d, y: %d, count: %d\n", old_x, old_y, count);
		old_x = x;
		old_y = y;
		count = 1;
	}
}

void	handle_zoom(t_data *data, int key, int x, int y)
{
	t_complex	*comp;
	double		real_offset;
	double		im_offset;

	dprintf(data->out, "%d %d %d\n", key == SCROLL_IN || key == KEY_ZOOM_IN, x, y);

	comp = data->comp;
	real_offset = ((double)x / SCREEN_WIDTH) * comp->real_range;
	im_offset = ((double)y / SCREEN_HEIGHT) * comp->im_range;
	if (key == SCROLL_IN || key == KEY_ZOOM_IN)
	{
		comp->real_start += real_offset / 10;
		comp->real_end -= (comp->real_range - real_offset) / 10;
		comp->im_start += im_offset / 10;
		comp->im_end -= (comp->im_range - im_offset) / 10;
	}
	else if (key == SCROLL_OUT || key == KEY_ZOOM_OUT)
	{
		comp->real_start -= real_offset / 10;
		comp->real_end += (comp->real_range - real_offset) / 10;
		comp->im_start -= im_offset / 10;
		comp->im_end += (comp->im_range - im_offset) / 10;
	}
	update_range(comp);
}

static void	handle_weird_mandelbrot(t_data *data)
{
	static int	is_weird = 0;

	if (is_weird == 0)
	{
		data->fractal_func = &weird_mandelbrot;
		is_weird = 1;
	}
	else
	{
		data->fractal_func = get_fractal_func(data->fractal_id, data);
		is_weird = 0;
	}
}

int	handle_all_mouse_input(int key, int x, int y, t_data *data)
{
	if (key == SCROLL_IN || key == SCROLL_OUT)
	{
		handle_zoom(data, key, x, y);
		draw_fractal(data);
	}
	else if (key == WHEEL_PRESS && data->fractal_id == MANDELBROT)
	{
		handle_weird_mandelbrot(data);
		draw_fractal(data);
	}
	return (0);
}

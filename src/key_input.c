/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:06:53 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/05 18:08:20 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "fractol.h"
#include <fcntl.h>
#include <unistd.h>

static void	move_fractal(t_complex *comp, int key)
{
	double	real_offset;
	double	im_offset;

	if (key == KEY_UP || key == KEY_ARROW_UP)
	{
		im_offset = comp->im_range / 50;
		comp->im_start -= im_offset;
		comp->im_end -= im_offset;
	}
	else if (key == KEY_DOWN || key == KEY_ARROW_DOWN)
	{
		im_offset = comp->im_range / 50;
		comp->im_start += im_offset;
		comp->im_end += im_offset;
	}
	else if (key == KEY_LEFT || key == KEY_ARROW_LEFT)
	{
		real_offset = comp->real_range / 50;
		comp->real_start -= real_offset;
		comp->real_end -= real_offset;
	}
	else if (key == KEY_RIGHT || key == KEY_ARROW_RIGHT)
	{
		real_offset = comp->real_range / 50;
		comp->real_start += real_offset;
		comp->real_end += real_offset;
	}
}

static void	handle_iteration(int key, t_data *data)
{
	if (key == KEY_ADD_ITER)
		data->max_iteration += 10;
	else if (key == KEY_REMOVE_ITER)
	{
		data->max_iteration -= 10;
		if (data->max_iteration > 5)
			data->max_iteration = 5;
	}
	draw_fractal(data);
}

static void	toggle_gradient(t_data *data)
{
	data->has_smooth_gradient = !data->has_smooth_gradient;
	data->fractal_func = get_fractal_func(data->fractal_id, data);
	draw_fractal(data);
}

static void	change_colorset_id(t_data *data, int key)
{
	int *id;

	id = &data->color_func_id;
	if (key == KEY_INCREASE_COLORSET)
		*id = (*id + 1) % COLOR_AMOUNT;
	else if (key == KEY_DECREASE_COLORSET)
	{
		if (*id <= 0)
			*id = COLOR_AMOUNT -1;
		else
			*id = (*id - 1) % COLOR_AMOUNT;
	}
	draw_fractal(data);
}

int	handle_all_key_input(int key, t_data *data)
{
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT
		|| (key >= KEY_ARROW_LEFT && key <= KEY_ARROW_DOWN))
	{
		move_fractal(data->comp, key);
		draw_fractal(data);
	}
	else if (key == KEY_ZOOM_IN || key == KEY_ZOOM_OUT)
	{
		handle_zoom(data, key, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		draw_fractal(data);
	}
	else if (key == KEY_ADD_ITER || key == KEY_REMOVE_ITER)
		handle_iteration(key, data);
	else if (key == KEY_TOGGLE_GRADIENT)
		toggle_gradient(data);
	else if (key == KEY_INCREASE_COLORSET || key == KEY_DECREASE_COLORSET)
		change_colorset_id(data, key);
	else if (key == KEY_SCREENSHOT)
		take_screenshot(data);
	else if (key == KEY_ESC)
		exit_close_free_mlx_and_data(data);
	return (0);
}

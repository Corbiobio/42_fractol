/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:06:53 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/09 16:03:01 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	move_fractal(t_complex *comp, int key)
{
	const double	real_offset = comp->real_range / 50;
	const double	im_offset = comp->im_range / 50;

	if (key == 'w' || key == KEY_UP)
	{
		comp->im_start -= im_offset;
		comp->im_end -= im_offset;
	}
	else if (key == 's' || key == KEY_DOWN)
	{
		comp->im_start += im_offset;
		comp->im_end += im_offset;
	}
	else if (key == 'a' || key == KEY_LEFT)
	{
		comp->real_start -= real_offset;
		comp->real_end -= real_offset;
	}
	else if (key == 'd' || key == KEY_RIGHT)
	{
		comp->real_start += real_offset;
		comp->real_end += real_offset;
	}
}

static void	handle_iteration(int key, t_data *data)
{
	if (key == KEY_ADD_ITER)
		data->max_iteration += 10;
	else if (key == KEY_REMOVE_ITER)
		data->max_iteration -= 10;
	draw_fractal(data);
}

static void	handle_gradient(t_data *data)
{
	data->has_smooth_gradient = !data->has_smooth_gradient;
	data->fractal_func = get_fractal_func(data->fractal_id, data);
	draw_fractal(data);
}

static void	handle_index_gradient(t_data *data)
{
	data->color_func_id = (data->color_func_id + 1) % 9;
	draw_fractal(data);
}

int	handle_all_key_input(int key, t_data *data)
{
	if (key == 'w' || key == 'a' || key == 's' || key == 'd'
		|| (key >= KEY_LEFT && key <= KEY_DOWN))
	{
		move_fractal(data->comp, key);
		draw_fractal(data);
	}
	else if (key == KEY_ZOOM_IN || key == KEY_ZOOM_OUT)
	{
		handle_zoom(data, key, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		draw_fractal(data);
	}
	else if (key == KEY_ADD_ITER
		|| (key == KEY_REMOVE_ITER && data->max_iteration >= 20))
		handle_iteration(key, data);
	else if (key == KEY_GRADIENT)
		handle_gradient(data);
	else if (key == KEY_GRADIENT)
		handle_gradient(data);
	else if (key == KEY_CHANGE_GRADIENT)
		handle_index_gradient(data);
	else if (key == KEY_ESC)
		exit_close_free_mlx_and_data(data);
	return (0);
}

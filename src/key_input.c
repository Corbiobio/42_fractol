/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:06:53 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/19 18:21:57 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

static void	move_fractal(t_complex *comp, int key)
{
	const double	real_offset = comp->real_range / 50;
	const double	im_offset = comp->im_range / 50;

	if (key == 'w' || key == ARROW_UP)
	{
		comp->im_start -= im_offset;
		comp->im_end -= im_offset;
	}
	else if (key == 's' || key == ARROW_DOWN)
	{
		comp->im_start += im_offset;
		comp->im_end += im_offset;
	}
	else if (key == 'a' || key == ARROW_LEFT)
	{
		comp->real_start -= real_offset;
		comp->real_end -= real_offset;
	}
	else if (key == 'd' || key == ARROW_RIGHT)
	{
		comp->real_start += real_offset;
		comp->real_end += real_offset;
	}
}

static void	key_zoom(t_complex *comp, int screen_width, int key)
{
	const double	real_offset = comp->real_range / 40;
	const double	im_offset = comp->im_range / 40;

	if (key == '=')
	{
		comp->real_start += real_offset;
		comp->real_end -= real_offset;
		comp->im_start += im_offset;
		comp->im_end -= im_offset;
	}
	else if (key == '-')
	{
		comp->real_start -= real_offset;
		comp->real_end += real_offset;
		comp->im_start -= im_offset;
		comp->im_end += im_offset;
	}
	update_range(comp, screen_width);
}

int	handle_all_key_input(int key, t_data *data)
{
	if (key == 'w' || key == 'a' || key == 's' || key == 'd'
		|| (key >= ARROW_LEFT && key <= ARROW_DOWN))
	{
		move_fractal(data->comp, key);
		draw_fractal(data->img, data->comp, data->screen_width,
			data->max_iteration);
		mlx_put_image_to_window(data->mlx, data->mlx_wind,
			data->img->img, 0, 0);
	}
	else if (key == '-' || key == '=')
	{
		key_zoom(data->comp, data->screen_width, key);
		draw_fractal(data->img, data->comp, data->screen_width,
			data->max_iteration);
		mlx_put_image_to_window(data->mlx, data->mlx_wind,
			data->img->img, 0, 0);
	}
	return (0);
}

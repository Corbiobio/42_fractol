/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:06:53 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/20 15:08:54 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>

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

int	exit_close_free_mlx_and_data(t_data *data)
{
	mlx_loop_end(data->mlx);
	mlx_destroy_image(data->mlx, data->img->img);
	mlx_destroy_window(data->mlx, data->mlx_wind);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->comp);
	free(data->img);
	free(data);
	exit(EXIT_SUCCESS);
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
		handle_zoom(data, key, data->screen_width / 2, SCREEN_HEIGHT / 2);
		draw_fractal(data);
	}
	else if (key == KEY_ESC)
		exit_close_free_mlx_and_data(data); 
	return (0);
}

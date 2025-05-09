/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:47:08 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/09 16:09:53 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

double	ft_abs_d(double n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

unsigned int	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

void	update_range(t_complex *comp)
{
	comp->im_range = comp->im_end - comp->im_start;
	comp->real_range = comp->real_end - comp->real_start;
	comp->im_range_per_px = comp->im_range / SCREEN_HEIGHT;
	comp->real_range_per_px = comp->real_range / SCREEN_WIDTH;
}

double	(*get_fractal_func(t_fract_id id, t_data *data))(
	t_complex *comp, int max_iteation)
{
	if (data->has_smooth_gradient == 0)
	{
		if (id == MANDELBROT)
			return (&mandelbrot);
		else if (id == JULIA)
			return (&julia);
		else if (id == PHOENIX)
			return (&phoenix);
		else if (id == BURNIN_SHIP)
			return (&burning_ship);
		else if (id == FISH)
			return (&fish);
		return (NULL);
	}
	if (id == MANDELBROT)
		return (&mandelbrot_gradient);
	else if (id == JULIA)
		return (&julia_gradient);
	else if (id == PHOENIX)
		return (&phoenix_gradient);
	else if (id == BURNIN_SHIP)
		return (&burning_ship_gradient);
	else if (id == FISH)
		return (&fish_gradient);
	return (NULL);
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

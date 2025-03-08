/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:27:31 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/08 10:37:18 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "X11/X.h"
#include <stdio.h>
#include <stdlib.h>

static int	update_julia_c(int x, int y, t_data *data)
{
	static int	x_old = 0;
	static int	y_old = 0;
	const int	offset = SCREEN_HEIGHT / 36;

	if (x <= x_old - offset || x >= x_old + offset)
	{
		if (x > x_old)
			data->comp->julia_c_real += 0.012;
		else
			data->comp->julia_c_real -= 0.012;
		x_old = x;
	}
	if (y <= y_old - offset || y >= y_old + offset)
	{
		if (y > y_old)
			data->comp->julia_c_im += 0.004;
		else
			data->comp->julia_c_im -= 0.004;
		y_old = y;
	}
	if (x == x_old || y == y_old)
		draw_fractal(data);
	return (0);
}

static void	set_julia_value(t_data *data, char **av)
{
	t_complex	*comp;

	comp = data->comp;
	comp->real_start = -2;
	comp->real_end = 2;
	comp->im_start = -1.125;
	comp->im_end = 1.125;
	comp->julia_c_real = parse_str_to_double(av[2]);
	comp->julia_c_im = parse_str_to_double(av[3]);
	update_range(comp, data->screen_width);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = init_data(verif_arg_and_get_fractal_id(ac, av));
	if (data == NULL)
		exit(EXIT_FAILURE);
	if (data->fractal_id == JULIA || data->fractal_id == PHOENIX)
		set_julia_value(data, av);
	if (data->fractal_id == JULIA || data->fractal_id == PHOENIX)
		mlx_hook(data->mlx_wind, MotionNotify, Button1MotionMask,
			&update_julia_c, data);
	mlx_hook(data->mlx_wind, KeyPress, KeyPressMask,
		&handle_all_key_input, data);
	mlx_hook(data->mlx_wind, DestroyNotify, StructureNotifyMask,
		&exit_close_free_mlx_and_data, data);
	mlx_mouse_hook(data->mlx_wind, &handle_all_mouse_input, data);
	draw_fractal(data);
	mlx_loop(data->mlx);
	return (0);
}

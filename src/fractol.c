/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:27:31 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/06 18:11:20 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "X11/X.h"//define for hook
#include <stdio.h>//printf

void	draw_fractal(t_data *data)
{
	calcul_fractal(data->img, data->comp, data->fractal_func, data);
	mlx_put_image_to_window(data->mlx, data->mlx_wind,
		data->img->img, 0, 0);
}

void	draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*pt;

	pt = img->addr + (img->line_length * y + x * img->bits_per_pixel);
	*(unsigned int *)pt = color;
}

void	calcul_fractal(t_img *img, t_complex *comp,
	double (fractal_func)(t_complex *, int), t_data *data)
{
	const int	screen_width = data->screen_width;
	const int	max_iteration = data->max_iteration;
	double		index;
	int			x;
	int			y;

	y = -1;
	comp->im_curr = comp->im_start;
	while (++y < SCREEN_HEIGHT)
	{
		x = 0;
		comp->real_curr = comp->real_start;
		while (x < screen_width)
		{
			index = fractal_func(comp, max_iteration);
			if (index == max_iteration)
				draw_pixel(img, x, y, 0x000000);
			else
				draw_pixel(img, x, y, get_color_form_palet(index,
						data->color_func_id));
			comp->real_curr += comp->real_range_per_px;
			x++;
		}
		comp->im_curr += comp->im_range_per_px;
	}
}

int	update_julia_c(int x, int y, t_data *data)
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

void	set_julia_value(t_data *data, char **av)
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
		printf("error");//FIX exit ?
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

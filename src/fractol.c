/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:27:31 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/20 15:00:04 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include "X11/X.h"//define for hook
#include <stdio.h>//printf
#include <math.h>

void	draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*pt;

	pt = img->addr + (img->line_length * y + x * img->bits_per_pixel);
	*(unsigned int *)pt = color;
}

int	julia(t_complex *comp, double c_real, double c_im, int max_iteration)
{
	double	tmp_real;
	int		index;
	double	real;
	double	im;

	real = comp->real_curr;
	im = comp->im_curr;
	index = 0;
	while (index < max_iteration)
	{
		//nb complex to square = r^2 - im^2 + 2*r*im
		//formula mandelbrot = complex^2 + c
		tmp_real = real * real - im * im;
		im = 2 * real * im + c_im;
		real = tmp_real + c_real;
		if (real > 2.1 || im > 2.1)
			return (index);
		index++;
	}
	return (index);
}

int	mandelbrot(double c_real, double c_im, int max_iteration)
{
	double	real;
	double	im;
	double	tmp_real;
	int		index;

	real = 0;
	im = 0;
	index = 0;
	while (index < max_iteration)
	{
		//nb complex to square = r^2 - im^2 + 2*r*im
		//formula mandelbrot = complex^2 + c
		tmp_real = real * real - im * im;
		im = 2 * real * im + c_im;
		real = tmp_real + c_real;
		if (real > 2.1 || im > 2.1)
			return (index);
		index++;
	}
	return (index);
}

void	draw_fractal(t_img *img, t_complex *comp, int screen_width,
	int max_iteration)
{
	int	index;
	int	x;
	int	y;

	y = 0;
	comp->im_curr = comp->im_start;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		comp->real_curr = comp->real_start;
		while (x < screen_width)
		{
			index = julia(comp, -1.76733, 0.00002, max_iteration);
			//index = mandelbrot(comp->real_curr, comp->im_curr, max_iteration);
			if (index == max_iteration)
				draw_pixel(img, x, y, create_rgb(0, 0, 0));
			else
				draw_pixel(img, x, y, create_rgb(100, 0, index * 5));
			comp->real_curr += comp->real_range_per_px;
			x++;
		}
		comp->im_curr += comp->im_range_per_px;
		y++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = init_data();
	if (data == NULL)
		printf("error");//FIX exit ?
	mlx_hook(data->mlx_wind, KeyPress, KeyPressMask,
		&handle_all_key_input, data);
	mlx_hook(data->mlx_wind, DestroyNotify, StructureNotifyMask,
		&exit_close_free_mlx_and_data, data);
	mlx_mouse_hook(data->mlx_wind, &handle_all_mouse_input, data);
	draw_fractal(data->img, data->comp, data->screen_width,
		data->max_iteration);
	mlx_put_image_to_window(data->mlx, data->mlx_wind, data->img->img, 0, 0);
	mlx_loop(data->mlx);
	(void)ac;
	(void)av;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:27:31 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/14 13:33:35 by edarnand         ###   ########.fr       */
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

	pt = img->addr + (img->line_length * y + x * (img->bits_per_pixel / 8));
	*(unsigned int*)pt = color;
}

void	draw_fractal(t_img *img, t_complex *comp)
{
	int	y = 0;
	double c_im = comp->im_start;
	while (y < SCREEN_HEIGHT)
	{
		int	x = 0;
		double c_real = comp->real_start;
		while (x < SCREEN_WIDTH)
		{
			double r = 0;
			double im = 0;
			int i = 0;
			while (i < 51)
			{
				//nb complex to square = r^2 - im^2 + 2*r*im
				//formula mandelbrot = complex^2 + c
				double tmp_real = r * r - im * im;
				im = 2 * r * im + c_im;
				r = tmp_real + c_real;
				if (r > 2 || im > 2)
					break;
				i++;
			}
			if (i == 51)
				draw_pixel(img, x, y, create_rgb(0, 0, 0));
			else
				draw_pixel(img, x, y, create_rgb(100, 0, i));
			c_real += comp->real_range;
			x++;
		}
		c_im += comp->im_range;
		y++;
	}
}

void	handle_offset(t_complex *comp, int key)
{
	if (key == 'w')
	{
		comp->im_start -= comp->im_range * 20.0;
		comp->im_end -= comp->im_range * 20.0;
	}
	else if (key == 's')
	{
		comp->im_start += comp->im_range * 20.0;
		comp->im_end += comp->im_range * 20.0;
	}
	else if (key == 'a')
	{
		comp->real_start -= comp->real_range * 20.0;
		comp->real_end -= comp->real_range * 20.0;
	}
	else if (key == 'd')
	{
		comp->real_start += comp->real_range * 20.0;
		comp->real_end += comp->real_range * 20.0;
	}
	//comp->im_start
}

int	handle_key(int key, t_data *data)
{
	if (key == 'w' || key == 'a' || key == 's' || key == 'd')
	{
		handle_offset(data->comp, key);
		draw_fractal(data->img, data->comp);
		mlx_put_image_to_window(data->mlx, data->mlx_wind, data->img->img, 0, 0);
		(void)data;
		printf("a\n");
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data *data;

	data = init_data();
	if (data == NULL)
		printf("error");//exit ?
	mlx_key_hook(data->mlx_wind, &handle_key, data);
	draw_fractal(data->img, data->comp);
	mlx_put_image_to_window(data->mlx, data->mlx_wind, data->img->img, 0, 0);
	mlx_loop(data->mlx);
	//mlx_destroy_image(data->mlx, data->img->img);
	//mlx_destroy_window(data->mlx, data->mlx_wind);
	//mlx_destroy_display(data->mlx);
	//free(data->mlx);
	//free(data->comp);
	//free(data->img);
	//free(data);
	(void)ac;
	(void)av;
	//(void)data;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:35:38 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/08 11:07:28 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

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

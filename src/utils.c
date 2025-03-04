/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:47:08 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/04 16:14:29 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

double	ft_abs_d(double n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

//REMOVE
void	print_binary(unsigned int num)
{
	int				i;
	unsigned int	bit;

	i = 31;
	while (i >= 0)
	{
		bit = (num >> i) & 1;
		printf("%d", bit);
		if (i % 8 == 0)
			printf(" ");
		i--;
	}
	printf("\n");
}

unsigned int	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

//REMOVE
void	get_ratio(t_complex *comp)
{
	printf("ratio %f_\n", ((comp->real_end - comp->real_start) / (comp->im_end - comp->im_start)));
}

void	update_range(t_complex *comp, int screen_width)
{
	comp->im_range = comp->im_end - comp->im_start;
	comp->real_range = comp->real_end - comp->real_start;
	comp->im_range_per_px = comp->im_range / SCREEN_HEIGHT;
	comp->real_range_per_px = comp->real_range / screen_width;
}

double	(*get_fractal_func(t_fract_id id, t_data *data))(t_complex *comp, int max_iteation)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:31:25 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/04 16:28:12 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

static double	calc_burning_ship(double c_real, double c_im,
	int max_iteration)
{
	double	real;
	double	im;
	double	tmp_im;
	double	index;

	real = 0;
	im = 0;
	index = 0;
	while (im * im + real * real < 16 && index < max_iteration)
	{
		tmp_im = im;
		im = ft_abs_d(2 * real * im) + c_im;
		real = real * real - tmp_im * tmp_im + c_real;
		index++;
	}
	return (index);
}

static double	calc_burning_ship_gradient(double c_real, double c_im,
	int max_iteration)
{
	double	real;
	double	im;
	double	tmp_im;
	double	index;

	real = 0;
	im = 0;
	index = 0;
	while (im * im + real * real < 16 && index < max_iteration)
	{
		tmp_im = im;
		im = ft_abs_d(2 * real * im) + c_im;
		real = real * real - tmp_im * tmp_im + c_real;
		index++;
	}
	if (index == max_iteration)
		return (index);
	return (index - log2(log2(im * im + real * real)));
}

double	burning_ship(t_complex *comp, int max_iteration)
{
	return (calc_burning_ship(comp->real_curr, comp->im_curr, max_iteration));
}

double	burning_ship_gradient(t_complex *comp, int max_iteration)
{
	return (calc_burning_ship_gradient(comp->real_curr, comp->im_curr,
			max_iteration));
}

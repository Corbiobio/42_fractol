/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fish.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:31:25 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/28 15:57:28 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

double	calc_fish(double c_real, double c_im, int max_iteration)
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
		im = 2 * real * im + c_im;
		real = ft_abs_d(real * real - tmp_im * tmp_im) + c_real;
		index++;
	}
	return (index);
}

double	calc_fish_gradient(double c_real, double c_im, int max_iteration)
{
	double	real;
	double	im;
	double	tmp_im;
	double	index;

	real = 0;
	im = 0;
	index = 0;
	while (im * im + real * real < 32 && index < max_iteration)
	{
		tmp_im = im;
		im = 2 * real * im + c_im;
		real = ft_abs_d(real * real - tmp_im * tmp_im) + c_real;
		index++;
	}
	if (index == max_iteration)
		return (index);
	return (index - log2(log2(im * im + real * real)));
}

double	fish(t_complex *comp, int max_iteration)
{
	return (calc_fish(comp->real_curr, comp->im_curr, max_iteration));
}

double	fish_gradient(t_complex *comp, int max_iteration)
{
	return (calc_fish_gradient(comp->real_curr, comp->im_curr, max_iteration));
}

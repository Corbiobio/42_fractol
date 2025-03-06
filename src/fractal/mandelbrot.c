/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:32:54 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/06 16:34:20 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

double	calc_mandelbrot(double c_real, double c_im, int max_iteration)
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
		real = real * real - tmp_im * tmp_im + c_real;
		index++;
	}
	return (index);
}

static double	calc_mandelbrot_gradient(double c_real, double c_im,
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
		im = 2 * real * im + c_im;
		real = real * real - tmp_im * tmp_im + c_real;
		index++;
	}
	if (index == max_iteration)
		return (index);
	return (index - log2(log2(im * im + real * real)));
}

double	mandelbrot(t_complex *comp, int max_iteration)
{
	return (calc_mandelbrot(comp->real_curr, comp->im_curr, max_iteration));
}

double	mandelbrot_gradient(t_complex *comp, int max_iteration)
{
	return (calc_mandelbrot_gradient(comp->real_curr, comp->im_curr,
			max_iteration));
}

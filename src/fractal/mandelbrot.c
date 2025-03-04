/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:32:54 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/04 13:44:51 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

double	calc_weird_mandelbrot(double c_real, double c_im, int max_iteration)
{
	double	real;
	double	im;
	double	tmp_im;
	double	index;

	real = 0;
	im = 0;
	index = 0;
	while (im * im + real * real < 4 && index < max_iteration)
	{
		tmp_im = im;
		im = 2 * real * im + c_im;
		real = real * real - tmp_im * tmp_im + c_real;
		index++;
	}
	if (index == max_iteration)
		return (index);
	return (index - log(log(im * real + real * im)) + 4.0);
}

static double	calc_mandelbrot(double c_real, double c_im, int max_iteration)
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
	//if (index == max_iteration)
		return (index);
	//double res = index - log2(log2(im * im + real * real));
	//return (res);
}

double	mandelbrot(t_complex *comp, int max_iteration)
{
	return (calc_mandelbrot(comp->real_curr, comp->im_curr, max_iteration));
}

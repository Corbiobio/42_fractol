/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_mandelbrot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:33:44 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/06 16:35:25 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

static double	calc_weird_mandelbrot(double c_real, double c_im,
	int max_iteration)
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

double	weird_mandelbrot(t_complex *comp, int max_iteration)
{
	return (calc_weird_mandelbrot(comp->real_curr, comp->im_curr,
			max_iteration));
}

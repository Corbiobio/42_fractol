/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:32:54 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/03 10:55:18 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calc_mandelbrot(double c_real, double c_im, int max_iteration)
{
	double	real;
	double	im;
	double	tmp_im;
	int		index;

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
	return (index);
}

int	mandelbrot(t_complex *comp, int max_iteration)
{
	return (calc_mandelbrot(comp->real_curr, comp->im_curr, max_iteration));
}

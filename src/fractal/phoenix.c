/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:34:30 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/04 13:53:31 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

static double	calc_phoenix(t_complex *comp, double real, double im, int max_iteration)
{
	double	index;
	double	res_im;
	double	res_real;
	double	old_im;
	double	old_real;

	old_im = 0;
	old_real = 0;
	index = 0;
	while (im * im + real * real < 16 && index < max_iteration)
	{
		res_im = 2 * real * im + comp->julia_c_im * old_im;
		res_real = (real * real - im * im) + comp->julia_c_real + comp->julia_c_im * old_real;
		old_im = im;
		old_real = real;
		im = res_im;
		real = res_real;
		index++;
	}
	//if (index == max_iteration)
		return (index);
	//return (index - log2(log2(im * im + real * real)));
}

//unused
double	real_calc_phoenix(t_complex *comp, double real,
	double im, int max_iteration)
{
	double	index;
	double	res_im;
	double	res_real;
	double	old_im;
	double	old_real;

	old_im = 0;
	old_real = 0;
	index = -1;
	while (++index < max_iteration)
	{
		res_im = 2 * real * im + 0 + comp->julia_c_im * old_im + 0 * old_real;
		res_real = (real * real - im * im) + comp->julia_c_real + comp->julia_c_im * old_real - 0 * old_im;
		old_im = im;
		old_real = real;
		im = res_im;
		real = res_real;
	}
	return (index);
}

double	phoenix(t_complex *comp, int max_iteration)
{
	return (calc_phoenix(comp, -comp->im_curr, -comp->real_curr,
			max_iteration));
}

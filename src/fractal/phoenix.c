/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:34:30 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/28 15:03:19 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calc_phoenix(t_complex *comp, double real, double im, int max_iteration)
{
	int		index;
	double	res_im;
	double	res_real;
	double	old_im;
	double	old_real;

	old_im = 0;
	old_real = 0;
	index = -1;
	while (++index < max_iteration)
	{
		res_im = 2 * real * im;
		res_im += comp->julia_c_im * old_im;
		if (res_im > 2.1)
			return (index);
		res_real = (real * real - im * im) + comp->julia_c_real;
		res_real += comp->julia_c_im * old_real;
		if (res_real > 2.1)
			return (index);
		old_im = im;
		old_real = real;
		im = res_im;
		real = res_real;
	}
	return (index);
}

int	real_calc_phoenix(t_complex *comp, double real,
	double im, int max_iteration)
{
	int		index;
	double	res_im;
	double	res_real;
	double	old_im;
	double	old_real;

	old_im = 0;
	old_real = 0;
	index = -1;
	while (++index < max_iteration)
	{
		res_im = 2 * real * im + 0;
		res_im += comp->julia_c_im * old_im + 0 * old_real;
		if (res_im > 2.1)
			return (index);
		res_real = (real * real - im * im) + comp->julia_c_real;
		res_real += comp->julia_c_im * old_real - 0 * old_im;
		if (res_real > 2.1)
			return (index);
		old_im = im;
		old_real = real;
		im = res_im;
		real = res_real;
	}
	return (index);
}

int	phoenix(t_complex *comp, int max_iteration)
{
	return (calc_phoenix(comp, -comp->im_curr, -comp->real_curr,
			max_iteration));
}

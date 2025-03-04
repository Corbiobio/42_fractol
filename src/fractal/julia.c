/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:34:01 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/03 18:49:09 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	julia(t_complex *comp, int max_iteration)
{
	double	real;
	double	im;
	double	tmp_im;
	double	index;

	real = comp->real_curr;
	im = comp->im_curr;
	index = 0;
	while (im * im + real * real < 4 && index < max_iteration)
	{
		tmp_im = im;
		im = 2 * real * im + comp->julia_c_im;
		real = real * real - tmp_im * tmp_im + comp->julia_c_real;
		index++;
	}
	return (index);
}

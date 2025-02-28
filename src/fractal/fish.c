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

int	calc_fish(double c_real, double c_im, int max_iteration)
{
	double	real;
	double	im;
	double	tmp_im;
	int		index;

	real = 0;
	im = 0;
	index = 0;
	while (index < max_iteration)
	{
		tmp_im = im;
		im = 2 * real * im + c_im;
		if (im > 2.1)
			return (index);
		real = ft_abs_d(real * real - tmp_im * tmp_im) + c_real;
		if (real > 2.1)
			return (index);
		index++;
	}
	return (index);
}

int	fish(t_complex *comp, int max_iteration)
{
	return (calc_fish(comp->real_curr, comp->im_curr, max_iteration));
}

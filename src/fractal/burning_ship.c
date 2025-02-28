/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:31:25 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/28 15:54:22 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calc_burning_ship(double c_real, double c_im, int max_iteration)
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
		im = ft_abs_d(2 * real * im) + c_im;
		if (im > 2.1)
			return (index);
		real = real * real - tmp_im * tmp_im + c_real;
		if (real > 2.1)
			return (index);
		index++;
	}
	return (index);
}

int	burning_ship(t_complex *comp, int max_iteration)
{
	return (calc_burning_ship(comp->real_curr, comp->im_curr, max_iteration));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:34:01 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/28 13:34:16 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_complex *comp, int max_iteration)
{
	double	real;
	double	im;
	double	tmp_im;
	int		index;

	real = comp->real_curr;
	im = comp->im_curr;
	index = 0;
	while (index < max_iteration)
	{
		tmp_im = im;
		im = 2 * real * im + comp->julia_c_im;
		if (im > 2.1)
			return (index);
		real = real * real - tmp_im * tmp_im + comp->julia_c_real;
		if (real > 2.1)
			return (index);
		index++;
	}
	return (index);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_set_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:03:22 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/06 18:41:03 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

void	color_6(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.0));
	rgb[1] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.33));
	rgb[2] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.67));
}

void	color_7(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.38));
	rgb[1] = 0.58 + 0.41 * cos(6.28318 * (1.0 * index + 0.22));
	rgb[2] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.15));
}

void	color_8(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.36 + 0.0 * cos(6.28318 * (2.4 * index + 0.83));
	rgb[1] = 0.5 + -0.18 * cos(6.28318 * (1.6 * index + 0.16));
	rgb[2] = 0.6 + 0.28 * cos(6.28318 * (0.9 * index + -0.7));
}

void	color_9(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.0));
	rgb[1] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.1));
	rgb[2] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.2));
}

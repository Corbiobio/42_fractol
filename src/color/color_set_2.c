/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_set_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:03:22 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/06 18:03:51 by edarnand         ###   ########.fr       */
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
	rgb[0] = 0.65 + -0.65 * cos(6.28318 * (0.333 * index + 0.66));
	rgb[1] = 0.5 + 0.5 * cos(6.28318 * (0.278 * index + 0.0));
	rgb[2] = 0.31 + 0.6 * cos(6.28318 * (0.278 * index + 0.667));
}

void	color_9(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.0));
	rgb[1] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.1));
	rgb[2] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.2));
}

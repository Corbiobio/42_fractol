/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_set_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:03:22 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/06 18:54:49 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

void	color_1(double index, double *rgb)
{
	index /= 20;
	index = index - (int)index;
	rgb[0] = 0.36 + 0.35 * cos(6.28318 * (3.1415 * index + 0.83));
	rgb[1] = 0.5 + 0.5 * cos(6.28318 * (1.9 * index + 0.16));
	rgb[2] = 0.6 + -0.4 * cos(6.28318 * (3.1415 * index + -0.7));
}

void	color_2(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.17 + 0.06 * cos(6.28318 * (0.7 * index + 0.06));
	rgb[1] = 0.5 + 0.45 * cos(6.28318 * (0.4 * index + 0.3));
	rgb[2] = 0.4 + 0.2 * cos(6.28318 * (0.99 * index + 0.1));
}

void	color_3(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.8 + 0.2 * cos(6.28318 * (2.0 * index + 0.0));
	rgb[1] = 0.5 + 0.4 * cos(6.28318 * (1.0 * index + 0.3));
	rgb[2] = 0.4 + 0.2 * cos(6.28318 * (1.0 * index + 0.25));
}

void	color_4(double index, double *rgb)
{
	index /= 40;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(6.28318 * (0.1 * index + 0.0));
	rgb[1] = 0.5 + 0.5 * cos(6.28318 * (0.5 * index + 0.0));
	rgb[2] = 0.0 + 0.0 * cos(6.28318 * (0.0 * index + 0.0));
}

void	color_5(double index, double *rgb)
{
	index /= 25;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.0));
	rgb[1] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.1));
	rgb[2] = 0.5 + 0.5 * cos(6.28318 * (1.0 * index + 0.1));
}

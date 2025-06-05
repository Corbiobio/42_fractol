/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_set_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:03:22 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/12 17:06:27 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>

void	color_6(double index, double *rgb)
{
	index /= 10;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.0));
	rgb[1] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.333));
	rgb[2] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.667));
}

void	color_7(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.38));
	rgb[1] = 0.58 + 0.41 * cos(PI_2 * (1.0 * index + 0.22));
	rgb[2] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.15));
}

void	color_8(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.25 +  0.25 * cos(PI_2 * (2.0 * index + 0.0));
	rgb[1] = 0.25 +  0.25 * cos(PI_2 * (2.0 * index + 0.5));
	rgb[2] = 0.75 +  0.25 * cos(PI_2 * (2.0 * index + 0.25));
}

void	color_9(double index, double *rgb)
{
	index /= 25;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.0));
	rgb[1] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.1));
	rgb[2] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.2));
}

void	color_10(double index, double *rgb)
{
	index /= 25;
	index = index - (int)index;
	rgb[0] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.0));
	rgb[1] = 0.5 + 0.5 * cos(PI_2 * (1.0 * index + 0.333));
	rgb[2] = 0.5 + 0.5 * cos(PI_2 * (-0.887 * index + 0.667));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_set_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:07:59 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/12 17:11:49 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>

void	color_11(double index, double *rgb)
{
	index /= 30;
	index = index - (int)index;
	rgb[0] = 0.36 + 0.35 * cos(PI_2 * (3.1415 * index + 0.83));
	rgb[1] = 0.5 + 0.5 * cos(PI_2 * (1.9 * index + 0.16));
	rgb[2] = 0.6 + -0.4 * cos(PI_2 * (3.1415 * index + -0.7));
}

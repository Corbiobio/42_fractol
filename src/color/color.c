/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:28:58 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/12 17:09:30 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "color.h"

unsigned int	get_color_form_palet(double index, int index_func)
{
	static void	(*color[COLOR_AMOUNT])(double, double *) = {&color_1, &color_2, &color_3,
		&color_4, &color_5, &color_6, &color_7, &color_8, &color_9, &color_10,
		&color_11};
	double		rgb[3];

	color[index_func](index, rgb);
	return (create_rgb(rgb[0] * 255, rgb[1] * 255, rgb[2] * 255));
}

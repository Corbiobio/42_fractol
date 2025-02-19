/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:47:08 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/19 18:00:55 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

double	ft_abs_d(double n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

//REMOVE
void	print_binary(unsigned int num)
{
	int				i;
	unsigned int	bit;

	i = 31;
	while (i >= 0)
	{
		bit = (num >> i) & 1;
		printf("%d", bit);
		if (i % 8 == 0)
			printf(" ");
		i--;
	}
	printf("\n");
}

unsigned int	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

int	get_r(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	get_g(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	get_b(int rgb)
{
	return ((rgb) & 0xFF);
}

//REMOVE
void	get_ratio(t_complex *comp)
{
	printf("ratio %f_\n", ((comp->real_end - comp->real_start) / (comp->im_end - comp->im_start)));
}

void	update_range(t_complex *comp, int screen_width)
{
	comp->im_range = comp->im_end - comp->im_start;
	comp->real_range = comp->real_end - comp->real_start;
	comp->im_range_per_px = comp->im_range / SCREEN_HEIGHT;
	comp->real_range_per_px = comp->real_range / screen_width;
}

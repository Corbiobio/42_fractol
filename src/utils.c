/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:47:08 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/14 13:36:11 by edarnand         ###   ########.fr       */
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

void print_binary(unsigned int num)
{
    for (int i = 31; i >= 0; i--)
    {
        unsigned int bit = (num >> i) & 1;
        printf("%d", bit);
		if (i % 8 == 0)
            printf(" ");
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

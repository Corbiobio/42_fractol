/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:27:31 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/10 21:17:36 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>//printf
#include <math.h>

#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH (int)(SCREEN_HEIGHT*(16.0/9))

unsigned int	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
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

void	draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*pt;

	pt = img->addr + (img->line_length * y + x * (img->bits_per_pixel / 8));
	*(unsigned int*)pt = color;
}
int	get_r(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}
int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Fractol !");
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);





	// r^2 - im^2 + 2*r*im
	//double c_r = -2;
	//double c_im = 1.2;


	double real_start = -2.5;
	double real_end = 2;
	double im_start = 1.2;
	double im_end = -1.5;
	//y im   1.2 -> -1.2 range 2.4 1080
	//x real -2  -> 0.4  range 2.4 1920
	double im_range = (double)(ft_abs(im_start) + ft_abs(im_end)) / SCREEN_HEIGHT;
	double real_range = (double)(ft_abs(real_start) + ft_abs(real_end)) / SCREEN_WIDTH;
	printf("%f\n", real_range);
	int	y = 0;
	double c_im = im_start;
	while (y < SCREEN_HEIGHT)
	{
		int	x = 0;
		double c_real = real_start;
		while (x < SCREEN_WIDTH)
		{
			double r = 0;
			double im = 0;
			int i = 0;
			while (i < 51)
			{
				double tmp_real = r * r - im * im;
				im = 2 * r * im + c_im;
				r = tmp_real + c_real;

				//printf("%f, %f\n", r, im);
				if (isnan(r) || isnan(im))
					break;
				i++;
			}
			if (i == 51)
				draw_pixel(&img, x, y, create_rgb(0, 0, 0));
			else
				draw_pixel(&img, x, y, create_rgb(0, 255, 255 - i * 5));
			c_real += real_range;
			//printf("%f\n", real_range);
			x++;
		}
		c_im -= im_range;
		//printf("%f \n", c_im);
		y++;
	}
	
	//draw_pixel(&img, 100, 100 + y, create_rgb(125, 255, 200));



	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	(void)ac;
	(void)av;
	return (0);
}

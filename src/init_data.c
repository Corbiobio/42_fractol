/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:31:15 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/21 16:13:46 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <unistd.h>

static t_complex	*init_complex(int screen_width)
{
	t_complex	*comp;

	comp = malloc(sizeof(t_complex) * 1);
	if (comp == NULL)
		return (NULL);
	//mandelbrot center
	//comp->real_start = -1.9;
	//comp->real_end = 0.5;
	//comp->im_start = -0.675;
	//comp->im_end = 0.675;
	comp->real_start = -2;
	comp->real_end = 2;
	comp->im_start = -1.125;
	comp->im_end = 1.125;
	comp->julia_c_real = -1.76733;
	comp->julia_c_im = 0.00002;
	update_range(comp, screen_width);
	return (comp);
}

static t_img	*init_img(void *mlx, int screen_width)
{
	t_img	*img;

	img = malloc(sizeof(t_img) * 1);
	if (img == NULL)
		return (NULL);
	img->img = mlx_new_image(mlx, screen_width, SCREEN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->bits_per_pixel /= 8;
	return (img);
}

static void	verif_data_alloc(t_data *data)
{
	if (data->img == NULL || data->mlx_wind == NULL
		|| data->comp == NULL || data->mlx == NULL)
	{
		if (data->mlx != NULL)
		{
			if (data->img != NULL)
				mlx_destroy_image(data->mlx, data->img->img);
			if (data->mlx_wind != NULL)
				mlx_destroy_window(data->mlx, data->mlx_wind);
			mlx_destroy_display(data->mlx);
		}
		free(data->mlx);
		free(data->comp);
		free(data);
		data = NULL;
	}
}

t_data	*init_data(void)
{
	t_data		*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->screen_width = SCREEN_HEIGHT * (16.0 / 9);
	data->max_iteration = 51;
	data->fractal_func = &julia;
	data->fractal_id = JULIA;
	data->comp = init_complex(data->screen_width);
	data->mlx = mlx_init();
	if (data->mlx != NULL)
	{
		data->mlx_wind = mlx_new_window(data->mlx, data->screen_width,
				SCREEN_HEIGHT, "Fractol !");
		data->img = init_img(data->mlx, data->screen_width);
	}
	verif_data_alloc(data);
	return (data);
}

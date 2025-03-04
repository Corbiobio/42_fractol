/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:31:15 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/04 16:07:32 by edarnand         ###   ########.fr       */
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
	comp->real_start = -1.9;
	comp->real_end = 0.5;
	comp->im_start = -0.675;
	comp->im_end = 0.675;
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

static double	(*get_fractal_func(t_fract_id id, t_data *data))(t_complex *comp, int max_iteation)
{
	if (data->has_smooth_gradient == 0)
	{
		if (id == MANDELBROT)
			return (&mandelbrot);
		else if (id == JULIA)
			return (&julia);
		else if (id == PHOENIX)
			return (&phoenix);
		else if (id == BURNIN_SHIP)
			return (&burning_ship);
		else if (id == FISH)
			return (&fish);
		return (NULL);
	}
	if (id == MANDELBROT)
		return (&mandelbrot_gradient);
	else if (id == JULIA)
		return (&julia_gradient);
	else if (id == PHOENIX)
		return (&phoenix_gradient);
	else if (id == BURNIN_SHIP)
		return (&burning_ship_gradient);
	else if (id == FISH)
		return (&fish_gradient);
	return (NULL);
}

t_data	*init_data(t_fract_id id)
{
	t_data		*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->screen_width = SCREEN_HEIGHT * (16.0 / 9);
	data->max_iteration = 51;
	data->has_smooth_gradient = 0;
	data->fractal_id = id;
	data->fractal_func = get_fractal_func(id, data);
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

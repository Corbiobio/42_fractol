/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:31:15 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/09 16:11:24 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>

static t_complex	*init_complex()
{
	t_complex	*comp;

	comp = malloc(sizeof(t_complex) * 1);
	if (comp == NULL)
		return (NULL);
	comp->real_start = -3;
	comp->real_end = 1.4;
	comp->im_start = -1.2375;
	comp->im_end = 1.2375;
	update_range(comp);
	return (comp);
}

static t_img	*init_img(void *mlx)
{
	t_img	*img;

	img = malloc(sizeof(t_img) * 1);
	if (img == NULL)
		return (NULL);
	img->img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->bits_per_pixel /= 8;
	return (img);
}

static t_data	*verif_data_alloc(t_data *data)
{
	if (data->img == NULL || data->mlx_wind == NULL
		|| data->comp == NULL || data->mlx == NULL)
	{
		if (data->mlx != NULL)
		{
			if (data->img != NULL)
			{
				mlx_destroy_image(data->mlx, data->img->img);
				free(data->img);
			}
			if (data->mlx_wind != NULL)
				mlx_destroy_window(data->mlx, data->mlx_wind);
			mlx_destroy_display(data->mlx);
		}
		free(data->mlx);
		free(data->comp);
		free(data);
		data = NULL;
	}
	return (data);
}

t_data	*init_data(t_fract_id id)
{
	t_data		*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->max_iteration = 51;
	data->has_smooth_gradient = 0;
	data->fractal_id = id;
	data->fractal_func = get_fractal_func(id, data);
	data->comp = init_complex();
	data->mlx = mlx_init();
	if (data->mlx != NULL)
	{
		data->mlx_wind = mlx_new_window(data->mlx, SCREEN_WIDTH,
				SCREEN_HEIGHT, "Fractol !");
		data->img = init_img(data->mlx);
	}
	data = verif_data_alloc(data);
	return (data);
}

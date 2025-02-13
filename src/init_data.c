/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:31:15 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/14 13:36:16 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <unistd.h>

static t_complex	*init_complex(void)
{
	t_complex	*comp;

	comp = malloc(sizeof(t_complex) * 1);
	if (comp == NULL)
		return (NULL);
	comp->real_start = -1.7;
	comp->real_end = 0.6;
	comp->im_start = -0.65;
	comp->im_end = 0.65;
	comp->im_range = (comp->im_end - comp->im_start) / SCREEN_HEIGHT;
	comp->real_range = (comp->real_end - comp->real_start) / SCREEN_WIDTH;
	return (comp);
}

static t_img	*init_img(void *mlx)
{
	t_img	*img;

	img = malloc(sizeof(t_img) * 1);
	if (img == NULL)
		return (NULL);
	img->img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	return (img);
}

static void	verif_data_alloc(t_data *data)
{
	if (data->img == NULL || data->mlx_wind == NULL ||
		data->comp == NULL || data->mlx == NULL)
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
	data->comp = init_complex();
	data->mlx = mlx_init();
	if (data->mlx != NULL)
	{
		data->mlx_wind = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Fractol !");
		data->img = init_img(data->mlx);
	}
	verif_data_alloc(data);
	return (data);
}

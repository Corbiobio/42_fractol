/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:11:53 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/20 15:09:00 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

void	handle_zoom(t_data *data, int key, int x, int y)
{
	t_complex	*comp;
	double		real_offset;
	double		im_offset;

	comp = data->comp;
	real_offset = ((double)x / data->screen_width) * comp->real_range;
	im_offset = ((double)y / SCREEN_HEIGHT) * comp->im_range;
	if (key == SCROLL_IN || key == KEY_ZOOM_IN)
	{
		comp->real_start += real_offset / 10;
		comp->real_end -= (comp->real_range - real_offset) / 10;
		comp->im_start += im_offset / 10;
		comp->im_end -= (comp->im_range - im_offset) / 10;
	}
	else if (key == SCROLL_OUT || key == KEY_ZOOM_OUT)
	{
		comp->real_start -= real_offset / 10;
		comp->real_end += (comp->real_range - real_offset) / 10;
		comp->im_start -= im_offset / 10;
		comp->im_end += (comp->im_range - im_offset) / 10;
	}
	update_range(comp, data->screen_width);
}

int	handle_all_mouse_input(int key, int x, int y, t_data *data)
{
	if (key == 4 || key == 5)
	{
		handle_zoom(data, key, x, y);
		draw_fractal(data);
	}
	return (0);
}

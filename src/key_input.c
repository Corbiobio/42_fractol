/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:06:53 by edarnand          #+#    #+#             */
/*   Updated: 2026/06/30 02:43:08 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "fractol.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void	move_fractal(t_complex *comp, int key)
{
	double	real_offset;
	double	im_offset;

	if (key == KEY_UP || key == KEY_ARROW_UP)
	{
		im_offset = comp->im_range / 50;
		comp->im_start -= im_offset;
		comp->im_end -= im_offset;
	}
	else if (key == KEY_DOWN || key == KEY_ARROW_DOWN)
	{
		im_offset = comp->im_range / 50;
		comp->im_start += im_offset;
		comp->im_end += im_offset;
	}
	else if (key == KEY_LEFT || key == KEY_ARROW_LEFT)
	{
		real_offset = comp->real_range / 50;
		comp->real_start -= real_offset;
		comp->real_end -= real_offset;
	}
	else if (key == KEY_RIGHT || key == KEY_ARROW_RIGHT)
	{
		real_offset = comp->real_range / 50;
		comp->real_start += real_offset;
		comp->real_end += real_offset;
	}
}

static void	handle_iteration(int key, t_data *data)
{
	if (key == KEY_ADD_ITER)
		data->max_iteration += 10;
	else if (key == KEY_REMOVE_ITER)
	{
		data->max_iteration -= 10;
		if (data->max_iteration < 5)
			data->max_iteration = 5;
	}
	draw_fractal(data);
}

static void	toggle_gradient(t_data *data)
{
	data->has_smooth_gradient = !data->has_smooth_gradient;
	data->fractal_func = get_fractal_func(data->fractal_id, data);
	draw_fractal(data);
}

static void	change_colorset_id(t_data *data, int key)
{
	int *id;

	id = &data->color_func_id;
	if (key == KEY_INCREASE_COLORSET)
		*id = (*id + 1) % COLOR_AMOUNT;
	else if (key == KEY_DECREASE_COLORSET)
	{
		if (*id <= 0)
			*id = COLOR_AMOUNT -1;
		else
			*id = (*id - 1) % COLOR_AMOUNT;
	}
	draw_fractal(data);
}

//from https://stackoverflow.com/a/3974138
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

//from https://stackoverflow.com/a/4743295
double long_to_double(long mask) {
	double d = 0;
	long long t = (*(long long*)&d) | mask;
	return *(double*)&t;
}

void binary_to_double(char* t)
{
	int len = strlen(t);
	long l = 0;
	for (int i = 0; i < len; ++i)
		l |= ((long)(t[i] - '0') << (len - i - 1));
	double d = long_to_double(l);
	printf("%f\n", d);
}

int	handle_all_key_input(int key, t_data *data)
{
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT
		|| (key >= KEY_ARROW_LEFT && key <= KEY_ARROW_DOWN))
	{
		move_fractal(data->comp, key);
		draw_fractal(data);
	}
	else if (key == KEY_ZOOM_IN || key == KEY_ZOOM_OUT)
	{
		handle_zoom(data, key, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		draw_fractal(data);
	}
	else if (key == KEY_ADD_ITER || key == KEY_REMOVE_ITER)
		handle_iteration(key, data);
	else if (key == KEY_TOGGLE_GRADIENT)
		toggle_gradient(data);
	else if (key == KEY_INCREASE_COLORSET || key == KEY_DECREASE_COLORSET)
		change_colorset_id(data, key);
	else if (key == KEY_SCREENSHOT)
		take_screenshot(data);
	else if (key == KEY_PRINTCOORD)
	{
		printBits(sizeof(double), &data->comp->real_start);
		printBits(sizeof(double), &data->comp->real_end);
		printBits(sizeof(double), &data->comp->im_start);
		printBits(sizeof(double), &data->comp->im_end);
	}
	else if (key == KEY_ESC)
		exit_close_free_mlx_and_data(data);
	return (0);
}

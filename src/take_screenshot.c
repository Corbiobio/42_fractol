/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:06:19 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/05 18:07:31 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <fcntl.h>
#include <unistd.h>

void write_bmp_header(int fd, int width, int height)
{
	unsigned char	header[54] = {0};
	int 			filesize = 54 + 4 * width * height;

	header[0] = 'B';
	header[1] = 'M';
	*(int*)&header[2] = filesize;
	header[10] = 54;
	header[14] = 40;
	*(int*)&header[18] = width;
	*(int*)&header[22] = -height;
	header[26] = 1;
	header[28] = 32;
	write(fd, header, 54);
}

void	take_screenshot(t_data *data)
{
	int fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(2, "Failed to open file\n", 20);
		return ;
	}
	write_bmp_header(fd, SCREEN_WIDTH, SCREEN_HEIGHT);
	write(fd, data->img->addr, SCREEN_HEIGHT * data->img->line_length);
	close(fd);
}
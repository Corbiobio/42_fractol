/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:27:52 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/14 13:34:04 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_complex {
	double	real_start;
	double	real_end;
	double	im_start;
	double	im_end;
	double	im_range;
	double	real_range;
}	t_complex;

typedef struct	t_data {
	void		*mlx;
	void		*mlx_wind;
	t_img		*img;
	t_complex	*comp;
}	t_data;


# define SCREEN_HEIGHT 720
# define SCREEN_WIDTH (int)(SCREEN_HEIGHT*(16.0/9))

//init_data
t_data	*init_data(void);


//utils
double			ft_abs_d(double n);
void 			print_binary(unsigned int num);
unsigned int	create_rgb(unsigned char r, unsigned char g, unsigned char b);

#endif

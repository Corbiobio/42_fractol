/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:27:52 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/19 17:27:37 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_complex
{
	double	real_start;
	double	real_end;
	double	real_curr;
	double	real_range;
	double	real_range_per_px;
	double	im_start;
	double	im_end;
	double	im_curr;
	double	im_range;
	double	im_range_per_px;
}	t_complex;

typedef struct t_data
{
	void		*mlx;
	void		*mlx_wind;
	t_img		*img;
	t_complex	*comp;
	int			screen_width;
	int			max_iteration;
}	t_data;

# define SCREEN_HEIGHT 1080
# define SCROLL_IN 4
# define SCROLL_OUT 5

//init_data
t_data			*init_data(void);

//utils
double			ft_abs_d(double n);
void			print_binary(unsigned int num);
unsigned int	create_rgb(unsigned char r, unsigned char g, unsigned char b);
void			get_ratio(t_complex *comp);//REMOVE
void			update_range(t_complex *comp, int screen_width);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:27:52 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/05 18:11:31 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

typedef enum e_fract_id
{
	ERROR,
	JULIA,
	MANDELBROT,
	PHOENIX,
	BURNIN_SHIP,
	FISH,
}	t_fract_id;

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
	double	julia_c_real;
	double	julia_c_im;
}	t_complex;

typedef struct t_data
{
	void		*mlx;
	void		*mlx_wind;
	t_img		*img;
	t_complex	*comp;
	int			max_iteration;
	t_fract_id	fractal_id;
	int			has_smooth_gradient;
	int			color_func_id;
	double		(*fractal_func)(t_complex*, int);
}	t_data;

typedef struct s_line_data
{
	t_img *img;
	t_complex comp;
	double (*fractal_func)(t_complex*, int);
	t_data *data;
	int y_start;
	int y_stop;
}	t_line_data;

//screen
# define SCREEN_HEIGHT ((double)1080)
//# define SCREEN_HEIGHT ((double)2160)
# define SCREEN_WIDTH ((double)(16.0 / 9 * SCREEN_HEIGHT))

//mouse
# define SCROLL_IN 4
# define SCROLL_OUT 5
# define WHEEL_PRESS 2

//keyboard
# define KEY_ARROW_LEFT 65361
# define KEY_ARROW_UP 65362
# define KEY_ARROW_RIGHT 65363
# define KEY_ARROW_DOWN 65364
# define KEY_LEFT 'a'
# define KEY_UP 'w'
# define KEY_RIGHT 'd'
# define KEY_DOWN 's'
# define KEY_ZOOM_IN '='
# define KEY_ZOOM_OUT '-'
# define KEY_ESC 65307
# define KEY_ADD_ITER 'e'
# define KEY_REMOVE_ITER 'r'
# define KEY_TOGGLE_GRADIENT 'q'
# define KEY_INCREASE_COLORSET 'c'
# define KEY_DECREASE_COLORSET 'x'
# define KEY_SCREENSHOT 'p'
# define PARAM_ERROR 100

//fractol
void			draw_fractal(t_data *data);

//fractal
double			mandelbrot(t_complex *comp, int max_iteration);
double			julia(t_complex *comp, int max_iteration);
double			phoenix(t_complex *comp, int max_iteration);
double			burning_ship(t_complex *comp, int max_iteration);
double			fish(t_complex *comp, int max_iteration);
double			weird_mandelbrot(t_complex *comp, int max_iteration);
//fractal_gradient
double			mandelbrot_gradient(t_complex *comp, int max_iteration);
double			julia_gradient(t_complex *comp, int max_iteration);
double			phoenix_gradient(t_complex *comp, int max_iteration);
double			burning_ship_gradient(t_complex *comp, int max_iteration);
double			fish_gradient(t_complex *comp, int max_iteration);

//key_input
int				handle_all_key_input(int key, t_data *data);

//mouse_input
int				handle_all_mouse_input(int key, int x, int y, t_data *data);
void			handle_zoom(t_data *data, int key, int x, int y);

//verif_param
t_fract_id		verif_arg_and_get_fractal_id(int ac, char **av);
double			parse_str_to_double(char *str);
void			print_notice(void);

//init_data
t_data			*init_data(t_fract_id id);

//take_screenshot
void	take_screenshot(t_data *data);

//utils
double			ft_abs_d(double n);
unsigned int	create_rgb(unsigned char r, unsigned char g, unsigned char b);
void			update_range(t_complex *comp);
double			(*get_fractal_func(t_fract_id id, t_data *data))(
					t_complex *comp, int max_iteation);
int				exit_close_free_mlx_and_data(t_data *data);

#endif

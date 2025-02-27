/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:11:28 by edarnand          #+#    #+#             */
/*   Updated: 2025/02/28 15:38:13 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <unistd.h>

static int	verif_str(char **pt_str)
{
	int		is_negative;
	char	*str;

	str = *pt_str;
	is_negative = 1;
	if (str[0] != '+' && str[0] != '-' && ft_isdigit(str[0]) == 0)
		return (0);
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			is_negative = -1;
		(*pt_str)++;
	}
	return (is_negative);
}

double	parse_str_to_double(char *str)
{
	double	db;
	int		is_negative;
	int		len;

	is_negative = verif_str(&str);
	if (is_negative == 0)
		return (PARAM_ERROR);
	if (ft_isdigit(str[0]) == 1 && ft_strlen(str) == 1)
		return ((str[0] - 48) * is_negative);
	len = ft_strlen(str);
	if (ft_strchr_index(str, '.') != 1 || len >= 7)
		return (PARAM_ERROR);
	db = 0;
	while (len - 2 > 0)
	{
		if (ft_isdigit(str[len - 1]) == 0)
			return (PARAM_ERROR);
		db += (str[len - 1] - 48);
		db /= 10;
		len--;
	}
	db += str[0] - 48;
	return (db * is_negative);
}

void	print_notice(void)
{
	ft_putstr_fd("╔══════════════════════════════╗\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("║        Fractol notice        ║\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("╠══════════════════════════════╣\n", STDOUT_FILENO);
	ft_putstr_fd("║    ./fractol fractal_name    ║\n", STDOUT_FILENO);
	ft_putstr_fd("╠══════════════════════════════╣\n", STDOUT_FILENO);
	ft_putstr_fd("║        fractal_name          ║\n", STDOUT_FILENO);
	ft_putstr_fd("╟──────────────────────────────╢\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("║         mandelbrot           ║\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("╟──────────────────────────────╢\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("║    julia parm_1 parm_2       ║\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("║    param_1 & param_2 need    ║\n", STDOUT_FILENO);
	ft_putstr_fd("║      to be float between     ║\n", STDOUT_FILENO);
	ft_putstr_fd("║        -2 and 2 with a       ║\n", STDOUT_FILENO);
	ft_putstr_fd("║    maximum of four digit     ║\n", STDOUT_FILENO);
	ft_putstr_fd("║      after the decimal       ║\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("╚══════════════════════════════╝\n", STDOUT_FILENO);
}

static t_fract_id	get_fractal_id(char **av)
{
	if (ft_strncmp(av[1], "mandelbrot", 11) == 0)
		return (MANDELBROT);
	else if (ft_strncmp(av[1], "julia", 6) == 0)
		return (JULIA);
	else if (ft_strncmp(av[1], "phoenix", 8) == 0)
		return (PHOENIX);
	else if (ft_strncmp(av[1], "burning_ship", 13) == 0)
		return (BURNIN_SHIP);
	return (ERROR);
}

t_fract_id	verif_arg_and_get_fractal_id(int ac, char **av)
{
	char		is_error;
	t_fract_id	fractal_id;

	is_error = 0;
	if (ac <= 1)
		is_error = PARAM_ERROR;
	else
	{
		fractal_id = get_fractal_id(av);
		if (fractal_id == ERROR)
			is_error = PARAM_ERROR;
		else if (fractal_id == JULIA && ac == 4)
		{
			is_error += parse_str_to_double(av[2]);
			is_error += parse_str_to_double(av[3]);
		}
		else if (fractal_id == PHOENIX && ac == 4)
		{
			is_error += parse_str_to_double(av[2]);
			is_error += parse_str_to_double(av[3]);
		}
		else if (fractal_id == MANDELBROT && ac == 2)
			is_error += 0;
		else if (fractal_id == BURNIN_SHIP && ac == 2)
			is_error += 0;
		else
			is_error = PARAM_ERROR;
	}
	if (is_error == 0)
		return (fractal_id);
	print_notice();
	exit(EXIT_SUCCESS);
}

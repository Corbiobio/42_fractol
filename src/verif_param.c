/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:11:28 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/06 18:08:05 by edarnand         ###   ########.fr       */
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
	double	nbr;
	int		is_negative;
	int		len;

	is_negative = verif_str(&str);
	if (is_negative == 0)
		return (PARAM_ERROR);
	len = ft_strlen(str);
	if (len >= 7 || len == 2 || (len == 1 && ft_isdigit(str[0]) == 0)
		|| (len >= 3 && ft_strchr_index(str, '.') != 1))
		return (PARAM_ERROR);
	nbr = 0;
	while (len - 2 > 0)
	{
		if (ft_isdigit(str[len - 1]) == 0)
			return (PARAM_ERROR);
		nbr += (str[len - 1] - '0');
		nbr /= 10;
		len--;
	}
	nbr += str[0] - '0';
	if (nbr > 2)
		return (PARAM_ERROR);
	return (nbr * is_negative);
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
	ft_putstr_fd("║         fractal_name         ║\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("║          mandelbrot          ║\n", STDOUT_FILENO);
	ft_putstr_fd("║         burning_ship         ║\n", STDOUT_FILENO);
	ft_putstr_fd("║           the_fish           ║\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("╟──────────────────────────────╢\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("║     julia parm_1 parm_2      ║\n", STDOUT_FILENO);
	ft_putstr_fd("║    phoenix parm_1 parm_2     ║\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("║    param_1 & param_2 need    ║\n", STDOUT_FILENO);
	ft_putstr_fd("║      to be float between     ║\n", STDOUT_FILENO);
	ft_putstr_fd("║        -2 and 2 with a       ║\n", STDOUT_FILENO);
	ft_putstr_fd("║    maximum of four digit     ║\n", STDOUT_FILENO);
	ft_putstr_fd("║      after the decimal       ║\n", STDOUT_FILENO);
	ft_putstr_fd("║                              ║\n", STDOUT_FILENO);
	ft_putstr_fd("╚══════════════════════════════╝\n", STDOUT_FILENO);
}

static t_fract_id	get_fractal_id(int ac, char **av)
{
	if (ac <= 1)
		return (ERROR);
	else if (ft_strncmp(av[1], "mandelbrot", 11) == 0)
		return (MANDELBROT);
	else if (ft_strncmp(av[1], "julia", 6) == 0)
		return (JULIA);
	else if (ft_strncmp(av[1], "phoenix", 8) == 0)
		return (PHOENIX);
	else if (ft_strncmp(av[1], "burning_ship", 13) == 0)
		return (BURNIN_SHIP);
	else if (ft_strncmp(av[1], "the_fish", 9) == 0)
		return (FISH);
	else
		return (ERROR);
}

t_fract_id	verif_arg_and_get_fractal_id(int ac, char **av)
{
	char				is_error;
	const t_fract_id	fractal_id = get_fractal_id(ac, av);

	is_error = 0;
	if (ac <= 1)
		is_error = PARAM_ERROR;
	else
	{
		if (fractal_id == ERROR)
			is_error = PARAM_ERROR;
		else if ((fractal_id == JULIA || fractal_id == PHOENIX) && ac == 4)
		{
			is_error += parse_str_to_double(av[2]);
			is_error += parse_str_to_double(av[3]);
		}
		else if ((fractal_id == MANDELBROT || fractal_id == BURNIN_SHIP
				|| fractal_id == FISH) && ac == 2)
			is_error += 0;
		else
			is_error = PARAM_ERROR;
	}
	if (is_error < PARAM_ERROR)
		return (fractal_id);
	print_notice();
	exit(EXIT_SUCCESS);
}

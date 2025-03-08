/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:53:39 by edarnand          #+#    #+#             */
/*   Updated: 2024/11/08 09:57:25 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	clean(char **nptr)
{
	long int	is_negative;

	is_negative = 1;
	while ((**nptr >= '\t' && **nptr <= '\r') || **nptr == ' ')
		*nptr += 1;
	if (*nptr[0] == '-' || *nptr[0] == '+')
	{
		if (*nptr[0] == '-')
			is_negative = -1;
		*nptr += 1;
	}
	return (is_negative);
}

int	ft_atoi(const char *nptr)
{
	long int	total;
	long int	i;
	long int	is_negative;

	i = 0;
	total = 0;
	is_negative = clean((char **)&nptr);
	while (ft_isdigit(nptr[i]) == 1)
	{
		total = total * 10 + (nptr[i] - '0');
		i++;
	}
	return (total * is_negative);
}

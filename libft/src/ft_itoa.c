/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:29:27 by edarnand          #+#    #+#             */
/*   Updated: 2024/11/12 19:02:36 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	total_len(long int n)
{
	int		len;

	len = 1;
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*itoa_calcul(char *s, long int n, int len, int is_negative)
{
	s[len] = '\0';
	s[0] = '-';
	while (len > is_negative)
	{
		s[len - 1] = '0' + n % 10;
		n /= 10;
		len--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char		*s;
	int			len;
	int			is_negative;
	long int	n_cpy;

	is_negative = 0;
	n_cpy = n;
	len = 0;
	if (n < 0)
	{
		n_cpy *= -1;
		is_negative = 1;
		len++;
	}
	len += total_len(n_cpy);
	s = malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	s = itoa_calcul(s, n_cpy, len, is_negative);
	return (s);
}

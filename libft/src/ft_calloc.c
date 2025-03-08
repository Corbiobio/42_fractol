/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:00:22 by edarnand          #+#    #+#             */
/*   Updated: 2024/11/14 14:52:43 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*element;

	if (nmemb * size > 2147483647)
		return (NULL);
	i = 0;
	element = malloc(nmemb * size);
	if (element == NULL)
		return (element);
	while (i < size * nmemb)
	{
		element[i] = 0;
		i++;
	}
	return (element);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:29:00 by edarnand          #+#    #+#             */
/*   Updated: 2025/01/08 11:14:49 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && s[i] != (char)c)
		s++;
	if (s != NULL && s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

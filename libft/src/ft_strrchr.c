/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:18:48 by edarnand          #+#    #+#             */
/*   Updated: 2024/11/07 15:39:55 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*finded;

	finded = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			finded = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		finded = (char *)s;
	return (finded);
}

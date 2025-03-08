/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:18:56 by edarnand          #+#    #+#             */
/*   Updated: 2025/01/08 11:19:31 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int n)
{
	int		i;
	char	*new;

	if (s == NULL)
		return (NULL);
	i = 0;
	new = malloc(sizeof(char) * (n + 1));
	if (new == NULL)
		return (NULL);
	while (i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

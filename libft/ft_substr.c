/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:43:06 by edarnand          #+#    #+#             */
/*   Updated: 2024/11/12 17:52:44 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	unsigned int	i;
	char			*new;

	s_len = ft_strlen(s);
	if (start >= s_len || s_len <= 0)
	{
		new = ft_calloc(1, sizeof(char));
		if (new == NULL)
			return (NULL);
		return (new);
	}
	if (s_len - start > len)
		new = ft_calloc(len + 1, sizeof(char));
	else
		new = ft_calloc(s_len - start + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len && i < (s_len - start))
	{
		new[i] = s[i + start];
		i++;
	}
	return (new);
}

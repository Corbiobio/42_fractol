/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:19:15 by edarnand          #+#    #+#             */
/*   Updated: 2024/11/11 21:42:44 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, const char *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s_len;
	char	*new;
	int		i;

	while (isset((char)*s1, set) && (char)*s1 != '\0')
		s1++;
	s_len = ft_strlen(s1);
	while ((char)*s1 != '\0' && isset(s1[s_len - 1], set))
		s_len--;
	new = malloc(sizeof(char) * (s_len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

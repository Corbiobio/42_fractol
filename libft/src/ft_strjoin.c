/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:59:59 by edarnand          #+#    #+#             */
/*   Updated: 2024/11/11 21:13:26 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*new;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		new[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		new[i + s1_len] = s2[i];
		i++;
	}
	new[s1_len + s2_len] = '\0';
	return (new);
}

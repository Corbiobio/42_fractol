/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:33:22 by edarnand          #+#    #+#             */
/*   Updated: 2025/01/23 14:24:03 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**clear(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
	return (NULL);
}

static int	get_len_next_word(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s == c && *s != '\0')
		s++;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static char	**add_words(char **dst, const char *s, char c, int total)
{
	int	i;
	int	j;
	int	len_word;

	i = 0;
	while (i < total)
	{
		while (*s == c && *s != '\0')
			s++;
		len_word = get_len_next_word(s, c);
		dst[i] = malloc(sizeof(char) * (len_word + 1));
		if (dst[i] == NULL)
			return (clear(dst));
		j = 0;
		while (j < len_word && len_word > 0)
		{
			dst[i][j] = s[j];
			j++;
		}
		dst[i][j] = '\0';
		s += j;
		i++;
	}
	return (dst);
}

static int	get_total_words(const char *s, char c)
{
	int	count_words;
	int	len_word;

	count_words = 0;
	while (*s != '\0')
	{
		len_word = 0;
		while (*s == c && *s != '\0')
			s++;
		len_word = get_len_next_word(s, c);
		if (len_word >= 1)
		{
			s += len_word;
			count_words++;
		}
	}
	return (count_words);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**new;

	if (s == NULL)
		return (NULL);
	len = get_total_words(s, c);
	new = malloc(sizeof(char *) * (len + 1));
	if (new == NULL)
		return (NULL);
	new[len] = 0;
	new = add_words(new, s, c, len);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:20:31 by edarnand          #+#    #+#             */
/*   Updated: 2025/01/21 10:58:51 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

#ifndef GNL_BUFFER_SIZE
# define GNL_BUFFER_SIZE 10
#endif

static char	*get_remain_malloc(char *remain)
{
	char	*new;

	if (remain == NULL)
		new = NULL;
	else
	{
		new = ft_strndup(remain, ft_strlen(remain));
		if (new == NULL)
			return (NULL);
	}
	return (new);
}

static char	*read_line(int fd, char *remain, int *byte)
{
	char	buffer[GNL_BUFFER_SIZE + 1];
	char	*new_line;
	char	*tmp;

	new_line = get_remain_malloc(remain);
	if (new_line == NULL)
		return (NULL);
	while (*byte == GNL_BUFFER_SIZE && ft_strchr_index(new_line, '\n') == -1)
	{
		*byte = read(fd, buffer, GNL_BUFFER_SIZE);
		buffer[*byte] = '\0';
		if (*byte == -1)
		{
			free(new_line);
			return (NULL);
		}
		else if (*byte == 0)
			return (new_line);
		tmp = ft_strjoin(new_line, buffer);
		free(new_line);
		if (tmp == NULL)
			return (NULL);
		new_line = tmp;
	}
	return (new_line);
}

static void	clear_line(char *line, char *remain)
{
	int	nl_pos;

	nl_pos = ft_strchr_index(line, '\n');
	if (nl_pos == -1)
		return ;
	ft_strlcpy(remain, line + nl_pos + 1, ft_strlen(line + nl_pos + 1) + 1);
	line[nl_pos + 1] = '\0';
}

static char	*clear_remain(char *remain)
{
	char	*line;
	int		index_nl;

	index_nl = ft_strchr_index(remain, '\n');
	line = ft_strndup(remain, index_nl + 1);
	ft_strlcpy(remain, remain + index_nl + 1, ft_strlen(remain + index_nl));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	remain[GNL_BUFFER_SIZE + 1];
	char		*line;
	int			byte;

	if (GNL_BUFFER_SIZE <= 0 || fd <= -1)
		return (NULL);
	byte = GNL_BUFFER_SIZE;
	if (ft_strchr_index(remain, '\n') >= 0)
	{
		line = clear_remain(remain);
		return (line);
	}
	line = read_line(fd, remain, &byte);
	remain[0] = '\0';
	if (line == NULL)
		return (NULL);
	if (byte <= 0 && ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	clear_line(line, remain);
	return (line);
}

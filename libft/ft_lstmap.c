/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:13:41 by edarnand          #+#    #+#             */
/*   Updated: 2024/12/12 15:28:28 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew_secur(void *value, void *(*f)(void *))
{
	t_list	*new;

	new = ft_lstnew(NULL);
	if (new == NULL)
		return (NULL);
	new->content = f(value);
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new;
	t_list	*curr;

	if (lst == NULL)
		return (NULL);
	new_lst = ft_lstnew_secur(lst->content, f);
	if (new_lst == NULL)
		return (NULL);
	lst = lst->next;
	curr = new_lst;
	while (lst != NULL)
	{
		new = ft_lstnew_secur(lst->content, f);
		if (new == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&curr, new);
		curr = curr->next;
		lst = lst->next;
	}
	return (new_lst);
}

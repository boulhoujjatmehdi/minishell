/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:18:17 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/20 09:44:51 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*tmp;

	newl = NULL;
	while (lst)
	{
		tmp = ft_lstnew (f (lst->content));
		if (!tmp)
		{
			ft_lstclear (&newl, del);
			return (NULL);
		}
		ft_lstadd_back (&newl, tmp);
		lst = lst->next;
	}
	return (newl);
}

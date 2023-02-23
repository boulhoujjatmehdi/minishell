/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:21:02 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/20 09:43:52 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*t2;

	if (!lst || !del)
		return ;
	t2 = *lst;
	temp = t2;
	while (temp)
	{
		temp = t2->next;
		ft_lstdelone(t2, del);
		t2 = temp;
	}
	*lst = NULL;
}

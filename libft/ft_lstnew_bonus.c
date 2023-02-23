/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:40:24 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/20 09:45:02 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_t_list;

	new_t_list = (t_list *)malloc(sizeof(t_list));
	if (!new_t_list)
		return (0);
	new_t_list->content = content;
	new_t_list->next = NULL;
	return (new_t_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LList2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:54:42 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 15:32:19 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

t_cmd	*lstnew2(void *content)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->str = content;
	new->cmd_args = NULL;
	new->cmd_path = NULL;
	new->str = NULL;
	new->next = NULL;
	new->exit_msg = NULL;
	new->exit_stat = -1;
	new->ctr_c = 0;
	return (new);
}

void	addback2(t_cmd **list, t_cmd *new)
{
	t_cmd	*temp;

	if (!(*list))
		*list = new;
	else
	{
		temp = lstlast2(*list);
		temp->next = new;
	}
}

t_cmd	*lstlast2(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

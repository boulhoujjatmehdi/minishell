/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LList2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:54:42 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/12 19:40:51 by fhihi            ###   ########.fr       */
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

void	delete_node2(t_cmd **head, int key)
{
    t_cmd *temp;
    t_cmd *current  = *head;
	int i;

    if((*head)->key == key)
    {
        temp = *head;    
        *head = (*head)->next;
		free(temp->str);
		free(temp->cmd_path);
		i = 0;
		while (temp->cmd_args && temp->cmd_args[i])
			free(temp->cmd_args[i++]);
        free(temp);
	}
    else
    {
        while(current->next)
        {
            if(current->next->key == key)
            {
                temp = current->next;
                current->next = current->next->next;
        		*head = (*head)->next;
				free(temp->str);
				free(temp->cmd_path);
				i = 0;
				while (temp->cmd_args && temp->cmd_args[i])
					free(temp->cmd_args[i++]);
        		free(temp);
                break;
            }
            else
                current = current->next;
        }
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LList1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:54:45 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/12 19:01:03 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

t_tokens	*lstnew(void *content)
{
	t_tokens	*new_t_list;

	new_t_list = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_t_list)
		return (0);
	new_t_list->token = content;
	new_t_list->token_type = token_type(content);
	new_t_list->prev = NULL;
	new_t_list->next = NULL;
	return (new_t_list);
}

void	addback(t_tokens **list, t_tokens *new)
{
	t_tokens	*temp;

	if (!(*list))
		*list = new;
	else
	{
		temp = lstlast (*list);
		temp->next = new;
		new->prev = temp;
	}
}

t_tokens	*lstlast(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

//this function goes through a the tokens lincked list and indexs it
void	give_pos(t_tokens **list)
{
	t_tokens *head;
	int i;
	
	i = 1;
	head = *list;
	while (head)
	{
		head->pos = i;
		i++;
		head = head->next;
	}
}

void delete_node(t_tokens** head, int key) {
    t_tokens	*current;
    // t_tokens	*temp;

	current = *head;
    while (current != NULL && current->pos != key) {
        current = current->next;
    }
    if (current == NULL)
        return;
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
	free(current->token);
    free(current);
}

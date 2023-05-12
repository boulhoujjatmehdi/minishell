/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_Utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:53:52 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/12 18:55:41 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"


int8_t	join_two_nodes(t_tokens *node1, t_tokens *node2)
{
	char *temp;

	node1->token = ft_strjoin2(node1->token, node2->token);
	return (node2->pos);
}

void	mark_delelimeter(t_tokens **list, int key)
{
	t_tokens *head;

	head = *list;
	while (head)
	{
		if (head->pos == key)
		{
			head->token = ft_joinchar(head->token, 5);
		}
		head = head->next;
	}
}

void	adjest(t_tokens **list)
{
	t_tokens *head;
	int tmp1;
	int tmp2;

	head = *list;
	while (head->next)
	{
		if ((head->token_type == 2 && head->next->token_type == 2) || (head->token_type == 6 && head->next->token_type == 6) || (head->token_type == 7 && head->next->token_type == 7) )
		{
			tmp1 = join_two_nodes(head, head->next);
			tmp2 = head->pos;
			delete_node(list, tmp1);
		}
		else if ((head->token_type == 6 && head->next->token_type == 7) || (head->token_type == 7 && head->next->token_type == 6))
		{
			tmp2 = head->pos;
			tmp1 = join_two_nodes(head, head->next);
			delete_node(list, tmp1);
		}
		else if ((head->token_type == 2 && head->next->token_type == 6) || \
(head->token_type == 6 && head->next->token_type == 2))
		{
			tmp2 = head->pos;
			tmp1 = join_two_nodes(head, head->next);
			delete_node(list, tmp1);
		}
		else if ((head->token_type == 2 && head->next->token_type == 5) || \
(head->token_type == 5 && head->next->token_type == 2))
		{
			tmp2 = head->pos;
			tmp1 = join_two_nodes(head, head->next);
			delete_node(list, tmp1);
		}
		else if ((head->token_type == 2 && head->next->token_type == 7) || \
(head->token_type == 7 && head->next->token_type == 2))
		{
			tmp2 = head->pos;
			tmp1 = join_two_nodes(head, head->next);
			delete_node(list, tmp1);
		}
		else if ((head->token_type == 5 && head->next->token_type == 6) || \
(head->token_type == 6 && head->next->token_type == 5))
		{
			tmp2 = head->pos;
			tmp1 = join_two_nodes(head, head->next);
			delete_node(list, tmp1);
		}
		else if ((head->token_type == 5 && head->next->token_type == 7) || \
(head->token_type == 7 && head->next->token_type == 5))
		{
			tmp2 = head->pos;
			tmp1 = join_two_nodes(head, head->next);
			delete_node(list, tmp1);
		}
		else
			head = head->next;
	}
	mark_delelimeter(list, tmp2);
}
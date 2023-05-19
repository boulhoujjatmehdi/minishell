/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_Utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:53:52 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/19 15:46:06 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

int	join_two_nodes(t_tokens *node1, t_tokens *node2)
{
	node1->token = ft_strjoin2(node1->token, node2->token);
	return (node2->pos);
}

void	mark_delelimeter(t_tokens **list, int key)
{
	t_tokens	*head;

	head = *list;
	while (head)
	{
		if (head->pos == key || head->token_type == 6 || head->token_type == 7)
		{
			head->token = ft_joinchar(head->token, 5);
		}
		head = head->next;
	}
}

int	adjest1(t_tokens *head, t_tokens **list)
{
	int	tmp1;
	int	tmp2;

	tmp2 = head->pos;
	tmp1 = join_two_nodes(head, head->next);
	delete_node(list, tmp1);
	return (tmp2);
}

int	adjest2(t_tokens *head, t_tokens **list, int *tmp)
{
	int	tmp2;
	int	tmp1;

	tmp2 = *tmp;
	if ((head->token_type == 2 && head->next->token_type == 2)
		|| (head->token_type == 6 && head->next->token_type == 6)
		|| (head->token_type == 7 && head->next->token_type == 7))
	{
		tmp2 = adjest1(head, list);
		return (1);
	}
	else if ((head->token_type == 6 && head->next->token_type == 7) || \
	(head->token_type == 7 && head->next->token_type == 6))
	{
		tmp2 = adjest1(head, list);
		return (1);
	}
	else if ((head->token_type == 2 && head->next->token_type == 5) || \
	(head->token_type == 5 && head->next->token_type == 2))
	{
		tmp1 = join_two_nodes(head, head->next);
		delete_node(list, tmp1);
		return (1);
	}
	return (0);
}

void	adjest(t_tokens **list)
{
	t_tokens	*head;
	int			tmp2;

	tmp2 = 0;
	head = *list;
	while (head->next)
	{
		if (adjest2(head, list, &tmp2))
			;
		else if ((head->token_type == 2 && head->next->token_type == 6) || \
		(head->token_type == 6 && head->next->token_type == 2))
			tmp2 = adjest1(head, list);
		else if ((head->token_type == 2 && head->next->token_type == 7) || \
		(head->token_type == 7 && head->next->token_type == 2))
			tmp2 = adjest1(head, list);
		else if ((head->token_type == 5 && head->next->token_type == 6) || \
		(head->token_type == 6 && head->next->token_type == 5))
			tmp2 = adjest1(head, list);
		else if ((head->token_type == 5 && head->next->token_type == 7) || \
		(head->token_type == 7 && head->next->token_type == 5))
			tmp2 = adjest1(head, list);
		else
			head = head->next;
	}
	mark_delelimeter(list, tmp2);
}

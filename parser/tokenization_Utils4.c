/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_Utils4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:00:11 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 19:51:02 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

void	del_emptyyy(t_tokens **list)
{
	t_tokens	*head;

	head = *list;
	give_pos(list);
	while (head)
	{
		if (!ft_strncmp(head->token, "", 1))
		{
			head->token = ft_joinchar(head->token, 2);
			head = head->next;
		}
		else
			head = head->next;
	}
}

int	syntax_error_util(void)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	return (1);
}

int	syntax_error(t_tokens **list)
{
	t_tokens	*head;

	head = *list;
	give_pos(list);
	if ((head->token_type == 3 || head->token_type == 1) && !head->next)
		return (syntax_error_util());
	while (head)
	{
		if (head->token_type == 3 && !head->next)
			return (syntax_error_util());
		if (head->token_type == 1 && !head->next)
			return (syntax_error_util());
		if (head->token_type == 3 && head->next->token_type == 3)
			return (syntax_error_util());
		if (head->token_type == 3 && head->next->token_type == 1)
			return (syntax_error_util());
		if (head->token_type == 1 && (head->pos == 1 || !head->next))
			return (syntax_error_util());
		if (head->token_type == 1 && head->next->token_type == 1)
			return (syntax_error_util());
		head = head->next;
	}
	return (0);
}

//this function checks my token Llist for the single and double redirections
void	check_double_red(t_tokens **list)
{
	t_tokens	*h;
	char		*tmp;

	h = *list;
	while (h->next)
	{
		if (!ft_strncmp("<", h->token, 2) && \
		!ft_strncmp("<", h->next->token, 2))
		{
			delete_node(list, h->next->pos);
			tmp = h->token;
			h->token = ft_strdup("<<");
			free(tmp);
		}
		else if (!ft_strncmp(">", h->token, 2) && \
		!ft_strncmp(">", h->next->token, 2))
		{
			delete_node(list, h->next->pos);
			tmp = h->token;
			h->token = ft_strdup(">>");
			free(tmp);
		}
		else
			h = h->next;
	}
}

void	free_token(t_tokens **list)
{
	t_tokens	*head;

	head = *list;
	while (head)
	{
		delete_node(list, head->pos);
		head = head->next;
	}
	free(*list);
}

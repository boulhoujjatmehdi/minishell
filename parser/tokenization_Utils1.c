/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_Utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:53:58 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 20:03:50 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

void	replace_red(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<')
			s[i] = 3;
		if (s[i] == '>')
			s[i] = 4;
		i++;
	}
}

int	check(t_var *var, t_tokens *current)
{
	while (current->prev)
	{
		if (current->prev->token_type == 4)
		{
			var->i = 4;
			var->j = 4;
			var->k = 4;
		}
		if (current->prev->token_type == var->i || \
		current->prev->token_type == var->j || \
		current->prev->token_type == var->k)
			current = current->prev;
		else if ((ft_strncmp(current->prev->token, "<<", 3)))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	check_after_heredoc(t_tokens *node)
{
	t_tokens	*current;
	t_var		var;
	int			tmp;

	current = node;
	var.i = 4;
	var.j = 4;
	var.k = 4;
	if (current->prev && (current->prev->token_type == 4 || \
	current->prev->token_type == 7 || current->prev->token_type == 6 || \
	current->prev->token_type == 2))
	{
		tmp = current->prev->token_type;
		if (tmp != 4)
		{
			var.i = 6;
			var.j = 7;
			var.k = 2;
		}
		current = current->prev;
	}
	if (check(&var, current))
		return (1);
	return (0);
}

void	fill_empty(char *s)
{
	if (s[0] == '\0')
		s = ft_joinchar(s, 7);
	return ;
}

void	fill_qouted_empty(t_tokens *node)
{
	if (!ft_strncmp(node->token, "", 1))
	{
		if ((!(node->next) || (node->next && !check_if_connected(node->next))) \
		&& \
		(!(node->prev) || (node->prev && !check_if_connected(node->prev))))
		{
			node->token = ft_joinchar(node->token, 6);
		}
	}
}

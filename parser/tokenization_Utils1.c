/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_Utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:53:58 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/12 18:58:21 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

extern int g_exit;

void	replace_red(char *s)
{
	int i;

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

int	check_after_heredoc(t_tokens *node)
{
	t_tokens	*current;
	int			key1;
	int			key2;
	int			tmp;

	current = node;
	key1 = 4;
	key2 = 4;
	if (current->prev && (current->prev->token_type == 4 || current->prev->token_type == 7 || current->prev->token_type == 6))
	{
		tmp = current->prev->token_type;
		if (tmp != 4)
		{
			key1 = 6;
			key2 = 7;
		}
		current = current->prev;
	}
	while (current->prev)
	{
		if (current->prev->token_type == 4)
		{
			key1 = 4;
			key2 = 4;
		}
		if (current->prev->token_type == key1 || current->prev->token_type == key2)
		{
			current = current->prev;
		}
		else if ((ft_strncmp(current->prev->token, "<<", 3)))
			return (0);
		else 
			return (1);
	}
	return (0);
}

void	check_env(t_tokens **list, t_list **env)
{
	char		*tmp;
	int			l;
	t_tokens 	*head;

	head = *list;
	while (head)
	{
		if (head->token_type == 6)
		{
			tmp = head->token;
			head->token = ft_strtrim(head->token, "\"");
			replace_red(head->token);
			free(tmp);
			if (!check_after_heredoc(head))
				head->token = swap_env(head->token, head, env);
		}
		else if (head->token_type == 7)
		{
			tmp = head->token;
			head->token = ft_strtrim(head->token, "\'");
			replace_red(head->token);
			free(tmp);
		}
		else if (head->token_type == 5)
		{
			if (!check_after_heredoc(head))
				head->token = swap_env(head->token, head, env);
			replace_red(head->token);
		}
		head = head->next;
	}
}
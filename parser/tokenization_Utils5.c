/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_Utils5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:25:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 19:26:56 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

void	d_quotes(t_tokens *head, t_list	**env)
{
	char	*tmp;

	tmp = head->token;
	head->token = ft_strtrim(head->token, "\"");
	replace_red(head->token);
	free(tmp);
	if (!check_after_heredoc(head))
		head->token = swap_env(head->token, head, env);
	fill_qouted_empty(head);
}

void	check_env(t_tokens **list, t_list **env)
{
	char		*tmp;
	t_tokens	*head;

	head = *list;
	while (head)
	{
		if (head->token_type == 6)
			d_quotes(head, env);
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

char	*ft_replace(t_tokens *node, char *from, int *l, t_list **env)
{
	char	*new;
	char	*env1;
	int		i;

	i = 1;
	*l = 0;
	if (from[i] == '\0' && \
	((!node->next) || (node->next && node->next->token_type == 4)))
	{
		*l = 1;
		return (ft_strdup(from));
	}
	while (from[i] && \
	(ft_isalnum(from[i]) || from[i] == '_' || from[1] == '?' || from[1] == '@'))
	{
		i++;
		if (from[1] == '?' || from[1] == '@' || ft_isdigit(from[1]))
			break ;
	}
	*l = i;
	env1 = ft_substr(from, 1, i - 1);
	if (env1[0] == '?')
		return (ft_exit_status(env1));
	new = get_assos(env1, env, node->token_type);
	return (new);
}

char	*swap_env(char *str, t_tokens *node, t_list **env)
{
	t_var	var;
	char	*tmp;

	var.new = (char *)ft_calloc(sizeof(char), 1);
	if (!var.new)
		return (0);
	var.i = 0;
	var.j = 0;
	while (str[var.i])
	{
		if (str[var.i] == '$')
		{
			tmp = ft_replace(node, &str[var.i], &var.j, env);
			var.new = ft_strjoin2(var.new, tmp);
			free(tmp);
			var.i += var.j;
		}
		else
		{
			var.new = ft_joinchar(var.new, str[var.i]);
			var.i++;
		}
	}
	free(str);
	return (var.new);
}

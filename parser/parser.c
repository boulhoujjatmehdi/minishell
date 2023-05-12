/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/12 20:05:21 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

extern int g_exit;

void print(t_tokens **list)
{
	t_tokens *head;
	head = *list;
	while (head)
	{
		printf("token     =     -%s-,  token_type %d,    position %d, len %lu\n", head->token, head->token_type, head->pos, strlen(head->token));
		head = head->next;
	}
}

void print2(t_cmd **list)
{
	t_cmd *head;
	head = *list;
	char **new;
	new = ft_split(head->str, 1);
	while (*new)
	{
		printf("cmd_path  =     -%s-,              cmd_args = :%s:\n", head->cmd_path, *new);
		new++;
	}
}


t_cmd *main_function(int ac, char *str, t_list **env)
{
	t_tokens	*info;
	t_cmd		*head;
	char *s;

	info = NULL;
	head = NULL;
	head = (t_cmd *)calloc(sizeof(t_cmd), 1);
	s = my_strtok(&str);
	while (s)
	{
		if (!ft_strncmp(s, "SSYY", ft_strlen(s) + 1))
		{
			free_token(&info);
			return (NULL);
		}
		addback(&info, lstnew(s));
		s = my_strtok(&str);
	}
	check_double_red(&info);
	check_env(&info, env);
	adjest(&info);
	del_space(&info);
	del_emptyyy(&info);
	if (syntax_error(&info) == 1)
	{
		free_token(&info);
		return (NULL);
	}
	listing_cmd(&info, &head);
	free_token(&info);
	return (head);
}

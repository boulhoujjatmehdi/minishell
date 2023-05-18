/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 20:23:44 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

int	check_if_connected(t_tokens *node)
{
	if (node->token_type == 2 || node->token_type == 5 || \
node->token_type == 6 || node->token_type == 7)
		return (1);
	return (0);
}

void	fill_alone_empty(t_tokens **list)
{
	t_tokens	*head;

	head = *list;
	while (head)
	{
		if (!ft_strncmp(head->token, "\'\'", 3) || \
!ft_strncmp(head->token, "\"\"", 3))
		{
			if ((!(head->next) || \
	(head->next && !check_if_connected(head->next))) && \
	(!(head->prev) || (head->prev && !check_if_connected(head->prev))))
			{
				head->token = ft_joinchar(head->token, 6);
			}
		}
		head = head->next;
	}
}

int	fiil_tokenll(char *str, t_tokens **info)
{
	char	*s;

	s = my_strtok(&str);
	while (s)
	{
		if (!ft_strncmp(s, "SSYY", ft_strlen(s) + 1))
		{
			free(s);
			free_token(info);
			return (1);
		}
		addback(info, lstnew(s));
		s = my_strtok(&str);
	}
	return (0);
}

t_cmd	*main_function(int ac, char *str, t_list **env)
{
	t_tokens	*info;
	t_cmd		*head;

	info = NULL;
	if (fiil_tokenll(str, &info))
		return (NULL);
	head = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	give_pos(&info);
	check_double_red(&info);
	fill_alone_empty(&info);
	check_env(&info, env);
	adjest(&info);
	del_space(&info);
	del_emptyyy(&info);
	if (syntax_error(&info) == 1)
	{
		free(head);
		free_token(&info);
		return (NULL);
	}
	listing_cmd(&info, &head);
	free_token(&info);
	return (head);
}

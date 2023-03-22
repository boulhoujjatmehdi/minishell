/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/03/17 15:42:21 by fhihi            ###   ########.fr       */
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
	new_t_list->next = NULL;
	return (new_t_list);
}

int	token_type(char *s)
{
	if (!ft_strncmp("|", s, 2))
		return(PIPE_TOKEN);
	else if (!ft_strncmp(">", s, 2) || !ft_strncmp("<", s, 2) || !ft_strncmp(">>", s, 3) || !ft_strncmp("<<", s, 3))
		return (RED_TOKEN);
	else if (!ft_strncmp(" ", s, 2))
		return(SPACE_TOKEN);
	else 
		return(ARG_TOKEN);
}

void	lexer(t_tokens *tok, char *str)
{
	char **new;
	t_tokens *head;
	int i = 0;
	head = tok;
	new = ft_split(str, ' ');
	while (new[i])
	{
		head->token = lstnew(new[i]);
	}
}

int main(int ac, char **av, char **env)
{
	t_tokens	*info;
	info = (t_tokens *)malloc(sizeof(t_tokens));
	lexer(info, av[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/03/28 20:52:29 by fhihi            ###   ########.fr       */
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
	new_t_list->size++;
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

int main(int ac, char **av, char **env)
{
	t_tokens	*info, *head;
	char *s;
	
	s = my_strtok(&av[1]);
	info = (t_tokens *)malloc(sizeof(t_tokens));
	if (!info)
		return 0;
	info->size = 0;
	while (s)
	{
		addback(&info, lstnew(s));
		s = my_strtok(&av[1]);
	}
	while (info)
	{
		printf("token type === %d -- :%s:\n", info->token_type, info->token);
		info = info->next;
	}
	return (0);
}

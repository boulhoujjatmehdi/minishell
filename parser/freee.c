/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freee.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:24:53 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 16:17:33 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

void	free_2darrary(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	if (arr)
		free(arr);
}

void	free_lincked_list(t_list *head)
{
	while (head)
	{
		ft_lstdelone(head, &free);
		head = head->next;
	}
}

void	free_str(char *s)
{
	if (s)
		free(s);
	s = NULL;
}

void	free_cmdlist(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		free_str(head->str);
		free_str(head->exit_msg);
		free_str(head->cmd_path);
		free_2darrary(head->cmd_args);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

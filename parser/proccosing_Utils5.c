/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing_Utils5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:28:37 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/19 15:20:59 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

void	return_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 7)
			s[i] = ' ';
		i++;
	}
	return ;
}

void	tmp_free(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
	free(s);
}

char	*triiim_char(char *name, char c)
{
	char	*tmp;
	char	*new;

	if (!name)
		return (NULL);
	tmp = ft_joinchar(ft_strdup(""), c);
	new = ft_my_strtrim(name, tmp);
	free(tmp);
	free(name);
	return (new);
}

int	has_space(char *name)
{
	char	**test;
	char	*tmp;
	int		count;

	if (!name[0])
		return (0);
	count = 0;
	test = ft_my_split(name, 7);
	while (test && test[count])
		count++;
	if (count > 1 || !(*test))
	{
		tmp_free(test);
		return (1);
	}
	tmp_free(test);
	return (0);
}

void	deletelastnode(t_list **list)
{
	t_list	*head;

	head = *list;
	if (*list == NULL)
		return ;
	if ((*list)->next == NULL)
	{
		free((*list)->content);
		free(*list);
		*list = NULL;
		return ;
	}
	while (head->next->next != NULL)
		head = head->next;
	free(head->next->content);
	free(head->next);
	head->next = NULL;
	return ;
}

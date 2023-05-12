/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LList2_Utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:40:29 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/12 20:04:35 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

size_t	ft_strlen2(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	size_t	j2;
	char	*s;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen2(s1) + ft_strlen2(s2);
	s = (char *)malloc((size + 1) * sizeof(char));
	if (!s)
		return (0);
	i = 0;
	j = 0;
	j2 = 0;
	while (s1 && s1[j])
		s[i++] = s1[j++];
	while (s2 && s2[j2])
		s[i++] = s2[j2++];
	s[i] = '\0';
	free(s1);
	return (s);
}

void	give_key(t_cmd **list)
{
	t_cmd *head;
	int i;
	
	i = 1;
	head = *list;
	while (head)
	{
		head->key = i;
		i++;
		head = head->next;
	}
}

void	free_cmd(t_cmd **list)
{
	t_cmd *head;

	give_key(list);
	head = *list;
	while (head)
	{
		delete_node2(list, head->key);
		head = head->next;
	}
	// *list = NULL;
}

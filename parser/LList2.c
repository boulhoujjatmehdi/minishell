/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LList2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:54:42 by fhihi             #+#    #+#             */
/*   Updated: 2023/04/11 20:16:59 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

t_cmd	*lstnew2(void *content)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->str = content;
	new->cmd_args = NULL;
	new->cmd_path = NULL;
	new->str = NULL;
	new->next = NULL;
	return (new);
}

void	addback2(t_cmd **list, t_cmd *new)
{
	t_cmd	*temp;

	if (!(*list))
		*list = new;
	else
	{
		temp = lstlast2(*list);
		temp->next = new;
	}
}

t_cmd	*lstlast2(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	delete_node2(t_cmd **head, int key)
{
    t_cmd *temp;
    t_cmd *current  = *head;
	int i;

    if((*head)->key == key)
    {
        temp = *head;    
        *head = (*head)->next;
		// free(temp->tmp);
		free(temp->str);
		free(temp->cmd_path);
		i = 0;
		while (temp->cmd_args && temp->cmd_args[i])
			free(temp->cmd_args[i++]);
        free(temp);
	}
    else
    {
        while(current->next)
        {
            if(current->next->key == key)
            {
                temp = current->next;
                current->next = current->next->next;
        		*head = (*head)->next;
				// free(temp->tmp);
				free(temp->str);
				free(temp->cmd_path);
				i = 0;
				while (temp->cmd_args && temp->cmd_args[i])
					free(temp->cmd_args[i++]);
        		free(temp);
                break;
            }
            else
                current = current->next;
        }
    }
}

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
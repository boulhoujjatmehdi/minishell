/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LList1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:54:45 by fhihi             #+#    #+#             */
/*   Updated: 2023/04/06 21:53:05 by fhihi            ###   ########.fr       */
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

//this function goes through a the tokens lincked list and indexs it
void	give_pos(t_tokens **list)
{
	t_tokens *head;
	int i;
	
	i = 0;
	head = *list;
	while (head)
	{
		head->pos = i;
		i++;
		head = head->next;
	}
}

void	delete_node(t_tokens **head, int key)
{
    t_tokens *temp;
    t_tokens *current  = *head;

    if((*head)->pos == key)
    {
        temp = *head;    
        *head = (*head)->next;
        free(temp);
	}
    else
    {
        while(current->next)
        {
            if(current->next->pos == key)
            {
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                break;
            }
            else
                current = current->next;
        }
    }
}

//this fucntion removes space tokens from the Llist
void	del_space_empty(t_tokens **list)
{
	t_tokens *head;
	
	head = *list;
	while (head)
	{
		if (head->token_type == 4 || !ft_strncmp(head->token, "", 1))
		{
			printf("here---:%s:-- %d\n", head->token, head->pos);
			delete_node(list, head->pos);
			head = head->next;
		}
		else
			head = head->next;
	}
}

void	syntax_error(t_tokens **list)
{
	t_tokens *head;
	
	head = *list;
	give_pos(list);
	while (head->next)
	{
		// if (head->token_type == 1 && !head->next)  to be handled later 
		if (head->token_type == 1 && head->pos == 0)
		{
			printf("minishell: syntax error near unexpected token `|'\n"); // to be changed to stderr
			exit(0);
		}
		if (head->token_type == 1 && head->next->token_type == 1)
		{
			printf("minishell: syntax error near unexpected token `|'\n"); // to be changed to stderr
			exit(0);			
		}
		if (head->token_type == 1 && head->next->token_type == 3)
		{
			printf("minishell: syntax error near unexpected token `|'\n"); // to be changed to stderr
			exit(0);			
		}
		if (head->token_type == 3 && !head->next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n"); // to be changed to stderr
			exit(0);			
		}
		head = head->next;
	}
	
}

//this function checks my token Llist for the single and double redirections
void	check_double_red(t_tokens **list)
{
	t_tokens *head;

	head = *list;
	while (head->next)
	{
		if (!ft_strncmp("<", head->token, 2) && !ft_strncmp("<", head->next->token, 2))
		{
			delete_node(list, head->next->pos);
			head->token = ft_strdup("<<");
		}
		else if (!ft_strncmp(">", head->token, 2) && !ft_strncmp(">", head->next->token, 2))
		{
			delete_node(list, head->next->pos);
			head->token = ft_strdup(">>");
		}
		else
			head = head->next;
	}
}
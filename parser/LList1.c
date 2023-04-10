/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LList1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:54:45 by fhihi             #+#    #+#             */
/*   Updated: 2023/04/10 17:39:49 by fhihi            ###   ########.fr       */
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
	
	i = 1;
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
		free(temp->token);
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
				free(temp->token);
                free(temp);
                break;
            }
            else
                current = current->next;
        }
    }
}

//this fucntion removes space tokens from the Llist
void	del_space(t_tokens **list)
{
	t_tokens *head;
	
	head = *list;
	give_pos(list);
	while (head)
	{
		if (head->token_type == 4)
		{
			delete_node(list, head->pos);
			head = head->next;
		}
		else
			head = head->next;
	}
}

//this fucntion removes empty tokens from the Llist that need to be removed
void	del_empty(t_tokens **list)
{
	t_tokens *head;
	
	head = *list;
	give_pos(list);
	while (head->next)
	{
		if (!ft_strncmp(head->token, "", 1) && head->next->token_type == 2)
		{
			delete_node(list, head->pos);
			head= head->next;
		}
		else
			head = head->next;
	}
}

void	adjest(t_tokens **list)
{
	t_tokens *head;
	int tmp1;
	char	*tmp;

	head = *list;
	while (head->next)
	{
		// puts(head->token);
		if (head->token_type == 2 && head->next->token_type == 2)
		{
			tmp = ft_strdup(head->token);
			head->next->token = ft_strjoin2(tmp, head->next->token);
			tmp1 = head->pos;
			head = head->next;
			delete_node(list, tmp1);
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
		if (head->token_type == 1 && head->pos == 1)
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
	char *tmp;

	head = *list;
	give_pos(list);
	while (head->next)
	{
		if (!ft_strncmp("<", head->token, 2) && !ft_strncmp("<", head->next->token, 2))
		{
			delete_node(list, head->next->pos);
			tmp = head->token;
			head->token = ft_strdup("<<");
			free(tmp);
		}
		else if (!ft_strncmp(">", head->token, 2) && !ft_strncmp(">", head->next->token, 2))
		{
			delete_node(list, head->next->pos);
			tmp = head->token;
			head->token = ft_strdup(">>");
			free(tmp);
		}
		else
			head = head->next;
	}
}

void	free_token(t_tokens **list)
{
	t_tokens *head;

	head = *list;
	while (head)
	{
		delete_node(list, head->pos);
		head = head->next;
	}
	// *list = NULL;
}
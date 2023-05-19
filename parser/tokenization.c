/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:53:47 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/19 15:34:34 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

int	token_type(char *s)
{
	if (!ft_strncmp("\'", s, 1))
		return (QUOTE);
	else if (!ft_strncmp("\"", s, 1))
		return (DQUOTE);
	else if (!ft_strncmp("$", s, 1))
		return (ENV_VAR);
	else if (!ft_strncmp("|", s, 2))
		return (PIPE_TOKEN);
	else if (!ft_strncmp(">", s, 2) || !ft_strncmp("<", s, 2) || \
	!ft_strncmp(">>", s, 3) || !ft_strncmp("<<", s, 3))
		return (RED_TOKEN);
	else if (!ft_strncmp(" ", s, 2))
		return (SPACE_TOKEN);
	else
		return (ARG_TOKEN);
}

//this function puts together my commend table by spliting
// the tokens with the pipe token and
// puting them together into a string ready to be processed 
void	listing_cmd(t_tokens **list1, t_cmd **list2)
{
	t_tokens	*head1;
	t_cmd		*head2;

	head2 = *list2;
	head1 = *list1;
	while (head1)
	{
		if (head1->token_type == 1)
		{
			addback2(list2, lstnew2(NULL));
			head1 = head1->next;
			head2 = head2->next;
		}
		else
		{
			head2->str = ft_strjoin2(head2->str, head1->token);
			head2->str = ft_joinchar(head2->str, 1);
			head1 = head1->next;
		}
	}
}

//this fucntion removes space tokens from the Llist
void	del_space(t_tokens **list)
{
	t_tokens	*head;

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

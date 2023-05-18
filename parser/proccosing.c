/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:44:44 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 19:01:23 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

void	add_if_separeted(t_list **list)
{
	t_list	*head;
	char	**tmp;
	int		i;

	head = ft_lstlast(*list);
	tmp = ft_split(head->content, 7);
	i = 0;
	if (tmp && tmp[i])
		deletelastnode(list);
	while (tmp && tmp[i])
	{
		ft_lstadd_back(list, ft_lstnew(ft_my_strdup(tmp[i])));
		i++;
	}
	free_2darrary(tmp);
	return ;
}

void	cmd_opt_ll(t_list **list, char *s)
{
	char	**tmp;
	t_list	*head;
	int		i;

	tmp = ft_my_split(s, 1);
	i = 0;
	while (tmp[i])
	{
		return_red(tmp[i]);
		if (tmp[i][0] == 2 && tmp[i][1] == 0)
			ft_lstadd_back(list, ft_lstnew(NULL));
		else
			ft_lstadd_back(list, ft_lstnew(ft_my_strdup(tmp[i])));
		add_if_separeted(list);
		i++;
	}
	free_2darrary(tmp);
}

char	**fill_opts(t_list *head)
{
	char	**new;
	int		i;

	i = ft_lstsize(head);
	new = (char **)malloc((sizeof(char *) * i) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (head)
	{
		if (head->content != NULL)
		{
			new[i] = ft_my_strdup(head->content);
			new[i] = remove_non_printble(new[i]);
			if ((new[i][0] == 2 && new[i][1] == 2 && new[i][2] == '\0') || \
			new[i][0] == 6)
				new[i][0] = 0;
			i++;
		}
		head = head->next;
	}
	new[i] = NULL;
	return (new);
}

char	**get_cmd_opt(char *s)
{
	char	**new;
	t_list	*list;
	t_list	*head;

	if (!s && !s[0])
		return (NULL);
	list = NULL;
	cmd_opt_ll(&list, s);
	head = list;
	new = fill_opts(head);
	free_lincked_list(list);
	return (new);
}

//this function gets the string and processes it ato get cmd, inputfile
// to read from and output file to write to and so on
void	proccesing_cmd(t_cmd *node, char **env)
{
	int		fd;
	char	*cmd;

	cmd = NULL;
	node->infile = input_file(node);
	if (node->infile == -1)
		return ;
	node->outfile = output_file(node);
	if (node->outfile == -1)
		return ;
	node->cmd_args = get_cmd_opt(node->str);
	if (node->cmd_args != NULL && (node->cmd_args)[0] != NULL)
		cmd = ft_strdup(node->cmd_args[0]);
	node->cmd_path = ft_cmd_path(cmd, env, node);
}

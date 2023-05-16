/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:44:44 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/17 00:25:54 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

extern int g_exit;


int	file_errors(char *name, int key, t_cmd *node)
{
	if (key == -2)
	{
		ft_ambiguous(1, node);
		return (1);
	}
	if (access(name, F_OK) == -1)
		ft_no_file_diractory(name, 1, node);
	else if (access(name, R_OK) == -1 && key == 0)
		ft_permision(name, 1, node);
	else if (access(name, W_OK) == -1 && key == 1)
		ft_permision(name, 1, node);
	return (0);
}

void	return_red(char *s)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] == 3)
			s[i] = '<';
		if (s[i] == 4)
			s[i] = '>';
		i++;
	}
}

char *remove_non_printble(char *s)
{
	int i;
	int len;
	char *new;
	
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		if (s[i] != 5 && s[i] != 7)
			new[i] = s[i];
		i++;
	}
	free(s);
	return (new);
}


void deleteLastNode(t_list **list) {
    t_list *head = *list;
	
    if (*list == NULL)
        return;

    // If the linked list has only one node
    if ((*list)->next == NULL)
	{
        free(*list);
        *list = NULL;
        return;
    }
    // Traverse to the second last node
    while (head->next->next != NULL)
        head = head->next;
    free(head->next);
    head->next = NULL;
	return ;
}

void	print_str(char *s)
{
	int i;

	i = 0;
	puts(s);
	while (s[i])
		printf("%d - ", s[i++]);
	printf("\n");
	return ;
}

void	add_if_separeted(t_list **list)
{
	t_list *head;
	char **tmp;
	int i;
	
	head = ft_lstlast(*list);
	tmp = ft_split(head->content, 7);
	i = 0;
	if (tmp && tmp[i])
	{
		deleteLastNode(list);
	}
	while (tmp && tmp[i])
	{
		ft_lstadd_back(list, ft_lstnew(ft_my_strdup(tmp[i])));
		i++;
	}
	return ;
}

void	cmd_opt_ll(t_list **list, char *s)
{
	char **tmp;
	t_list *head;
	int i;
	
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
}

char	**get_cmd_opt(char *s)
{
	char **new;
	t_list *list;
	t_list *head;
	int i;
	
	if (!s && !s[0])
		return (NULL);
	list = NULL;
	cmd_opt_ll(&list, s);
	i = ft_lstsize(list);
	new = (char **)malloc((sizeof(char *) * i) + 1);
	if (!new)
		return (NULL);
	head = list;
	i = 0;
	while (head)
	{
		if (head->content != NULL)
		{
			new[i] = ft_my_strdup(head->content);
			if ((new[i][0] == 2 && new[i][1] == 2 && new[i][2] == '\0') ||\
			(new[i][ft_strlen(new[i]) - 1] == 5 && new[i][ft_strlen(new[i])] == 0) || new[i][0] == 6)
				new[i][ft_strlen(new[i]) - 1] = 0;
			new[i] = remove_non_printble(new[i]);
			i++;
		}
		head = head->next;
	}
	new[i] = NULL;
	return new;	
}

//this function gets the string and processes it ato get cmd, inputfile
// to read from and output file to write to and so on
void	proccesing_cmd(t_cmd *node, char **env)
{
	int fd;
	char	*cmd;

	cmd = NULL;
	node->infile = input_file(node);
	if (node->infile == -1)
		return ;
	node->outfile = output_file(node);
	if (node->outfile == -1)
		return ;
	node->cmd_args = get_cmd_opt(node->str);
	if (node->cmd_args != NULL)
		cmd = ft_strdup(node->cmd_args[0]);
	node->cmd_path = ft_cmd_path(cmd, env, node);
}

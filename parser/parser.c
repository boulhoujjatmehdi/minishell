/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/04/07 20:06:57 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

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

//this function puts toghater my commend table by spliting the tokens with the pipe token and
// puting them toghater into a string ready to be processed 
void	listing_cmd(t_tokens **list1, t_cmd **list2)
{
	t_tokens	*head1;
	t_cmd		*head2;
	char *tmp;

	head1 = *list1;
	head2 = *list2;	
	while (head1)
	{
		if (!ft_strncmp(head1->token, "", 1))
		{
			tmp = head1->token;
			head1->token = ft_strdup("|");
			free(tmp);
		}
		if (head1->token_type == 1)
		{
			addback2(list2, lstnew2(NULL));
			head1 = head1->next;
			head2 = head2->next;
		}
		else
		{
		head2->str = ft_strjoin2(head2->str, head1->token);
		head2->str = ft_strjoin2(head2->str, ":");
		head1 = head1->next;
		}
	}
}

char	*ft_strchr1(char *s, int c, int c1)
{
	int				i;
	unsigned char	cc;

	cc = c;
	i = 0;
	while (s[i] != cc)
	{
		if (!s[i])
			return (0);
		i++;
	}
	s[i] = c1;
	i+= 1;
	return ((char *)(s + i));
}

char	*get_filename(char *s, int c, int c1)
{
	char *new;
	int i;
	
	i = 0;
	new = (char *)malloc(sizeof(s));
	if (!new)
		return NULL;
	while (s[i] != c)
	{
		new[i] = s[i];
		s[i] = c1;
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*her_doc(char *s)
{
	char *new;
	char *ret;
	new = readline(">");
	while (ft_strncmp(new, s, ft_strlen(s)))
		ret = new;
	return (ret);
}

int	input_file(char *s, char **her_doc)
{
	int i;
	int fd;
	char *name;
	char *tmp;

	i = 0;
	if (!s)
		return(0);
	name = ft_strchr1(s, '<', ':');
	while (name)
	{
		if (name && name[0] == '<')
		{
			name+= 2;
			tmp = ft_strdup(get_filename(name , ':', ':'));
			*her_doc = ft_strjoin2(*her_doc, tmp);
			*her_doc = ft_strjoin2(*her_doc, ":");
			return 2;
		}
		else if (name && name[0] == ':')
		{
			name++;
			name = get_filename(name, ':', ':');
			if (!name)
				return (0);
			fd = open(name, O_RDONLY);
			return fd;
		}
		name = ft_strchr1(s, '<', ':');
	}
	return (0);
}

int output_file(char *s)
{
	int i;
	int fd;
	char *name;

	i = 0;
	if (!s)
		return (1);
	name = ft_strchr1(s, '>', ':');
	if (name)
	{		if (name && name[0] == '>')
		{
			name = ft_strchr1(s, '>', ':');
			name++;
			name = get_filename(name, ':', ':');
			fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			return fd;
		}
		else if (name && name[0] != '>')
		{	
			name++;
			name = get_filename(name, ':', ':');
			fd = open(name, O_CREAT | O_WRONLY, 0644);
			return fd;
		}
	}
		return (1);
}

char	**get_cmd_opt(char *s)
{
	char **new;
	new = ft_split(s, ':');
	return new;	
}

//this function gets the string and processes it ato get cmd, inputfile
// to read from and output file to write to and so on
void	proccesing_cmd(t_cmd **list, char **env)
{
	t_cmd *head;
	int fd;
	char	*cmd;
	
	head = *list;
	while (head)
	{
		cmd = NULL;
		head->infile = input_file(head->str, &head->her_doc);
		while((fd = input_file(head->str, &head->her_doc)))
			head->infile = fd;
		head->outfile = output_file(head->str);
		while((fd = output_file(head->str)) != 1)
			head->outfile = fd;
		head->cmd_args = get_cmd_opt(head->str);
		if (head->cmd_args != NULL)
			cmd = ft_strdup(head->cmd_args[0]);
		head->cmd_path = ft_cmd_path(cmd, env);
		head = head->next;
	}
}

void print(t_tokens **list)
{
	t_tokens *head;
	head = *list;
	while (head)
	{
		printf("token = -%s-\n", head->token);
		head = head->next;
	}
}

int main_function(int ac, char **av, char **env)
{
	t_tokens	*info;
	t_cmd		*head;
	char *s;

	info = NULL;
	head = NULL;
	head = (t_cmd *)calloc(sizeof(t_cmd), 1);
	s = my_strtok(&av[1]);
	while (s)
	{
		// printf("-%s-\n", s);
		addback(&info, lstnew(s));
		s = my_strtok(&av[1]);
	}
	check_double_red(&info);
	del_empty(&info);
	adjest(&info);
	// print(&info);
	del_space(&info);
	syntax_error(&info);
	listing_cmd(&info, &head); 
	proccesing_cmd(&head, env);
	while (head)
	{
		printf("**********************************************\nstr === :%s:\ninfile %d --- outfile %d -  cmd :%s:, here_doc --> %s\n", head->str, head->infile, head->outfile, head->cmd_path, head->her_doc);
		int i = 0;
		while (head->cmd_args && head->cmd_args[i])
			printf("opts == %s\n", head->cmd_args[i++]);
		head = head->next;
	}
	return (0);
}
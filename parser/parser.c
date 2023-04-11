/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/04/11 21:13:20 by eboulhou         ###   ########.fr       */
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

//this function puts together my commend table by spliting the tokens with the pipe token and
// puting them together into a string ready to be processed 
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
			// head2->tmp = ft_strdup(head2->str);
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

char	*ft_strchr2(char *s, int c, int c1)
{
	int	i;
	unsigned char	cc;

	cc = c;
	i = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] == cc && s[i + 1] && s[i + 1] == cc)
		{
			s[i] = c1;
			s[i + 1] = c1;
			i+= 2;
			return ((char *)s + i);
		}
		i++;
	}
	return (0);
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


int	ft_strrchr1(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char )c)
			return (i);
		i--;
	}
	return (0);
}

int	get_here_doc(char *name)
{
	int fd, len;
	char *str;

	len = ft_strlen(name);
	fd = open(".tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	str = readline(">");
	while(ft_strncmp(name, str, len))
	{
		ft_putstr_fd(str,fd );
		ft_putstr_fd("\n" , fd);
		str =readline(">");
	}
	close(fd);
	return (fd);
}
void	file_errors(char *name, int key)
{
	if (access(name, F_OK) == -1)
		ft_no_file_diractory(name, 1);
	if (access(name, R_OK) == -1 && key == 0)
		ft_permision(name, 1);
	if (access(name, W_OK) == -1 && key == 1)
		ft_permision(name, 1);
}

int	input_file(char *s)
{
	int i;
	int fd1, fd2, t;
	char *name;
	char *tmp;
	int	last;

	i = 0;
	t = 0;
	fd1 = 0;
	fd2 = 0;
	if (!s)
		return(0);
	last = ft_strrchr1(s, '<');
	if (s[last - 1] == '<')
		t = 1;
	name = ft_strchr2(s, '<', ':');
	while (name)
	{
		if (fd2 != 0)
			close(fd2);
		name++;
		name = get_filename(name , ':', ':');
		fd2 = get_here_doc(name);
		free (name);
		fd2 = open(".tmp.txt", O_RDONLY);
		name = ft_strchr2(s, '<', ':');
	}
	name = ft_strchr1(s, '<', ':');
	while(name)
	{
		if (fd1 != 0)
			close(fd1);
		name++;
		name = get_filename(name, ':', ':');
		if (!name)
			return (0);
		fd1 = open(name, O_RDONLY);
		if (fd1 == -1)
			file_errors(name, 0);
		free (name);
		name = ft_strchr1(s, '<', ':');
	}
	if (t == 1)
		return (fd2);
	return (fd1);
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
	{
		if (name && name[0] == '>')
		{
			name = ft_strchr1(s, '>', ':');
			name++;
			name = get_filename(name, ':', ':');
			fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
				file_errors(name, 1);
			free (name);
			return fd;
		}
		else if (name && name[0] != '>')
		{	
			name++;
			name = get_filename(name, ':', ':');
			fd = open(name, O_CREAT | O_WRONLY, 0644);
			if (fd == -1)
				file_errors(name, 1);
			free (name);
			return fd;
		}
	}
	return (1);
}

char	**get_cmd_opt(char *s)
{
	char **new;
	// printf("str ===%s\n", s);
	new = ft_split(s, ':');
	return new;	
}

//this function gets the string and processes it ato get cmd, inputfile
// to read from and output file to write to and so on
void	proccesing_cmd(t_cmd *node, char **env)
{
	t_cmd *head;
	int fd;
	char	*cmd;

	head = node;
	cmd = NULL;
	head->infile = input_file(head->str);
	head->outfile = output_file(head->str);
	while((fd = output_file(head->str)) != 1)
	{
		close(head->outfile);
		head->outfile = fd;
	}
	head->cmd_args = get_cmd_opt(head->str);
	// printf("argss   %s\n", head->cmd_args[0]);
	if (*head->cmd_args != NULL)
		cmd = ft_strdup(head->cmd_args[0]);
	head->cmd_path = ft_cmd_path(cmd, env);
}

void print(t_tokens **list)
{
	t_tokens *head;
	head = *list;
	while (head)
	{
		printf("token = -%s-,  token_type %d\n", head->token, head->token_type);
		head = head->next;
	}
}

t_cmd *main_function(int ac, char *str, char **env)
{
	t_tokens	*info;
	t_cmd		*head;
	t_cmd *tmp;
	char *s;

	info = NULL;
	head = NULL;
	head = (t_cmd *)calloc(sizeof(t_cmd), 1);
	s = my_strtok( &str);
	while (s)
	{
		// printf("-%s-\n", s);
		addback(&info, lstnew(s));
		s = my_strtok(&str);
	}
	check_double_red(&info);
	del_empty(&info);
	adjest(&info);
	// print(&info);
	del_space(&info);
	syntax_error(&info);
	// puts("here");
	listing_cmd(&info, &head); 
	free_token(&info);
	tmp = head;
	return (head);
}
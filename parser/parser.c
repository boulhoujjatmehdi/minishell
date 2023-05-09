/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/09 16:20:06 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

extern int g_exit;

int	token_type(char *s)
{
	if (!ft_strncmp("\'", s, 1))
		return (QUOTE);
	else if (!ft_strncmp("\"", s, 1))
		return (DQUOTE);
	else if (!ft_strncmp("$", s, 1))
		return (ENV_VAR);
	else if (!ft_strncmp("|", s, 2))
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
			head1->token = ft_strdup("\\");
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
		head2->str = ft_joinchar(head2->str, 1);
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

	int pid = fork();
	if(pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		len = ft_strlen(name);
		fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		str = readline(">");
			while(ft_strncmp(name, str, len+1))
			{
				ft_putstr_fd(str,fd);
				ft_putstr_fd("\n", fd);
				str =readline(">");
			}
		close(fd);
		exit(0);
	}
	int status;
	waitpid(pid, &status, 0);
	if(status)
		return(-2);

	return (fd);
}
void	file_errors(char *name, int key, t_cmd *node)
{
	if (access(name, F_OK) == -1)
		ft_no_file_diractory(name, 1, node);
	else if (access(name, R_OK) == -1 && key == 0)
		ft_permision(name, 1, node);
	else if (access(name, W_OK) == -1 && key == 1)
		ft_permision(name, 1, node);

}

int	input_file(t_cmd *node)
{
	int i;
	int fd1, fd2, t;
	char *name;
	char *tmp;
	char *s;
	int	last;

	s = node->str;
	i = 0;
	t = 0;
	fd1 = 0;
	fd2 = 0;
	if (!s)
		return(0);
	last = ft_strrchr1(s, '<');
	if (s[last - 1] == '<')
		t = 1;
	name = ft_strchr2(s, '<', 1);
	while (name)
	{
		if (fd2 != 0)
			close(fd2);
		name++;
		name = get_filename(name , 1, 1);
		fd2 = get_here_doc(name);
		if(fd2 == -2)
		{
			node->ctr_c = 1;
		}
		free (name);
		fd2 = open(".tmp", O_RDONLY);
		name = ft_strchr2(s, '<', 1);
	}
	name = ft_strchr1(s, '<', 1);
	while(name)
	{
		if (fd1 != 0)
			close(fd1);
		name++;
		name = get_filename(name, 1, 1);
		if (!name)
			return (0);
		fd1 = open(name, O_RDONLY);
		if (fd1 == -1)
			file_errors(name, 0, node);
		free (name);
		name = ft_strchr1(s, '<', 1);
	}
	if (t == 1)
		return (fd2);
	return (fd1);
}

int output_file(t_cmd *node)
{
	int i;
	int fd;
	char *name;
	char *s;

	s = node->str;
	i = 0;
	if (!s)
		return (1);
	name = ft_strchr1(s, '>', 1);
	if (name)
	{
		if (name && name[0] == '>')
		{
			name = ft_strchr1(s, '>', 1);
			name++;
			name = get_filename(name, 1, 1);
			fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
				file_errors(name, 1, node);
			free (name);
			return fd;
		}
		else if (name && name[0] != '>')
		{	
			name++;
			name = get_filename(name, 1, 1);
			fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
				file_errors(name, 1, node);
			free (name);
			return fd;
		}
	}
	return (1);
}

char	**get_cmd_opt(char *s)
{
	char **new;
	new = ft_split(s, 1);
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
	node->outfile = output_file(node);
	while((fd = output_file(node)) != 1)
	{
		close(node->outfile);
		node->outfile = fd;
	}
	node->cmd_args = get_cmd_opt(node->str);
	if (*node->cmd_args != NULL)
		cmd = ft_strdup(node->cmd_args[0]);
	node->cmd_path = ft_cmd_path(cmd, env, node);
}

void print(t_tokens **list)
{
	t_tokens *head;
	head = *list;
	while (head)
	{
		printf("token     =     -%s-,  token_type %d,    position %d\n", head->token, head->token_type, head->pos);
		head = head->next;
	}
}

void print2(t_cmd **list)
{
	t_cmd *head;
	head = *list;
	char **new;
	new = ft_split(head->str, 1);
	while (*new)
	{
		printf("cmd_path  =     -%s-,              cmd_args = :%s:\n", head->cmd_path, *new);
		new++;
	}
}

int	env_len(char *s)
{
	int i;

	i = 0;
	while(s[i] != '=')
		i++;
	return (i + 1);
}

char	*env_var(char *s)
{
	int i;
	char *var;

	var = (char *)malloc(env_len(s) * sizeof(char ) + 1);
	if (!var)
		return NULL;
	i = 0;
	while(s[i] != '=')
	{
		var[i] = s[i];
		i++;	
	}
	var[i] = '\0';
	return (var);
}

char	*get_assos(char *s, t_list **env)
{
	int len;
	int size;
	char *new;
	char *tmp;
	t_list *head;

	head = *env;
	while (head->content)
	{
		tmp = env_var(head->content);
		if (ft_strncmp(s, tmp, ft_strlen(tmp) + 1) == 0)
			break ;
		free(tmp);
		head = head->next;
	}
	if (!head->content)
		return (ft_strdup(""));
	len = env_len(head->content);
	size = ft_strlen(head->content) - len;
	new = ft_substr(head->content, len, size);
	return (new);
}

char	*ft_replace(char *from, int *l, t_list **env)
{
	char	*new;
	char	*env1;
	int		i;

	i = 1;
	*l = 0;
	while (from[i] && (ft_isalnum(from[i]) || from[i] == '_'))
		i++;
	*l = i;
	env1 = ft_substr(from, 1, i - 1);
	new = get_assos(env1, env);
	return (new);
}

void	swap_env(t_tokens *node, t_list **env)
{
	int i;
	int l;
	char *new;
	char	*tmp;

	if (!(new = (char *)malloc(sizeof(char))))
		return ;
	i = 0;
	l = 0;
	new[0] = '\0';
	while(node->token[i])
	{
		if (node->token[i] == '$')
		{
			tmp = ft_replace(&node->token[i], &l, env);
			new = ft_strjoin2(new, tmp);
			i += l;
		}
		else
		{
			new = ft_joinchar(new, node->token[i]);
			i++;
		}
	}
	free(node->token);
	node->token = new;
}

void	check_env(t_tokens **list, t_list **env)
{
	char		*tmp;
	int l;
	t_tokens 	*head;

	head = *list;
	while (head)
	{
		if (head->token_type == 6)
		{
			tmp = head->token;
			head->token = ft_strtrim(head->token, "\"");
			free(tmp);
			swap_env(head, env);
		}
		else if (head->token_type == 5)
			swap_env(head, env);
		else if (head->token_type == 7)
		{
			tmp = head->token;
			head->token = ft_strtrim(head->token, "\'");
			free(tmp);
		}
		head = head->next;
	}
}

t_cmd *main_function(int ac, char *str, t_list **env)
{
	t_tokens	*info;
	t_cmd		*head;
	char *s;

	info = NULL;
	head = NULL;
	head = (t_cmd *)calloc(sizeof(t_cmd), 1);
	s = my_strtok(&str);
	while (s)
	{
		if (!ft_strncmp(s, "SSYY", ft_strlen(s) + 1))
		{
			free_token(&info);
			return (NULL);
		}
		addback(&info, lstnew(s));
		s = my_strtok(&str);
	}
	check_double_red(&info);
	check_env(&info, env);
	adjest(&info);
	del_space(&info);
	if (syntax_error(&info) == 1)
	{
		free_token(&info);
		return (NULL);
	}
	del_empty(&info);
	listing_cmd(&info, &head); 
	free_token(&info);
	return (head);
}

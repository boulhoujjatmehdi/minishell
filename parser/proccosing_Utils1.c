/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing_Utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:47:06 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/13 17:27:05 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

extern int g_exit;

char	*ft_rplc(char *from, int *l, t_list **env)
{
	char	*new;
	char	*env1;
	int		i;

	i = 1;
	*l = 0;
	while (from[i] && (ft_isalnum(from[i]) || from[i] == '_' || from[1] == '?'))
	{
		i++;
		if (from[1] == '?' || ft_isdigit(from[1]))
			break ;
	}
	*l = i;
	env1 = ft_substr(from, 1, i - 1);
	if (env1[0] == '?')
		return (ft_exit_status(env1));
	new = get_assos(env1, env);
	return (new);
}

char	*herdoc_env(char *str, t_list **env)
{
	int i;
	int l;
	char *new;
	char	*tmp;

	if (!(new = (char *)malloc(sizeof(char))))
		return 0;
	i = 0;
	l = 0;
	new[0] = '\0';
	while(str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_rplc(&str[i], &l, env);
			new = ft_strjoin2(new, tmp);
			i += l;
		}
		else
		{
			new = ft_joinchar(new, str[i]);
			i++;
		}
	}
	free(str);
	return (new);	
}

int	check_delimeter(char *s)
{
	int len;

	len = ft_strlen(s) - 1;
	if (s[len] == 5)
	{
		s[len] = 0;
		return (1);
	}
	return (0);
}

int	get_here_doc(char *name, t_list **env)
{
	int fd, len;
	int t;
	char *str;

	int pid = fork();
	if(pid == 0)
	{
		t = check_delimeter(name);
		signal(SIGINT, SIG_DFL);
		len = ft_strlen(name);
		fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		str = readline(">");
			while(ft_strncmp(name, str, len))
			{
				if (!t)
					str = herdoc_env(str, env);
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

int procces_her_doc(char *s, t_cmd *node)
{
	char *name;
	int fd;

	fd = 0;
	name = ft_strchr2(s, '<', 1);
	while (name)
	{
		if (fd != 0)
			close(fd);
		name++;
		name = get_filename(name , 1, 1);
		fd = get_here_doc(name, node->env);
		if(fd == -2)
			node->ctr_c = 1;
		free (name);
		fd = open(".tmp", O_RDONLY);
		name = ft_strchr2(s, '<', 1);
	}
	return (fd);
}

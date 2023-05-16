/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing_Utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:47:02 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/16 22:10:50 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

extern int g_exit;

void	return_space(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 7)
			s[i] = ' ';
		i++;
	}
	return ;
}

void	tmp_free(char **s)
{
	int i;

	if (!s)
		return ;

	i = 0;
	while(s[i])
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
	free(s);
}

char	*triiim_char(char *name, char c)
{
	char	*tmp;
	char	*new;

	if (!name)
		return (NULL);
	tmp = ft_joinchar(ft_strdup(""), c);
	new = ft_my_strtrim(name, tmp);
	free(tmp);
	free(name);
	return (new);
}

int	has_space(char *name)
{
	char **test;
	char *tmp;
	int count;

	if (!name[0])
		return (0);
	count = 0;
	// name = ft_strdup(name);
	test = ft_my_split(name, 7);
	while (test && test[count])
		count++;
	if (count > 1 || !(*test))
	{
		tmp_free(test);
		return (1);
	}
	tmp_free(test);
	return (0);
}

int procces_readfiles(char *s, t_cmd *node)
{
	char *name;
	int fd;
	
	fd = 0;
	name = ft_strchr1(s, '<', 1);
	while(name)
	{
		if (fd != 0)
			close(fd);
		name++;
		name = get_filename(name, 1, 1);
		if (!name)
			return (0);
		if (name[ft_strlen(name) - 1] == 5)
			name[ft_strlen(name) - 1] = 0;
		if ((name[0] == 2 && name[1] == '\0') || has_space(name))
		{
			if (file_errors(name, -2, node) == 1)
				return (-1);
		}
		name = triiim_char(name, 7);
		return_space(name);
		fd = open(name, O_RDONLY);
		if (fd == -1)
		{
			if (file_errors(name, 0, node) == 0)
				return (-1);
		}
		free (name);
		name = ft_strchr1(s, '<', 1);
	}
	return (fd);
}

int procces_writefiles(char *s, t_cmd *node)
{
	char *name;
	int fd;
	
	fd = 1;
	name = ft_strchr1(s, '>', 1);
	while (name)
	{
		name++;
		name = get_filename(name, 1, 1);
		if ((name[0] == 2 && name[1] == 2 && name[2] == '\0') || (name[0] == 6 && name[1] == 0))
		{
			free(name);
			name = ft_strdup("");
		}
		if (name[ft_strlen(name) - 1] == 5)
			name[ft_strlen(name) - 1] = 0;
		if ((name[0] == 2 && name[1] == '\0') || has_space(name))
		{	
			if (file_errors(name, -2, node) == 1)
				return (-1);
		}
		name = triiim_char(name, 7);
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			if (file_errors(name, 1, node) == 1)
				return (-1);
		}
		free (name);
		name = ft_strchr1(s, '>', 1);
	}
	return (fd);
}

int procces_appendfiles(char *s, t_cmd *node)
{
	char *name;
	int fd;
	
	fd = 1;
	name = ft_strchr2(s, '>', 1);
	while(name)
	{
		name++;
		name = get_filename(name, 1, 1);
		if ((name[0] == 2 && name[1] == 2 && name[2] == '\0') || (name[0] == 6 && name[1] == 0))
		{
			free(name);
			name = ft_strdup("");
		}
		if (name[ft_strlen(name) - 1] == 5)
			name[ft_strlen(name) - 1] = 0;
		if ((name[0] == 2 && name[1] == '\0') || has_space(name))
		{	
			if (file_errors(name, -2, node) == 1)
				return (-1);
		}
		name = triiim_char(name, 7); 
		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			if (file_errors(name, 1, node) == 1)
				return (-1);
		}
		free (name);
		name = ft_strchr2(s, '>', 1);
	}
	return (fd);
}

int	input_file(t_cmd *node)
{
	int fd1;
	int fd2;
	char *s;
	int	last;
	int t;

	s = node->str;
	t = 0;
	fd1 = 0;
	fd2 = 0;
	if (!s)
		return(0);
	last = ft_strrchr1(s, '<');
	if (s[last - 1] == '<')
		t = 1;
	fd2 = procces_her_doc(s, node);
	fd1 = procces_readfiles(s, node);
	if (t == 1)
		return (fd2);
	return (fd1);
}

int output_file(t_cmd *node)
{
	int fd1;
	int fd2;
	char *s;
	int	last;
	int t;
	
	s = node->str;
	t = 0;
	fd1 = 1;
	fd2 = 1;
	if (!s)
		return (1);
	last = ft_strrchr1(s, '>');
	if (s[last - 1] == '>')
		t = 1;
	fd2 = procces_appendfiles(s, node);
	fd1 = procces_writefiles(s, node);
	if (t == 1)
		return (fd2);
	return (fd1);
}

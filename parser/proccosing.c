/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:44:44 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/16 16:43:40 by fhihi            ###   ########.fr       */
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
		if (s[i] == 7)
			s[i] = 32;
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
		if (s[i] != 5)
			new[i] = s[i];
		i++;
	}
	free(s);
	return (new);
}

char	**get_cmd_opt(char *s)
{
	char **new;
	int i;
	
	i = 1;
	if (!s && !s[0])
		return (NULL);
	new = ft_split(s, 1);
	if (new[0] == NULL)
		return NULL;
	return_red(new[0]);
	new[0] = remove_non_printble(new[0]);
	while (new[i])
	{
		return_red(new[i]);
		if (new[i][0] == 2 && new[i][1] == 0)
			new[i] = NULL;
		else if ((new[i][0] == 2 && new[i][1] == 2 && new[i][2] == '\0') ||\
		 (new[i][ft_strlen(new[i]) - 1] == 5 && new[i][ft_strlen(new[i])] == 0) || new[i][0] == 6)
			new[i][ft_strlen(new[i]) - 1] = 0;
		new[i] = remove_non_printble(new[i]);
		i++;
	}
	
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

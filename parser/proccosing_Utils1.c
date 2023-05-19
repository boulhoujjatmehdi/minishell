/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing_Utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:47:06 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/19 15:38:07 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

void	her_child(char *name, t_list **env)
{
	t_var	var;
	int		fd;

	var.i = check_delimeter(name);
	signal(SIGINT, SIG_DFL);
	var.j = ft_strlen(name) + 1;
	fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	var.new = readline(">");
	while (var.new && ft_strncmp(name, var.new, var.j))
	{
		if (!var.i)
			var.new = herdoc_env(var.new, env);
		ft_putstr_fd(var.new, fd);
		ft_putstr_fd("\n", fd);
		var.new = readline(">");
	}
	close(fd);
	exit(0);
}

int	get_here_doc(char *name, t_list **env)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
		her_child(name, env);
	waitpid(pid, &status, 0);
	if (status)
		return (-2);
	return (0);
}

int	procces_her_doc(char *s, t_cmd *node)
{
	char	*name;
	int		fd;

	fd = 0;
	name = ft_strchr2(s, '<', 1);
	while (name)
	{
		if (fd != 0)
			close(fd);
		name++;
		name = get_filename(name, 1, 1);
		fd = get_here_doc(name, node->env);
		if (fd == -2)
			node->ctr_c = 1;
		free(name);
		fd = open(".tmp", O_RDONLY);
		name = ft_strchr2(s, '<', 1);
	}
	return (fd);
}

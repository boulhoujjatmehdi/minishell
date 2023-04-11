/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:39:36 by fhihi             #+#    #+#             */
/*   Updated: 2023/04/11 13:47:31 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

char	**ft_get_paths(char *env[])
{
	char	*path;
	char	**paths;
	int		i;

	path = ft_env(env);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin2(paths[i], "/");
		i++;
	}
	free(path);
	return (paths);
}

char	*ft_env(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = ft_strdup("/usr/local/sbin:/usr/local/bin:/\
	/usr/sbin:/usr/bin:/sbin:/bin");
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	if (env[i])
	{
		free(path);
		path = ft_strdup(env[i] + 5);
	}
	return (path);
}

char	*ft_cmd_path(char *cmd, char *env[])
{
	char	*cmd_path;
	int		l;

	l = 0;
	if (!cmd)
		return NULL;
	cmd_path = NULL;
	if (ft_strchr(cmd, '/') || cmd[0] == '.')
	{
		l = 1;
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (cmd);
			else
				ft_permision(cmd, 126);
		}
	}
	if (l == 1)
		ft_no_file_diractory(cmd, 127);
	cmd_path = ft_cmd_path2(cmd, env, l);
	return (cmd_path);
}

char	*ft_cmd_path2(char *cmd, char *env[], int l)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	paths = ft_get_paths(env);
	while (paths[i])
	{
		paths[i] = ft_strjoin2(paths[i], cmd);
		i++;
	}
	i = 0;
	while (paths[i] && (access(paths[i], F_OK) == -1))
		i++;
	if (!paths[i])
	{
		if (!ft_strncmp(cmd, "|", 2))
			ft_cmd_not_found("", 127);
		ft_cmd_not_found(cmd, 127);
	}
	else
		cmd_path = ft_strdup(paths[i]);
	free(cmd);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (cmd_path);
}

void	ft_permision(char *cmd, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Permission denied", 2);
	ft_putchar_fd('\n', 2);
	exit(exit_code);
}

void	ft_cmd_not_found(char *cmd, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putchar_fd('\n', 2);
	exit(exit_code);
}

void	ft_no_file_diractory(char *file_name, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putchar_fd('\n', 2);
	exit(exit_code);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:39:36 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/05 17:00:36 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

int check_builtins(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if(!ft_strncmp(cmd, "exit", 5))
		return (1);
	else if(!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if(!ft_strncmp(cmd, "env", 4))
		return (1);
	else if(!ft_strncmp(cmd, "unset", 6))
		return (1);
	else
		return (0);
}


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
		{
			break ;
		}
		i++;
	}
	// puts(env[i]);
	if (env[i])
	{
		free(path);
		path = ft_strdup(env[i] + 5);
	}
	return (path);
}

char	*ft_cmd_path(char *cmd, char *env[], t_cmd *node)
{
	char	*cmd_path;
	int		l;

	l = 0;
	if(check_builtins(cmd))
		return (cmd);
	if (!cmd)
		return NULL;
	cmd_path = NULL;
	if (ft_strchr(cmd, '/') || cmd[0] == '.')
	{
		l = 1;
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return(cmd);
			else
				ft_permision(cmd, 126, node);
		}
	}
	if (l == 1)
		ft_no_file_diractory(cmd, 127, node);
	cmd_path = ft_cmd_path2(cmd, env, l, node);
	return (cmd_path);
}

char	*ft_cmd_path2(char *cmd, char *env[], int l, t_cmd *node)
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
		if (!ft_strncmp(cmd, "\\", 2))
			ft_cmd_not_found("", 127, node);
		ft_cmd_not_found(cmd, 127, node);
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

void	ft_permision(char *cmd, int exit_code, t_cmd *node)
{
	node->exit_msg = ft_strjoin2(node->exit_msg, "minishell: ");
	node->exit_msg = ft_strjoin2(node->exit_msg, cmd);
	node->exit_msg = ft_strjoin2(node->exit_msg, ": Permission denied\n");
	node->exit_stat = exit_code;
}

void	ft_cmd_not_found(char *cmd, int exit_code, t_cmd *node)
{
	node->exit_msg = ft_strjoin2(node->exit_msg, "minishell: ");
	if (ft_strncmp("\\", cmd, 2) == 0)
		node->exit_msg = ft_strjoin2(node->exit_msg, cmd);
	else
		node->exit_msg = ft_strjoin2(node->exit_msg, cmd);
	node->exit_msg = ft_strjoin2(node->exit_msg, ": command not found\n");
	node->exit_stat = exit_code;
}

void	ft_no_file_diractory(char *file_name, int exit_code, t_cmd *node)
{
	node->exit_msg = ft_strjoin2(node->exit_msg, "minishell: ");
	node->exit_msg = ft_strjoin2(node->exit_msg, file_name);
	node->exit_msg = ft_strjoin2(node->exit_msg, ": No such file or directory\n");
	node->exit_stat = exit_code;
}

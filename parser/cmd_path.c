/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:39:36 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/10 20:23:10 by fhihi            ###   ########.fr       */
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
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	if (env[i])
		path = ft_strdup(env[i] + 5);
	else
		path = ft_strdup("");
	return (path);
}

int	check_diractory(char *cmd, t_cmd *node)
{
	if (cmd[ft_strlen(cmd) - 1] == '/')
	{
		if (access(cmd, F_OK) == 0)
			ft_is_a_diractory(cmd, 126, node);
		else
			ft_is_not_diractory(cmd, 126, node);
		return (1);
	}
	return (0);
}

char	*ft_cmd_path(char *cmd, char *env[], t_cmd *node)
{
	char	*cmd_path;
	int		l;

	l = 0;
	if (!cmd)
		return NULL;
	if(check_builtins(cmd))
		return (cmd);
	cmd_path = NULL;
	if (ft_strchr(cmd, '/') || cmd[0] == '.')
	{
		l = 1;
		if (check_diractory(cmd, node))
			return (NULL);
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return(cmd);
			else
			{
				ft_permision(cmd, 126, node);
				return (NULL);
			}
		}
	}
	if (l == 1)
	{
		ft_no_file_diractory(cmd, 127, node);
		return (NULL);
	}
	cmd_path = ft_cmd_path2(cmd, env, node);
	return (cmd_path);
}

char	*ft_cmd_path2(char *cmd, char *env[], t_cmd *node)
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
			ft_cmd_not_found(cmd, 127, node);
	else
		cmd_path = ft_strdup(paths[i]);
	free(cmd);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (cmd_path);
}

void	ft_is_a_diractory(char *cmd, int exit_code, t_cmd *node)
{
	node->exit_msg = ft_strjoin2(node->exit_msg, "minishell: ");
	node->exit_msg = ft_strjoin2(node->exit_msg, cmd);
	node->exit_msg = ft_strjoin2(node->exit_msg, ": is a directory\n");
	node->exit_stat = exit_code;
}

void	ft_is_not_diractory(char *cmd, int exit_code, t_cmd *node)
{
	node->exit_msg = ft_strjoin2(node->exit_msg, "minishell: ");
	node->exit_msg = ft_strjoin2(node->exit_msg, cmd);
	node->exit_msg = ft_strjoin2(node->exit_msg, ": Not a directory\n");
	node->exit_stat = exit_code;
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
	if (!ft_strncmp(cmd, "\\", 2))
		node->exit_msg = ft_strjoin2(node->exit_msg, "");
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

void	ft_ambiguous(char *name, int exit_code, t_cmd *node)
{
	node->exit_msg = ft_strjoin2(node->exit_msg, "minishell: ");
	node->exit_msg = ft_strjoin2(node->exit_msg, "ambiguous redirect\n");
	node->exit_stat = exit_code;
}

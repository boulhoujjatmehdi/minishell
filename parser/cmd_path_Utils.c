/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_Utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:15:36 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 18:00:07 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

char	*check_dir_scri(char *cmd, t_cmd *node)
{
	if (check_diractory(cmd, node))
		return (NULL);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			ft_permision(cmd, 126, node);
			free(cmd);
			return (NULL);
		}
	}
	ft_no_file_diractory(cmd, 127, node);
	free(cmd);
	return (NULL);
}

char	*ft_cmd_path(char *cmd, char *env[], t_cmd *node)
{
	char	*cmd_path;

	if (!cmd)
		return (NULL);
	if (!cmd[0])
		ft_cmd_not_found(cmd, 127, node);
	if (check_builtins(cmd))
		return (cmd);
	if (ft_strchr(cmd, '/') || cmd[0] == '.')
		return (check_dir_scri(cmd, node));
	cmd_path = ft_cmd_path2(cmd, env, node);
	return (cmd_path);
}

void	join_path_cmd(char **paths, char *cmd)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin2(paths[i], cmd);
		i++;
	}
}

char	*ft_cmd_path2(char *cmd, char *env[], t_cmd *node)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	paths = ft_get_paths(env);
	if (!paths)
	{
		ft_no_file_diractory(cmd, 127, node);
		free(cmd);
		return (NULL);
	}
	join_path_cmd(paths, cmd);
	i = 0;
	while (paths[i] && (access(paths[i], F_OK) == -1))
		i++;
	if (!paths[i])
		ft_cmd_not_found(cmd, 127, node);
	else
		cmd_path = ft_strdup(paths[i]);
	free(cmd);
	free_2darrary(paths);
	return (cmd_path);
}

void	ft_ambiguous(int exit_code, t_cmd *node)
{
	node->exit_msg = ft_strjoin2(node->exit_msg, "minishell: ");
	node->exit_msg = ft_strjoin2(node->exit_msg, "ambiguous redirect\n");
	node->exit_stat = exit_code;
}

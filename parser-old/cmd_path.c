/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:39:36 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/17 00:02:20 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

char	*ft_cmd_path(char *cmd, char *env[], t_cmd *node)
{
	char	*cmd_path;
	int		l;

	l = 0;
	if (!cmd)
		return NULL;
	if (cmd && !cmd[0])
		ft_cmd_not_found(cmd, 127, node);
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

void	ft_ambiguous(int exit_code, t_cmd *node)
{
	node->exit_msg = ft_strjoin2(node->exit_msg, "minishell: ");
	node->exit_msg = ft_strjoin2(node->exit_msg, "ambiguous redirect\n");
	node->exit_stat = exit_code;
}

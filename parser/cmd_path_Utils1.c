/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_Utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:43:08 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/12 19:44:45 by fhihi            ###   ########.fr       */
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

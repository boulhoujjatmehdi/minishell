/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_Utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:44:03 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/12 19:44:20 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"parse.h"

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
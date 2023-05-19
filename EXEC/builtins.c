/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:20 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/19 15:27:37 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_export(t_minishell msh, t_cmd *cmd)
{
	t_list	*tmp;
	int		i;

	i = 1;
	if (!cmd->cmd_args[1])
	{
		ft_export_list();
		return (1);
	}
	while (cmd->cmd_args[i])
	{
		tmp = *msh.lenv;
		if (!export_error(cmd->cmd_args[i]))
		{
			tmp = find_var_env(tmp, cmd->cmd_args[i]);
			if (!tmp || !tmp->content)
			{
				ft_lstlast(*msh.lenv)->content = ft_strdup(cmd->cmd_args[i]);
				ft_lstadd_back(msh.lenv, ft_lstnew(NULL));
			}
		}
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	char	**to_print;
	int		trigger;
	char	*str;

	str = NULL;
	trigger = 0;
	to_print = cmd->cmd_args;
	to_print++;
	ft_echo_1(to_print, &trigger, str);
	if (!trigger)
		printf("\n");
	return (0);
}

int	ft_env_cmd(t_minishell *msh)
{
	t_list	*tmp;

	tmp = *msh->lenv;
	while (tmp && tmp->content)
	{
		if (ft_strnstr_mod(tmp->content, "=") >= 0)
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	exit(0);
	return (1);
}

int	ft_unset(t_minishell *msh, t_cmd *cmd)
{
	t_list	*tmp;
	t_list	*prv;
	char	*arg;
	char	*str;
	int		i;

	str = NULL;
	prv = NULL;
		i = 1;
	while (cmd->cmd_args[i])
	{
		tmp = *msh->lenv;
		arg = cmd->cmd_args[i];
		ft_unset_1(tmp, prv, arg, str);
		i++;
	}
	return (1);
}

int	exec_builtins(t_cmd *cmd, int par)
{
	if (!cmd->cmd_path)
		return (0);
	else if (!ft_strncmp(cmd->cmd_path, "export", 7) && par)
		ft_export(*g_msh, cmd);
	else if (!ft_strncmp(cmd->cmd_path, "export", 7) && g_msh->child_nb == 1)
		return (ft_export(*g_msh, cmd));
	else if (!ft_strncmp(cmd->cmd_path, "unset", 6) && g_msh->child_nb == 1)
		return (ft_unset(g_msh, cmd));
	else if (!ft_strncmp(cmd->cmd_path, "echo", 5) && par)
		ft_echo(cmd);
	else if (!ft_strncmp(cmd->cmd_path, "cd", 3) && g_msh->child_nb == 1)
		return (ft_cd(cmd, g_msh));
	else if (!ft_strncmp(cmd->cmd_path, "pwd", 4) && par)
		ft_pwd();
	else if (!ft_strncmp(cmd->cmd_path, "env", 4) && par)
		return (ft_env_cmd(g_msh));
	else if (!ft_strncmp(cmd->cmd_path, "exit", 5))
		return (ft_exit(cmd));
	return (0);
}

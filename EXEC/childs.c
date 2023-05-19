/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:52:15 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/19 16:05:47 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	child_forked(t_minishell *msh, int idx, int *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		g_msh->c_tmp = get_right_comm(msh, idx);
		if (g_msh->c_tmp->next)
			dup2(msh->pipe[idx * 2 + 1], 1);
		if (g_msh->c_tmp->outfile != 1)
		{
			dup2(g_msh->c_tmp->outfile, 1);
			if (g_msh->c_tmp->next)
				ft_putstr_fd("\n", msh->pipe[idx * 2 + 1]);
		}
		if (idx > 0)
		{
			dup2(msh->pipe[(idx - 1) * 2], 0);
			if (g_msh->c_tmp->infile > 0)
				read(0, NULL, 1);
		}
		if (g_msh->c_tmp->infile > 0)
			dup2(g_msh->c_tmp->infile, 0);
		close_all_pipes(msh);
		exec_builtins(g_msh->c_tmp, 1);
		execve(g_msh->c_tmp->cmd_path, g_msh->c_tmp->cmd_args, msh->env);
		exit(0);
	}
}

void	forking(int k, int *stat, int *pid)
{
	while (*stat && k < g_msh->child_nb)
	{
		g_msh->c_tmp = get_right_comm(g_msh, k);
		g_msh->c_tmp->env = g_msh->lenv;
		proccesing_cmd(g_msh->c_tmp, g_msh->env);
		if (g_msh->c_tmp->ctr_c == 1)
		{
			*stat = 0;
			g_msh->exit_st = 130;
		}
		else if (*stat && g_msh->c_tmp->exit_msg)
		{
			ft_putstr_fd(g_msh->c_tmp->exit_msg, 2);
			g_msh->exit_st = g_msh->c_tmp->exit_stat;
		}
		else if (*stat && !exec_builtins(g_msh->c_tmp, 0))
			child_forked(g_msh, k, &pid[k]);
		k++;
	}
}

void	fork_it_for_me(void)
{
	int	k;
	int	*pid;
	int	stat;

	k = 0;
	stat = 1;
	pid = ft_calloc(sizeof(int), g_msh->child_nb);
	if (!pid)
		return ;
	open_pipes();
	forking(k, &stat, pid);
	close_all_pipes(g_msh);
	wait_for_all(pid, g_msh->child_nb);
	free(pid);
}

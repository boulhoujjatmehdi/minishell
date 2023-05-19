/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:59:28 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/19 13:55:29 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	wait_for_all(int *pids, int nb)
{
	int		i;
	t_cmd	*cmd;
	int		status;

	i = 0;
	while (i < nb)
	{
		status = 0;
		cmd = get_right_comm(g_msh, i);
		if (cmd->exit_msg)
		{
			g_msh->exit_st = cmd->exit_stat;
		}
		else if (pids[i])
		{
			waitpid(pids[i], &status, 0);
			g_msh->exit_st = status >> 8;
		}
		i++;
	}
}

void	close_all_pipes(t_minishell *msh)
{
	int	i;

	i = 0;
	while (i < (g_msh->child_nb - 1) * 2)
	{
		close(msh->pipe[i]);
		close(msh->pipe[i + 1]);
		i += 2;
	}
	free(msh->pipe);
}

void	open_pipes(void)
{
	int	i;

	i = 0;
	g_msh->pipe = ft_calloc (sizeof(int) * 2, (g_msh->child_nb + 1));
	if (!g_msh->pipe)
	{
		g_msh->pipe = NULL;
		return ;
	}
	while (i < g_msh->child_nb - 1)
	{
		pipe(&g_msh->pipe[i * 2]);
		i++;
	}
}

int	execution_function(t_cmd *comms, t_list **lenv)
{
	int		i;
	t_list	*tmp;

	g_msh->lenv = lenv;
	g_msh->comms = comms;
	g_msh->env = ft_calloc(sizeof(char *), ft_lstsize(*g_msh->lenv));
	tmp = *g_msh->lenv;
	i = 0;
	while (tmp)
	{
		if (tmp->content)
			g_msh->env[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	g_msh->child_nb = get_comm_lenght(g_msh->comms);
	fork_it_for_me();
	i = 0;
	free(g_msh->env);
	unlink(".tmp");
	return (0);
}

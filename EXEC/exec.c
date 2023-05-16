/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:59:28 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/15 21:58:14 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


void wait_for_all(int *pids , int nb)
{
	int i;

	i = 0;
	while(i < nb)
	{
		int status= 0;
		if(pids[i])
		{
			waitpid(pids[i], &status, 0);
			g_msh->exit_st = status>>8;
		}
		i++;
	}
}

void close_all_pipes(t_minishell *msh)
{
		int ii = 0;
		while(ii < (msh->pipe_nb - 1 ) * 2)
		{
			close(msh->pipe[ii]);
			close(msh->pipe[ii + 1]);
			ii += 2;
		}
}

void fork_it_for_me()
{
	int k;
	int *pid;

	k = 0;
	int stat = 1;
	pid = ft_calloc(sizeof(int) , g_msh->pipe_nb);
		while(stat && k < g_msh->child_nb)
		{
			t_cmd *com = get_right_comm(g_msh , k);
			com->env = g_msh->lenv;
			proccesing_cmd(com, g_msh->env);
			if(com->ctr_c == 1)
			{
				stat = 0;
				g_msh->exit_st = 130;
			}
			else if(stat && com->exit_msg)
			{
				ft_putstr_fd(com->exit_msg, 2);
				g_msh->exit_st = com->exit_stat;
				printf("**%d**\n", com->exit_stat);
			}
			else if(stat && !exec_builtins(com, 0))
				child_forked(g_msh , k,  &pid[k]);
			k++;
		}
	close_all_pipes(g_msh);
	printf("**%d**\n", g_msh->exit_st);
	wait_for_all(pid, g_msh->pipe_nb);
	printf("**%d**\n", g_msh->exit_st);
	free(pid);
}

void  open_pipes()
{
	int i;

	i = 0;
	g_msh->pipe = ft_calloc (sizeof(int) * 2 , (g_msh->pipe_nb + 1));

	if(!g_msh->pipe)
	{
		g_msh->pipe = NULL;
		return ;
	}
	while(i < g_msh->pipe_nb-1)
	{
		pipe(&g_msh->pipe[i * 2]);
		i++;
	}
}

void initialize_data()
{
	int i;

	g_msh->child_nb = get_comm_lenght(g_msh->comms);
	g_msh->pipe_nb = g_msh->child_nb;
}

int main_function_exec(t_cmd *comms , t_list **lenv)
{

    g_msh = g_msh;
	g_msh->lenv = lenv;
    g_msh->comms = comms;

	g_msh->env = ft_calloc(sizeof(char*), ft_lstsize(*g_msh->lenv));
	t_list *tmp = *g_msh->lenv;
	int i =0;
	while(tmp)
	{
		if(tmp->content)
			g_msh->env[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}

    initialize_data();
    open_pipes();
	fork_it_for_me();
    return (0);
}
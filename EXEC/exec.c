/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:59:28 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/18 14:22:01 by eboulhou         ###   ########.fr       */
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
		t_cmd *cmd = get_right_comm(g_msh, i);
		if(cmd->exit_msg)
		{
			g_msh->exit_st = cmd->exit_stat;
		}
		else if(pids[i])
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
	free(msh->pipe);
}
#include<sys/time.h>
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
			// puts("was here");
			proccesing_cmd(com, g_msh->env);
			// puts("was here");
			
			if(com->ctr_c == 1)
			{
				stat = 0;
				g_msh->exit_st = 130;
			}
			else if(stat && com->exit_msg)
			{
				ft_putstr_fd(com->exit_msg, 2);
				g_msh->exit_st = com->exit_stat;
				// puts("22222222222");
			}
			else if(stat && !exec_builtins(com, 0))
				child_forked(g_msh , k,  &pid[k]);
			k++;
		}
	close_all_pipes(g_msh);
	wait_for_all(pid, g_msh->pipe_nb);
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
	g_msh->child_nb = get_comm_lenght(g_msh->comms);
	g_msh->pipe_nb = g_msh->child_nb;
}

int main_function_exec(t_cmd *comms , t_list **lenv)
{
	g_msh->lenv = lenv;
    g_msh->comms = comms;

	g_msh->env = ft_calloc(sizeof(char*), ft_lstsize(*g_msh->lenv));
	t_list *tmp = *g_msh->lenv;
	int i =0;
	if(puse_)
		pause();
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
	i = 0;
	free(g_msh->env);
    return (0);
}
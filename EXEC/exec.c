/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:59:28 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/08 17:40:49 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int g_exit;
void wait_for_all(int *pids , int nb)
{
	int i;

	i = 0;
	while(i < nb)
	{
		int status= 0;
		waitpid(pids[i], &status, 0);
		// printf("exit %d\n", status>>8);
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
			exit(55);
			ii += 2;
		}
}

void fork_it_for_me(t_minishell *msh)
{
	int i;
	int j;
	int k;
	int *pid;
	
	i = 0;
	j = 2;
	k = 0;
	int stat = 1;
	pid = ft_calloc(sizeof(int) , msh->pipe_nb);
		while(k < msh->child_nb)
		{
			t_cmd *com = get_right_comm(msh , k);
			proccesing_cmd(com, msh->env);

			if(com->ctr_c == 1)
			{
				stat = 0;
			}

			if(stat && com->exit_msg)
			{
				printf("-%s-\n", com->exit_msg);
			}
			else if(stat && !check_builtis(com, msh))
				child_forked(msh , k,  &pid[k]);
			k++;
		}
	close_all_pipes(msh);
	wait_for_all(pid, msh->pipe_nb);
	free(pid);
}

void  open_pipes(t_minishell *msh)
{
	int i;

	i = 0;
	msh->pipe = ft_calloc (sizeof(int) * 2 , (msh->pipe_nb + 1));

	if(!msh->pipe)
	{
		msh->pipe = NULL;
		return ;
	}
	while(i < msh->pipe_nb-1)
	{
		pipe(&msh->pipe[i * 2]);
		i++;
	}
}

void initialize_data(t_minishell *msh)
{
	int i;

	msh->child_nb = get_comm_lenght(msh->comms);
	msh->pipe_nb = msh->child_nb;
}

int main_function_exec(t_cmd *comms , t_list **lenv)
{
    t_minishell *msh;
    msh = ft_calloc(sizeof(t_minishell), 1);
	msh->lenv = lenv;
    msh->comms = comms;


	msh->env = ft_calloc(sizeof(char*), ft_lstsize(*msh->lenv));
	t_list *tmp = *msh->lenv;
	int i =0;
	while(tmp)
	{
		if(tmp->content)
			msh->env[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}

    initialize_data(msh);
    open_pipes(msh);

	fork_it_for_me(msh);
    
    return (0);
}
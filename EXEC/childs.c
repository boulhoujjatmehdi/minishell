/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:52:15 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/13 16:05:33 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int export(t_minishell msh , t_cmd *cmd)
{
	ft_lstadd_back(msh.lenv, ft_lstnew(cmd->cmd_args[1]));
	int i;
	i = 0;

	return 0;
}
void exit_handler()
{
	// printf();
	exit(150);
}



void child_forked(t_minishell *msh , int idx, int *pid)
{
	t_cmd *com;

	*pid = fork();
	if(*pid == 0)
	{
		t_cmd *com = get_right_comm(msh , idx);

		if(com->next)
			dup2(msh->pipe[idx * 2 + 1], 1);
		if(com->outfile != 1)
		{
			dup2(com->outfile, 1);
			if(com->next)
				ft_putstr_fd("\n",msh->pipe[idx * 2 + 1]);
		}

		if(idx > 0)
		{
			dup2(msh->pipe[(idx - 1) * 2], 0);
			if(com->infile > 0)
				read(0, NULL, 1);
		}
		if(com->infile > 0)
			dup2(com->infile, 0);
		




		signal(SIGINT, exit_handler);
		close_all_pipes(msh);
		execve(com->cmd_path, com->cmd_args, msh->env);
		exit(10);
	}
	if(*pid)
	{
		// int status;
		// // waitpid(*pid ,&status,0);
		// printf("~~~~~~~~~%d\n", status);
	}
}
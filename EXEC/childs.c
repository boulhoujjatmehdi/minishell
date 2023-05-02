/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:52:15 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/02 14:01:16 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


void check_builtis(t_cmd *cmd)
{
	// perror(cmd->cmd_args[0]);
	if(!ft_strncmp(cmd->cmd_args[0], "export", 7))
	{
		ft_putstr_fd("get in export function with suxess\n", 2);
	}
}

void child_forked(t_minishell *msh , int idx, int *pid)
{
	t_cmd *com;

	*pid = fork();
	if(*pid == 0)
	{
		
		t_cmd *com = get_right_comm(msh , idx);
		
		proccesing_cmd(com, msh->env);

		check_builtis(com);
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
			if(com->infile > 0) // in case of 
				read(0, NULL, 1);
			
		}
		if(com->infile > 0)
			dup2(com->infile, 0);
		




		
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
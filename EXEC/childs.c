/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:52:15 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/03 18:57:12 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int export(t_minishell msh , t_cmd cmd)
{
	


	return 0;
}


void check_builtis(t_cmd *cmd)
{
	if(!ft_strncmp(cmd->cmd_path, "export", 7))
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
		printf("mehdi\n");
		exit(12);
		printf("com-path = %s\ncom-args = %s\n", com->cmd_path , com->cmd_args[1]);
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
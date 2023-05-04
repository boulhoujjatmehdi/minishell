/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:52:15 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/04 15:23:20 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int export(t_minishell msh , t_cmd *cmd)
{
	ft_lstadd_back(msh.lenv, ft_lstnew(cmd->cmd_args[1]));
	int i;
	i = 0;
	// i = ft_strnstr_mod(cmd->cmd_args[1], "=");
	// printf("%d=======\n", i);

	return 0;
}


void check_builtis(t_cmd *cmd , t_minishell *msh)
{
	if(!ft_strncmp(cmd->cmd_path, "export", 7))
	{
		export(*msh, cmd);
		exit(110);
	}
}

void child_forked(t_minishell *msh , int idx, int *pid)
{
	t_cmd *com;

	*pid = fork();
	if(*pid == 0)
	{
		t_cmd *com = get_right_comm(msh , idx);

		// printf("***%s**\n", com->cmd_path);
		// exit(99);
		proccesing_cmd(com, msh->env);
		check_builtis(com ,msh);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:52:48 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/06 12:56:43 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"



void first_child(t_minishell *msh , int *pid)
{
	// int pid;

	*pid = fork();
	if(*pid == 0)
	{
		// sleep(1);
		// printf("hello from the first child \n");
		// exit(11);
		
		dup2(msh->pipe[1], 1);
		close_all_pipes(msh);

		execve(msh->comms->com, msh->comms->flags, msh->env);
		exit(10);
	}
}

void middle_child(t_minishell *msh, int idx , int *pid)
{

	t_comm *com;
	*pid = fork();
	if(*pid == 0)
	{
		// puts("mehid----");

		// printf("hello from the child number==== %d , %d\n",idx,  com->idx);
		// exit(idx);
		dup2(msh->pipe[(idx - 1) * 2], 0);
		dup2(msh->pipe[idx * 2 + 1], 1);

		close_all_pipes(msh);
		com = get_right_comm(msh, idx);
		execve(com->com, com->flags, msh->env);
	}
}

void last_child(t_minishell *msh, int idx, int *pid)
{

	t_comm *com;
	*pid = fork();
	if(*pid == 0)
	{
		// printf("hello from the last child number %d ,%d \n", idx , com->idx);
		// exit(idx);
		dup2(msh->pipe[(idx - 1) * 2], 0);
		dup2(msh->pipe[idx * 2 + 1], 1);

		close_all_pipes(msh);

		com = get_right_comm(msh, idx);
		execve(com->com, com->flags, msh->env);
	}
}

void printer_child(t_minishell *msh, int idx, int *pid)
{
	*pid = fork();
	if(*pid == 0)
	{
		// printf("*/*/**/*/*/*/*//*hello from the printer child number %d id = %d\n", idx  , getpid());
		// exit(idx);
		dup2(msh->pipe[(idx - 1) * 2], 0);
		close_all_pipes(msh);
		char *str;
		char tmp;
		int i;

		i = 0;
		while(1)
		{
			str = get_next_line(0);
			if (!str)
				break ;
			ft_putstr_fd(str, 1);
			tmp = str[ft_strlen(str)-1];
			i++;
		}
		if(tmp != 10 && i )
		{
			// write();
			write(1, "%\n", 3);
		}
		// printf("*******************\n");

		exit(0);
	}
}




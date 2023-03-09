/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:52:48 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/09 20:31:30 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void infiles_child(t_comm * com , int *pipe , int *pid)
{
	*pid = fork();
	if(*pid == 0)
	{
		printf("mehdi bouhloujjat\n");
		if(dup2(pipe[1], 1) < 0)
			printf("dup faild!!!!!!!\n");
		close(pipe[0]);
		int i = 0;
		while(com->infiles[i])
		{
			int fd = open (com->infiles[i], O_RDONLY);
			char *str = get_next_line(fd);
			while(str)
			{
				ft_putstr_fd(str, 1);
				str = get_next_line(fd);// this is weher i left it
				
			}
			i++;
		}
		close(pipe[1]);
		exit(0);
	}	
}

void first_child(t_minishell *msh , int *pid)
{
	// int pid;
	
	*pid = fork();
	if(*pid == 0)
	{
		// sleep(1);
		// printf("hello from the first child \n");
		// exit(11);
		if(msh->child_nb > 1)
			dup2(msh->pipe[1], 1);
		close_all_pipes(msh);
	
		if(msh->comms->infiles)
		{
			int pp[2];
			int pd;
			pipe(pp);
			dup2(pp[0] , 0);
			infiles_child(msh->comms, pp, &pd);
			close(pp[0]);
			close(pp[1]);
			waitpid(pd, NULL, 0);
		}
		// puts("");
		// puts(msh->comms->flags[1]);
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
		// dup2(msh->pipe[idx * 2 + 1], 1);

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
		// if(idx > 0)
			// dup2(msh->pipe[(idx - 1) * 2], 0);
		// if (idx < 1)
		// puts(msh->comms->infiles[0]);
		
		int i = 0;
		char tmpp = 0;
		if (idx == 0)
		{

			dup2(msh->pipe[(idx * 2) + 1], 1);
			close_all_pipes(msh);
			while(msh->comms->infiles[i])
			{
				int fd = open(msh->comms->infiles[i] , O_RDONLY);
				char *str = get_next_line(fd);
				while(str)
				{
					tmpp = str[ft_strlen(str)-1];
					ft_putstr_fd(str, 1);
					str = get_next_line(fd);
				}
				close(fd);
				i++;
			}
		}
		if (idx == 1)
		{
			dup2(msh->pipe[(idx - 1) * 2], 0);
			dup2(msh->pipe[(idx * 2) + 1], 1);
			close_all_pipes(msh);

			execve(msh->comms->com, msh->comms->flags, msh->env);
			exit(10);
		}
		if (idx == 2)
		{
			dup2(msh->pipe[(idx - 1) * 2], 0);
			close_all_pipes(msh);
			char *str = get_next_line(0);
			while(str)
			{
				tmpp = str[ft_strlen(str)-1];
				ft_putstr_fd(str, 1);
				str = get_next_line(0);
			}
			if (tmpp != '\n')
				write(1, "\n", 1);
		}
		exit(0);
	}
}




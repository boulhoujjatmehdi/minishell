/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:52:48 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/12 14:40:30 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void infiles_child(t_minishell *msh,int comidx, int idx, int *pid)
{
	*pid = fork();
	if(*pid == 0)
	{
		// printf("mehdi bouhloujjat\n");
		printf("%d\n",  msh->pipe[idx * 2 + 1] );
		dup2(msh->pipe[idx * 2 + 1], 1);
		close_all_pipes(msh);
		// printf("----=%d\n",pipe[1] );
		int i = 0;
		t_comm *com = get_right_comm(msh, comidx);
		while(com->infiles[i])
		{
			int fd = open (com->infiles[i], O_RDONLY);
			char *str = get_next_line(fd);
			while(str)
			{
				ft_putstr_fd(str, 1);
				str = get_next_line(fd);
			}
			i++;
		}
		exit(0);
	}	
}
void outfiles_child(t_minishell *msh, int comidx, int idx, int *pid)
{
	*pid = fork();
	if(*pid == 0)
	{
		printf("hello from outfiles_child\nread from %d\nwrite on %d\n", msh->pipe[(idx - 1) * 2] ,msh->pipe[idx * 2 + 1] );
		t_comm *com = get_right_comm(msh, comidx);
		dup2(msh->pipe[(idx - 1) * 2], 0);
		if(com->next)
			dup2(msh->pipe[idx * 2 + 1], 1);
		
		close_all_pipes(msh);
		int fd = open (com->outfiles[0], O_WRONLY);
		char *str = get_next_line(0);
		while(str)
		{
			ft_putstr_fd(str , fd);
			if(com->next)
				ft_putstr_fd(str , 1);
			str = get_next_line(0);
		}
		exit(0);
	}
}

void first_child(t_minishell *msh , int idx, int *pid)
{
	// int pid;

	*pid = fork();
	if(*pid == 0)
	{
		// sleep(1);
		printf("hello from the first child \nread from %d\nwrite on %d\n", msh->pipe[0], msh->pipe[idx * 2 + 1]);
		// exit(11);
		
		// if(msh->child_nb > 1)
			dup2(msh->pipe[idx * 2 + 1], 1);
		if(*msh->comms->infiles)
			dup2(msh->pipe[0], 0);
		close_all_pipes(msh);
		execve(msh->comms->com, msh->comms->flags, msh->env);
		exit(10);
	}
	// if(*msh->comms->outfiles)
	// {
	// 	outfiles_child()
	// }
}


void middle_child(t_minishell *msh, int idx , int *pid)
{

	t_comm *com;

	*pid = fork();
	if(*pid == 0)
	{
		
		dup2(msh->pipe[(idx - 1) * 2], 0);
		dup2(msh->pipe[idx * 2 + 1], 1);

		close_all_pipes(msh);
		com = get_right_comm(msh, idx);
		execve(com->com, com->flags, msh->env);
	}
}

void last_child(t_minishell *msh,int comidx,  int idx, int *pid)
{

	t_comm *com;
	*pid = fork();
	if(*pid == 0)
	{
		printf("hello from the last child number \nread from %d\n", msh->pipe[(idx - 1) * 2]);
		// exit(idx);
		dup2(msh->pipe[(idx - 1) * 2], 0);
		// dup2(msh->pipe[idx * 2 + 1], 1);

		close_all_pipes(msh);
		com = get_right_comm(msh, comidx);
		printf("*/*/*/*/**/*/*/*/ %s\n", com->com);
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




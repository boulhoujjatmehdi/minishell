/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:52:48 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/14 10:08:50 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void infiles_child(t_minishell *msh,int comidx, int idx, int *pid)
{
	*pid = fork();
	if(*pid == 0)
	{
		// printf("--INFILE %d - %d \n", idx , getpid());
		
		t_comm *com = get_right_comm(msh, comidx);
		dup2(msh->pipe[idx * 2 + 1], 1);
		if(com->prev)
			dup2(msh->pipe[(idx - 1) * 2] , 0);
		close_all_pipes(msh);
		int i = 0;
		if(com->prev)
		{			
			char *str = get_next_line(0);
			while(str)
			{
				ft_putstr_fd(str, 1);
				str = get_next_line(0);
			}
		}
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
		// printf("--OUTFILE %d - %d \n", idx , getpid());
		// printf("hello from outfiles_child\nread from %d\nwrite on %d-\n", msh->pipe[(idx - 1) * 2] ,msh->pipe[idx * 2 + 1] );
		
		t_comm *com = get_right_comm(msh, comidx);
		int out = get_mat_length(com->outfiles);////// make this function to make all output files.
		int *out_fd = malloc(sizeof(int) * out);
		dup2(msh->pipe[(idx - 1) * 2], 0);
		if(com->next)
			dup2(msh->pipe[idx * 2 + 1], 1);
		close_all_pipes(msh);
		int i = 0;
		while(i < out)
		{
			out_fd[i] = open(com->outfiles[i], O_CREAT | O_WRONLY | O_TRUNC , 0777);
			i++;
		}
		int fd = open (com->outfiles[0], O_WRONLY | O_TRUNC);
		char *str = get_next_line(0);
		while(str)
		{
			i = 0;
			while(i < out)
			{
				ft_putstr_fd(str , out_fd[i]);
				i++;
			}
				if(com->next)
					ft_putstr_fd(str , 1);
			str = get_next_line(0);
		}
		exit(0);
	}
}

void first_child(t_minishell *msh , int idx, int *pid)
{
	*pid = fork();
	if(*pid == 0)
	{
		// printf("--FIRST %d - %d \n", idx , getpid());
		// printf("hello from the first child \nread from %d\nwrite on %d\n", msh->pipe[0], msh->pipe[idx * 2 + 1]);
		// exit(11);

		if(msh->child_nb > 1 || get_right_comm(msh , 0)->outfiles[0])
			dup2(msh->pipe[idx * 2 + 1], 1);
		if(*msh->comms->infiles)
			dup2(msh->pipe[0], 0);
		close_all_pipes(msh);
		execve(msh->comms->com, msh->comms->flags, msh->env);
		exit(10);
	}

}


void middle_child(t_minishell *msh, int comidx, int idx , int *pid)
{
	t_comm *com;

	*pid = fork();
	if(*pid == 0)
	{
		// printf("--MIDDLE %d - %d \n", idx , getpid());
		
		// printf("//**//hellooo from midle child\nread from %d\nwrite on %d\n", msh->pipe[(idx - 1) * 2],  msh->pipe[(idx * 2)+ 1 ]);
		dup2(msh->pipe[(idx - 1) * 2], 0);
		dup2(msh->pipe[idx * 2 + 1], 1);

		close_all_pipes(msh);
		com = get_right_comm(msh, comidx);
		execve(com->com, com->flags, msh->env);
	}
}

void last_child(t_minishell *msh,int comidx,  int idx, int *pid)
{

	t_comm *com;
	*pid = fork();
	if(*pid == 0)
	{
		// printf("--LAST %d - %d \n", idx , getpid());
		
		com = get_right_comm(msh, comidx);
		// printf("hello from the last child number \nread from %d\n", msh->pipe[(idx - 1) * 2]);
		// exit(idx);
		dup2(msh->pipe[(idx - 1) * 2], 0);
		if(*com->outfiles)
			dup2(msh->pipe[idx * 2 + 1], 1);

		close_all_pipes(msh);
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




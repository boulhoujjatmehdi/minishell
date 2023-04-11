/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:52:15 by eboulhou          #+#    #+#             */
/*   Updated: 2023/04/11 13:51:58 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void infiles_child(t_minishell *msh,int comidx, int idx, int *pid)
{
	*pid = fork();
	if(*pid == 0)
	{
		t_cmd *cmd = get_right_comm(msh, comidx);
		printf("--INFILE %d - %d == %d\n", idx , getpid(), cmd->infile);

		// printf("======%d\n", cmd->infile);
		int i = 0;
		int fd;
		if(cmd->infile == -2)
		{
			char **here = ft_split(cmd->her_doc, ':');
			while(here[i])
			{
				fd = open(".tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
				char *str;
				str =readline("heredoc>>");
				while(strcmp(here[i] , str))
				{
					ft_putstr_fd(str,fd );
					ft_putstr_fd("\n" , fd);
					str =readline("heredoc>>");
				}
				i++;
				close(fd);
			}
			fd = open(".tmp.txt", O_RDONLY);
			char *str = malloc(101);
			int nb = read(fd , str , 100);
			str[nb]  = 0;
			while(nb > 0)
			{
				ft_putstr_fd(str , msh->pipe[idx * 2 + 1]);
				nb = read(fd , str , 1000);
			}
			unlink(".tmp.txt");
			close_all_pipes(msh);
		}
		if(cmd->infile > 0 )
		{
			dup2(msh->pipe[idx * 2 + 1], 1);
			close_all_pipes(msh);
			
			i = 0;
			char *str = get_next_line(cmd->infile);
			while(str)
			{
				ft_putstr_fd(str, 1);
				str = get_next_line(cmd->infile);
			}
			i++;
		}
		exit(0);
	}
} 

void first_child(t_minishell *msh , int idx, int *pid)
{
	*pid = fork();
	if(*pid == 0)
	{
		// puts(msh->env[0]);
		// printf("heool");
		t_cmd *com = get_right_comm(msh , 0);
		proccesing_cmd(com, msh->env);
		printf("~~~~~~~~~ cmd = %s | infile = %d | outfile = %d\n", com->cmd_path , com->infile , com->outfile);
		// if(msh->child_nb > 1 || com->outfiles[0] || com->append[0])
		// 	dup2(msh->pipe[idx * 2 + 1], 1);
		// if(com->infile > 0 || com->infile == -2)
		// 	dup2(msh->pipe[0], 0);
		// close_all_pipes(msh);
		// execve(msh->comms->cmd_path, msh->comms->cmd_args, msh->env);
		if(com->infile == -1)
		{
			// perror("infile not found");
			ft_putstr_fd("testexit.\n", 2);
			exit(127);
		}
			
		exit(0);
	}

}

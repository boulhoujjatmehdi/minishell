/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:02:55 by eboulhou          #+#    #+#             */
/*   Updated: 2023/04/11 21:15:09 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int counter;
t_comm *new_comm(char **com, int idx)
{
	t_comm *new;
	new = malloc(sizeof(t_comm));
	new->com = com[0];
	new->flags = com;
	new->idx = idx;
	new->next = NULL;
	return new;
}

char *get_right_path(char *str, char **env)
{
	int i;
		
	i = 0;
	while(env[i])
	{
		if(!ft_strncmp(env[i], "PATH=", 5))
		{
			env = ft_split(env[i], '=');
			env = ft_split(env[1], ':');
			i = 0;
			while(env[i])
			{
				env[i] = ft_strjoin(env[i], ft_strjoin("/", str));
				if(!access(env[i], F_OK))
				{
					return ft_strdup(env[i]);
				}
				i++;
			}
			break;
		}
		i++;
	}
	return NULL;
}

void add_back_comm(t_comm **comms, t_comm *new)
{
	t_comm *tmp;

	tmp = *comms;
	if (!*comms)
		*comms = new;
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int get_comm_lenght(t_comm *comms)
{
	int i;
	
	i = 0;
	while(comms)
	{
		comms = comms->next;
		i++;
	}
	return i;
}

t_comm *ft_get_commands(char *str, char **env)
{
	char **ret = ft_split(str, '|');
	int i = 0;
	t_comm *comms;

	comms = NULL;
	while(ret[i])
	{
		// printf("%s\n************\n", ret[i]);
		char **com = ft_split(ret[i], ' ');
		t_comm *tmp = new_comm(com, i);
		tmp->com = get_right_path(tmp->com, env);
		add_back_comm(&comms, tmp);
		i++;
	}
	return comms;
}

int glob[100];
void	ft_pipe(int *fd, int *fd2)
{
	int i = 1;
	char *buffer;
	int pid = fork();

	
	if(!pid)
	{	
		close(fd[1]);
		close(fd2[0]);
		dup2(fd[0], 0);
		dup2(fd2[1], 1);
		i = read(fd[0], buffer, 500);
		while(i>0)
		{
			write(fd2[1], "390 test\nlkdjfka d\nklfjadjsfklajsd\n", 35);
			write(fd2[1], buffer, i);
			i = read(fd[0], buffer, 500);
		}
		close(fd[0]);
		close(fd2[1]);
	}
	exit(0);
}

void funct(t_comm *com, char **env, int token , int file_descriptors[2][2] , int *piid)
{
	int *fd;
	int *fd2;
	fd = file_descriptors[0];
	fd2 = file_descriptors[1];
	*piid = fork();
	if(!*piid)
	{
		if(token == 1)
		{
			close(fd[0]);
			close(fd2[1]);
			close(fd2[0]);
			dup2(fd[1], 1);
			execve(com->com, com->flags , env);
			
		}
		else if(token == 2)
		{
			close(fd2[1]);
			dup2(fd2[0], 0);
			execve(com->com, com->flags , env);
		}else if(token == 3)
		{
			// usleep(100000);
			close(fd[1]);
			close(fd2[0]);

			dup2(fd[0], 0);
			// dup2(fd2[1], 1);
			// puts("meheid\n");
			execve(com->com, com->flags , env);
		}
		exit(0);
	}
}

#define FT_PIPE 1
#define FT_PIPED 2
#define FT_REDIRECT 3


void first_child(int *fd, int *pid)
{
	pid[0] = fork();
	if(pid[0] == 0)
	{
		dup2(fd[1] , 1);
		//close all
		// printf("mehdi boulhoujjat\n");
		int ii = 0;
		while(ii < 10)
			close(fd[ii++]);
		//-------------
		char *c0[3];	c0[0] = strdup("/bin/ls");	c0[1] = strdup("-la");	c0[2] = NULL;
		t_comm *cc0 = new_comm (c0 , 0);
		char **env;
		env = NULL;
		// sleep(1);
		execve(cc0->com, cc0->flags, env);
	}
}

void middle_child(int *fdd, int *fd, int *pid , int i)
{
	pid[1] = fork();
	if(pid[1] == 0)
	{
		// sleep(8);
		dup2(fdd[0], 0);
		dup2(fdd[3], 1);
		//close all
		int ii = 0;
		while(ii < 10)
			close(fd[ii++]);
		//-------------
		char str[100];
		str[0] = '0' + i;
		str[1] = 0;
		char *c1[3];	c1[0] = strdup("/usr/bin/grep");	c1[1] = strdup(str);	c1[2] = NULL;
		t_comm *cc1 = new_comm (c1 , 1);
		char **env;
		env = NULL;
		execve(cc1->com, cc1->flags, env);
	}
}

void third_child(int *fdd ,int *fd, int *pid)
{
	pid[2] = fork();
	if(!pid[2])
	{
		dup2(fdd[0], 0);
		//close all
		int ii = 0;
		while(ii < 10)
			close(fd[ii++]);
		//-------------
		
		char *c2[3];	c2[0] = strdup("/usr/bin/wc");	c2[1] = strdup("-l");	c2[2] = NULL;
		t_comm *cc2 = new_comm (c2 , 2);
		char **env;
		env = NULL;
		execve(cc2->com, cc2->flags, env);
	}

}




//initialize the t_minishell data by opening the pipes needed
//set the number of pipes needed
//pipe_nb == 0, no pipe needed
//pipe_nb == -1, no command
void initialize_data(t_minishell *msh)
{
	int i;
	
	msh->pipe_nb = get_comm_lenght(msh->comms) - 1;
	msh->pipe = malloc (sizeof(int) * msh->pipe_nb);
	i = 0;
	while(i < msh->pipe_nb)
	{
		pipe(&msh->pipe[i * 2]);
		i++;
	}
}

int *open_pipes(int nb)
{
	int *fd;
	int i;

	i = 0;
	fd = malloc(sizeof(int) * nb);
	if(!fd)
		return NULL;
	while(i < nb)
	{
		pipe(&fd[ i * 2]);
		i++;
	}
	return fd;
}
// void fork_it_for_me()

int main(int ac , char **av, char **env) 
{
	char *str;
	int i;

	while(1)
	{
		t_minishell msh;

		str = readline("minishell $>");
		add_history(str);
		msh.comms = ft_get_commands(str, env);
		initialize_data(&msh);
		for(int j = 0; j < 3; j++)
		{
			printf("com = %s **||** flags = %s\n" , msh.comms->com ,msh.comms->flags[1]);
			msh.comms = msh.comms->next;
		}

		
		
	}
	return 0;
}





















// int main(int ac , char **av , char **env)
// {
//     int num_child_processes = 5;
//     int i = 0;
// 	int pid[100];
// 	bzero(pid, 4 * 100);
// 	int pd = 01;
// 	pid[0] = 1;
// 	t_comm *com;
// 	char *c0[3];	c0[0] = strdup("/bin/ls");	c0[1] = strdup("-la");	c0[2] = NULL;
// 	char *c1[3];	c1[0] = strdup("/usr/bin/grep");	c1[1] = strdup("18");	c1[2] = NULL;
// 	char *c2[3];	c2[0] = strdup("/usr/bin/grep");	c2[1] = strdup("pipex");	c2[2] = NULL;
	
// 	t_comm *cc0 = new_comm (c0 , 0);
// 	t_comm *cc1 = new_comm (c1 , 1);
// 	// char *c2[3];	c2[0] = strdup("/usr/bin/grep");	c2[1] = strdup("pipex");	c2[2] = NULL;
// 	t_comm *cc2 = new_comm (c2 , 2);
// 	int fd[2][2];
// 	pipe(fd[0]);
// 	pipe(fd[1]);
// 	while(i < 3)
// 	{
// 		int piid;
// 		if(i == 0)
// 		{
// 			funct(cc0, env, FT_PIPE , fd , &piid);
// 		}
// 		if(i == 1)
// 			funct(cc1, env, FT_REDIRECT, fd, &piid);
// 		if(i == 2)
// 			funct(cc2, env, FT_PIPED, fd, &piid);
// 		printf("-- %d -- \n", piid);
// 		i++;
// 	}
// 		close(fd[0][0]);
// 		close(fd[0][1]);
// 		close(fd[1][0]);
// 		close(fd[1][1]);
// 		waitpid(-1, NULL, 0);
// 	return 0;
// }


























































































// int main()
// {
// 	int i = 0;
	
// 	//open pipes
// 	int fd[100];
// 	pipe(&fd[0]);
// 	pipe(&fd[2]);
// 	pipe(&fd[4]);
// 	pipe(&fd[6]);
// 	pipe(&fd[8]);
// 	//-----------
// 	int pid[3] = {0};
// 	first_child(fd, pid);
// 	while(i < 3)
// 	{
// 		middle_child(&fd[i*2], fd, pid , i*2);
// 		printf("%d -- is the fd\n", fd[i*2]);
// 		i++;
// 	}
	
// 	third_child(&fd[(i)*2],fd ,  pid);
// 	int ii = 0;
// 	while(ii < 10)
// 		close(fd[ii++]);
// 	for (int j=0; j < 5; j++)
// 	{
// 		waitpid(-1 , NULL, 0);
// 	}

// }
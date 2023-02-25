/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:02:55 by eboulhou          #+#    #+#             */
/*   Updated: 2023/02/25 15:56:51 by eboulhou         ###   ########.fr       */
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
		char **com = ft_split(ret[0], ' ');
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
		puts("mehdi\n");
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
	// printf("%d __ %d __ %d __%d\n", fd[0], fd[1] , fd2[0], fd2[1]);
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


void first_child(int *fd1 , int *fd2, int *fd3, int *pid)
{
	pid[0] = fork();
	if(pid[0] == 0)
	{
		dup2(fd1[1] , 1);
		//close all
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		close(fd3[0]);
		close(fd3[1]);
		//-------------
		char *c0[3];	c0[0] = strdup("/bin/ls");	c0[1] = strdup("-la");	c0[2] = NULL;
		t_comm *cc0 = new_comm (c0 , 0);
		char **env;
		env = NULL;
		execve(cc0->com, cc0->flags, env);
	}
}

void middle_child(int *fd1 , int *fd2, int *fd3 , int *pid)
{
	pid[1] = fork();
	if(pid[1] == 0)
	{
		dup2(fd1[0], 0);
		dup2(fd2[1], 1);
		//close all
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		close(fd3[0]);
		close(fd3[1]);
		//-------------
		char *c1[3];	c1[0] = strdup("/usr/bin/grep");	c1[1] = strdup("eboulhou");	c1[2] = NULL;
		t_comm *cc1 = new_comm (c1 , 1);
		char **env;
		env = NULL;
		execve(cc1->com, cc1->flags, env);
	}
}

void third_child(int *fd1 , int *fd2, int *fd3 , int *pid)
{
	pid[2] = fork();
	if(!pid[2])
	{
		dup2(fd2[0], 0);
		//close all
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		close(fd3[0]);
		close(fd3[1]);
		//-------------
		char *c2[3];	c2[0] = strdup("/usr/bin/grep");	c2[1] = strdup("1");	c2[2] = NULL;
		t_comm *cc2 = new_comm (c2 , 2);
		char **env;
		env = NULL;
		execve(cc2->com, cc2->flags, env);
	}
}


int main()
{
	int i = 0;
	
	//open pipes
	int fd1[2];
	int fd2[2];
	int fd3[2];
	
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	//-----------
	int pid[3] = {0};
	first_child(fd1, fd2, fd3, pid);
	middle_child(fd1, fd2, fd3, pid);
	third_child(fd1, fd2, fd3, pid);
	
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	close(fd3[0]);
	close(fd3[1]);
	waitpid(-1 , NULL, 0);
	
	
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

// int main(int ac , char **av, char **env) 
// {
// 	char *str;
// 	int	fd[2];
// 	int ids[5];
// 	int i;
// 	ids[0] = 0;
// 	while(1)
// 	{
// 			t_comm *comms;

// 			str = readline("minishell $>");
// 			comms = ft_get_commands(str, env);
// 			// pipe(fd);

// 		i = 0;
// 		while (i < get_comm_lenght(comms))
// 		{
// 			if(!ids[0])
// 			{
// 				ids[i] = fork();
// 				printf("---i = %d-ids[%d] == %d--\n", i, i, ids[i]);
// 			}
// 			i++;
// 		}
// 		i = 0;
// 		// printf();
// 		// ids[0] = fork();
// 		// while(i--)
// 		// {
// 			if(!ids[0])
// 			{
// 				// close(fd[0]);
// 				// dup2(fd[1], 1);
// 				// puts(comms->com);
// 				// wait(NULL);
// 				puts("-------------------------\n");
// 				exit(0);
// 				// execve(comms->com, comms->flags, env);
// 				// puts("mehdi\n");
// 				// close(fd[1]);
// 			}
// 		// }
// 		if(ids[0])
// 		{
// 			// close(fd[0]);
// 			// wait(NULL);
// 			wait(NULL);
// 			puts("puts from parent process\n");
// 			// comms = NULL;
// 			// close(fd[1]);
// 		}



		
// 	}
// 		// t_comm *tmp = comms;
// 		// while(tmp)
// 		// {
// 		// 	printf("%s -- %s -- %s\n",tmp->com, tmp->flags[1], tmp->flags[2]);
// 		// 	tmp = tmp->next;
// 		// }
// 	return 0;
// }
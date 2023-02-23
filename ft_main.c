/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:02:55 by eboulhou          #+#    #+#             */
/*   Updated: 2023/02/23 21:52:44 by eboulhou         ###   ########.fr       */
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

int main(int ac , char **av , char **env)
{
    int num_child_processes = 5;
    int i = 0;
	int pid[100];
	// pid[0] = fork();
	int pd = 01;
	pid[0] = 1;
	
	while(i < 5)
	{
		if(pd)
		{
			pd  = fork();
			pid[i]= pd;
		}
		i++;
	}


	int k = 0;
	while(k < 5)
	{
		if(!pid[k++])
			printf("mehdi from --- %d\n", getpid());
	}


	
	int j = 4;
	if(pid[0])
	{
		while(j > -1)
		{
			if(pid[j])
			{
				waitpid(pid[j], NULL, 0);
			}
			j--;
		}
	}
	printf("-----(%d)-----(%d)-==%d\n", getpid(), getppid(), pid[0]);
}

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
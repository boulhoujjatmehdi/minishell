/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:02:55 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/01 15:51:30 by eboulhou         ###   ########.fr       */
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


#define FT_PIPE 1
#define FT_PIPED 2
#define FT_REDIRECT 3

void close_all_pipes(t_minishell *msh)
{
		int ii = 0;
		while(ii <= msh->pipe_nb*2)
		{
			close(msh->pipe[ii]);
			// msh->pipe[ii] = 0;
			close(msh->pipe[ii + 1]);
			// printf("closed --%d-- --%d--\n", msh->pipe[ii], msh->pipe[ii+1]);
			msh->pipe[ii + 1] = 0;
			ii += 2;
		}
}

void first_child(t_minishell *msh)
{
	int pid;
	int i;
	
	i = 0;
	pid = fork();
	if(pid == 0)
	{
		// if(msh->child_nb > 1)
			dup2(msh->pipe[1] , 1);

		close_all_pipes(msh);

		execve(msh->comms->com, msh->comms->flags, msh->env);
	}
}

void middle_child(t_minishell *msh, int idx)
{
	int pid;

	pid = fork();
	if(pid == 0)
	{
		dup2(msh->pipe[(idx - 1) * 2], 0);
		dup2(msh->pipe[idx * 2 + 1], 1);

		close_all_pipes(msh);

		execve(msh->comms->com, msh->comms->flags, msh->env);
	}
}

void last_child(t_minishell *msh, int idx)
{
	int pid;

	pid = fork();
	if(pid == 0)
	{
		dup2(msh->pipe[(idx - 1) * 2], 0);
		// dup2(msh->pipe[idx*2 + 1])
		close_all_pipes(msh);

		execve(msh->comms->com, msh->comms->flags, msh->env);
	}
}
void printer_child(t_minishell *msh, int idx)
{
	int pid;

	pid = fork();
	if(pid == 0)
	{
		dup2(msh->pipe[(idx - 1) * 2], 0);
		close_all_pipes(msh);
		char str[11];
		int i = 0;
		while((i = read(0, str, 10)))
		{
			write(1, str, i);
		}
		// execve(msh->comms->com, msh->comms->flags, msh->env);
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
	msh->child_nb = msh->pipe_nb + 1;
	msh->pipe = malloc (sizeof(int) * msh->pipe_nb);
	i = 0;
	while(i < msh->pipe_nb)
	{
		pipe(&msh->pipe[i * 2]);
		i++;
	}
}


void  open_pipes(t_minishell *msh)
{
	int i;

	i = 0;
	msh->pipe = malloc(sizeof(int) * msh->pipe_nb);
	bzero(msh->pipe, sizeof(int)*msh->pipe_nb);
	if(!msh->pipe)
	{
		msh->pipe = NULL;
		return ;
	}
	while(i <= msh->pipe_nb)
	{
		printf("%d \n" , msh->pipe_nb);
		pipe(&msh->pipe[i * 2]);
		i++;
	}
}

void fork_it_for_me(t_minishell *msh)
{
	int i;
	int j;
	
	j = 2;
	i = 1;
	if(msh->child_nb > 1)
	{
		first_child(msh);
		while(j <= msh->child_nb)
		{
			
			msh->comms = msh->comms->next;
			middle_child(msh , i++);
			j++;	
		}
		// msh->comms = msh->comms->next;
		// last_child(msh, i);
	}
	else if(msh->child_nb == 1)
	{
		first_child(msh);
		// i++;
	}
	printer_child(msh , i);
}

/* -----------------MAIN FUNCTION----------------- */
int main(int ac , char **av, char **env) 
{
	char *str;
	int i;
	t_minishell msh;
	
	msh.env = env;
	add_history("ls -la | grep ft | grep 1");
	add_history("cat Makefile");
	while(1)
	{
		
		str = readline("minishell $>");	
		add_history(str);
		// rl_redisplay();
		rl_on_new_line();
		msh.comms = ft_get_commands(str, env);
		initialize_data(&msh);
		open_pipes(&msh);
		fork_it_for_me(&msh);
		while(1 + msh.pipe_nb--)
		{
			waitpid(-1 , NULL, 0);
		}
		close_all_pipes(&msh);
	}

	return 0;
}

// int main() {
//     char* line;
//     rl_initialize();

//     while ((line = readline("> ")) != NULL) {
//         // Do something with the input
//         printf("You entered: %s\nkljs\nmehdi", line);
//         // Move the cursor to a new line
//         rl_on_new_line();
//         // Free the input buffer
//         free(line);
//     }

//     return 0;
// }
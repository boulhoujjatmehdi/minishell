/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:02:55 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/03 21:54:30 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void close_all_pipes(t_minishell *msh)
{
		int ii = 0;
		while(ii <= msh->pipe_nb*2)
		{
			close(msh->pipe[ii]);
			close(msh->pipe[ii + 1]);
			// printf("closed --%d-- --%d--\n", msh->pipe[ii], msh->pipe[ii+1]);
			ii += 2;
		}
}

//*****************************************************************************************************************************************************************************
//*****************************************************************************************************************************************************************************
//*****************************************************************************************************************************************************************************

void first_child(t_minishell *msh , int *pid)
{
	// int pid;
	*pid = fork();
	if(*pid == 0)
	{
		sleep(1);
		printf("hello from the first child id = %d\n" , getpid());
		exit(11);
		dup2(msh->pipe[1], 1);
		close_all_pipes(msh);

		execve(msh->comms->com, msh->comms->flags, msh->env);
		exit(10);
	}
	else
		printf("-------- pid = %d first\n", *pid);
}

void middle_child(t_minishell *msh, int idx , int *pid)
{


	*pid = fork();
	if(*pid == 0)
	{
		printf("hello from the child number %d\n", idx);
		exit(idx);
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
		printf("hello from the last child number %d id = %d \n", idx , getpid());
		exit(idx);
		dup2(msh->pipe[(idx - 1) * 2], 0);
		dup2(msh->pipe[idx * 2 + 1], 1);

		close_all_pipes(msh);

		execve(msh->comms->com, msh->comms->flags, msh->env);
	}
}

void printer_child(t_minishell *msh, int idx, int *pid)
{

	*pid = fork();
	if(*pid == 0)
	{
		printf("hello from the printer child number %d id = %d\n", idx , getpid());
		exit(idx);
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
	else
		printf("======== pid = %d printer\n", *pid);
}


//*****************************************************************************************************************************************************************************
//*****************************************************************************************************************************************************************************
//*****************************************************************************************************************************************************************************


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
		// printf("%d \n" , msh->pipe_nb);
		pipe(&msh->pipe[i * 2]);
		i++;
	}
	// msh->pipe = malloc(3*3);
	// pipe(msh->pipe);
}

void wait_for_all(int *pids , int nb)
{
	int i;

	i = 0;
	while(i <= nb)
	{
		waitpid(pids[i], NULL, 0);
		// printf("%d -- " , pids[i]);
		// printf("\n");
		i++;
	}
	// i = 0;
	// while(i < nb)
	// {
	// 	i++;
	// }
}

void fork_it_for_me(t_minishell *msh)
{
	int i;
	int j;
	
	j = 2;
	i = 1;
	int pid[500];
	if(msh->child_nb > 1)
	{
		first_child(msh, pid);
		waitpid(pid[0], NULL, 0);
		while(j < msh->child_nb)
		{
			
			msh->comms = msh->comms->next;
			middle_child(msh , i , &pid[i]);
			waitpid(pid[i], NULL, 0);

			i++;
			j++;
		}
		msh->comms = msh->comms->next;
		last_child(msh, i);
		waitpid(pid[i], NULL, 0);
		i++;
		
	}
	else
	if(msh->child_nb == 1)
	{
		first_child(msh , pid);
		waitpid(pid[i], NULL, 0);
	}
	printer_child(msh , i , &pid[i]);
		waitpid(pid[i], NULL, 0);
	// wait_for_all(pid, msh->child_nb);
	// pause();


}

/* -----------------MAIN FUNCTION----------------- */
int main(int ac , char **av, char **env) 
{
	char *str;
	int i;
	t_minishell msh;
	
	msh.env = env;
	add_history("ls -la | grep ft | grep 1");
	add_history("cat Makefile | grep me");
	add_history("cat Makefile");
	while(1)
	{
		
		str = readline("minishell $> ");	
		add_history(str);
		// rl_redisplay();
		msh.comms = ft_get_commands(str, env);
		initialize_data(&msh);
		open_pipes(&msh);
		fork_it_for_me(&msh);
		// pause();
		
		// sleep(3);
		close_all_pipes(&msh);
		while(1 + msh.pipe_nb--)
		{
			waitpid(-1 , NULL, 0);
		}
		rl_on_new_line();
	}

	return 0;
}


// void fn(int i , ...)
// {
// 	va_list mehdi;
// 	va_start(mehdi, i);
// 	int jj = va_arg(mehdi, int);
// 	jj += va_arg(mehdi, int);
// 	printf("%d \n", jj);
// }
// int main()
// {
	
// 	fn(2 , 3 , 5);
// }
// int main() {
// 	int fd = open("Makefile", O_RDONLY);
// 	char *str = get_next_line(fd);
// 	while(str)
// 	{
// 		write(1, str , ft_strlen(str));
		
// 		str = get_next_line(fd);
// 	}
	
// }
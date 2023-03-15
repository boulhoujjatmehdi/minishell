/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:02:55 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/15 09:44:39 by eboulhou         ###   ########.fr       */
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
//pipe_nb == 0, no pipe needed
//pipe_nb == -1, no command

int get_nb_of_pipes(t_comm *comms)
{
	int i;
	
	i = 0;
	while(comms)
	{
		if(*comms->infiles)
			i++;
		if(*comms->outfiles)
			i++;
		comms = comms->next;
		i++;
	}
	return i;
	
}

void initialize_data(t_minishell *msh)
{
	int i;

	msh->pipe_nb = get_nb_of_pipes(msh->comms) -1 ;
	msh->child_nb = get_comm_lenght(msh->comms);
	// printf("*/*/*/*/*/**/*/*/*/ %d\n", msh->child_nb);
}


void  open_pipes(t_minishell *msh)
{
	int i;

	i = 0;
	msh->pipe = malloc (sizeof(int) * msh->pipe_nb * 2 + 2 );

	if(!msh->pipe)
	{
		msh->pipe = NULL;
		return ;
	}
	while(i <= msh->pipe_nb)
	{

		pipe(&msh->pipe[i * 2]);
		// printf("(%d _-_-_ %d)\n", msh->pipe[i * 2], msh->pipe[i * 2 + 1]);
		i++;

	}
}

void wait_for_all(int *pids , int nb)
{
	int i;

	i = 0;
	while(i <= nb)
	{
		waitpid(pids[i], NULL, 0);
		// printf("watied for pids[%d] == %d\n", i , pids[i]);
		i++;
	}
}

void fork_it_for_me(t_minishell *msh)
{
	int i;
	int j;
	int k;
	int *pid;
	
	i = 0;
	j = 2;
	k = 0;
	pid = malloc(sizeof(int) * msh->pipe_nb);
	if(msh->child_nb > 1)
	{
		
		//////////////////////////////////////////////////////////////////////////////////////////
		// puts("testme");
		if(*msh->comms->infiles)
		{
			infiles_child(msh, i, k ,  pid);
			k++;
		}
		first_child(msh , k,  &pid[k]);
		k++;
		if(*msh->comms->outfiles)
		{
			outfiles_child(msh, i, k, &pid[k]);
			k++;
		}
		//////////////////////////////////////////////////////////////////////////////////////////
		i++;
		while(j < msh->child_nb)
		{
			// printf("*/*/*/***/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/**\n");
			t_comm * com = get_right_comm(msh, i);
			if(get_right_comm(msh, i)->infiles[0])
			{
				infiles_child(msh, i, k ,  &pid[k]);
				k++;
			}
			middle_child(msh , i , k, &pid[k]);
			k++;
			if(get_right_comm(msh, i)->outfiles[0])
			{
				outfiles_child(msh, i, k, &pid[k]);
				k++;
			}
			i++;
			j++;
			//this part need some work to be right
		}

		//////////////////////////////////////////////////////////////////////////////////////////
		t_comm * com = get_right_comm(msh, i);
		if(*com->infiles)
		{
			infiles_child(msh, i, k ,  &pid[k]);
			k++;
		}
		last_child(msh,i , k, &pid[k]);
		k++;
		if(*com->outfiles)
		{
			outfiles_child(msh, i, k, &pid[k]);
			k++;
		}
		//////////////////////////////////////////////////////////////////////////////////////////
	}
	else
	if(msh->child_nb == 1)
	{
		// printf("////////////////////\n");
		if(*msh->comms->infiles)
		{
			infiles_child(msh, i, k ,  pid);
			k++;
		}
		first_child(msh , k,  &pid[k]);
		k++;
		if(*msh->comms->outfiles)
		{
			outfiles_child(msh, i, k, &pid[k]);
		}
		
	}
	close_all_pipes(msh);
	wait_for_all(pid, msh->pipe_nb);
	free(pid);

}
void ft_free_msh(t_minishell msh)
{
	ft_free_commands(msh.comms);
	free(msh.pipe);
}
// int inter;
// void signal_handler(int sig)
// {
// 	if(sig == SIGINT)
// 	{
// 		inter = 1;
// 		// close(1);
// 		puts("");
// 		rl_forced_update_display();
// 		rl_redisplay();
// 		// rl_cleanup_after_signal();
// 	}
// }

/* -----------------MAIN FUNCTION----------------- */
int main(int ac , char **av, char **env) 
{
	char *str;
	int i;
	t_minishell msh;
	
	msh.env = env;
	add_history("ls -la | grep ft | grep 1");
	add_history("cat Makefile | grep me");
	add_history("ls -la | grep ft | grep 1 | ls -la | grep ft");
	add_history("ls -la | grep ft | grep 15: | grep ft_m | grep ma | cat Makefile | grep me");
	add_history("cat > text.txt");
	add_history("cat < outerr >out | cat -e");
	add_history("cat < outerr >out ");
	add_history("cat < outerr >out | cat -e < out999 > out1 | cat ");
	
	
	while(1)
	{
		// // rl_on_new_line();
		// signal(SIGINT, *signal_handler);
		str = readline("minishell $> ");
		// str = NULL;
		// rl_replace();
		// puts("mehdiboulhoujjat\n");
		add_history(str);
		ft_get_commands(&msh, str, env);
		initialize_data(&msh);
		open_pipes(&msh);
		
		fork_it_for_me(&msh);
		ft_free_msh(msh);
		free(str);
	}
	return 0;
}


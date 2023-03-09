/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:02:55 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/09 15:56:26 by eboulhou         ###   ########.fr       */
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
		{
			i++;
		}
		comms = comms->next;
		i++;
	}
	return i;
	
}

void initialize_data(t_minishell *msh)
{
	int i;

	msh->pipe_nb = get_nb_of_pipes(msh->comms) - 1;
	msh->child_nb = get_comm_lenght(msh->comms);
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
		i++;
	}
}

void fork_it_for_me(t_minishell *msh)
{
	int i;
	int j;
	int *pid;
	
	j = 2;
	i = 1;
	pid = malloc(sizeof(int) * msh->child_nb);
	if(msh->child_nb > 1)
	{
		first_child(msh, pid);
		while(j < msh->child_nb)
		{
			middle_child(msh , i , &pid[i]);
			i++;
			j++;
		}
		last_child(msh, i, &pid[i]);
		i++;
	}
	else
	if(msh->child_nb == 1)
	{
		first_child(msh , pid);
	}
	// printer_child(msh , 0 , &pid[i]);
	// printer_child(msh , 1 , &pid[i]);
	// printer_child(msh , 2 , &pid[i]);
	


		// puts(msh.comms->infiles[0]);
	
	close_all_pipes(msh);
	wait_for_all(pid, msh->child_nb);
	free(pid);

}
void ft_free_msh(t_minishell msh)
{
	ft_free_commands(msh.comms);
	free(msh.pipe);
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
	add_history("ls -la | grep ft | grep 1 | ls -la | grep ft");
	add_history("ls -la | grep ft | grep 15: | grep ft_m | grep ma | cat Makefile | grep me");
	add_history("cat > text.txt");
	add_history("cat < outerr >out | cat -e");
	add_history("cat < outerr >out ");
	while(1)
	{
		rl_on_new_line();
		str = readline("minishell $> ");	
		add_history(str);
		ft_get_commands(&msh, str, env);
		// t_comm *coo = msh.comms;
		// while(coo)
		// {
		// 	printf("com = %s , flag1 = -%s- , flag2 = -%s-\n", coo->com, coo->flags[1], coo->flags[2]);
		// 	coo = coo->next;
		// }
		initialize_data(&msh);
		open_pipes(&msh);

		fork_it_for_me(&msh);
		ft_free_msh(msh);
		free(str);
		rl_redisplay();
	}
	return 0;
}


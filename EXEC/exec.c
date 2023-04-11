/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:59:28 by eboulhou          #+#    #+#             */
/*   Updated: 2023/04/11 13:34:12 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void wait_for_all(int *pids , int nb)
{
	int i;

	i = 0;
	while(i < nb)
	{
		int status= 0;
		waitpid(pids[i], &status, 0);
		printf("watied for pids[%d] == %d || status = %d\n", i , pids[i] ,status >> 8);
		i++;
	}
}

void close_all_pipes(t_minishell *msh)
{
		int ii = 0;
		while(ii < msh->pipe_nb*2)
		{
			close(msh->pipe[ii]);
			close(msh->pipe[ii + 1]);
			// printf("closed --%d-- --%d--\n", msh->pipe[ii], msh->pipe[ii+1]);
			ii += 2;
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
		// // puts("testme");
		
		// if(msh->comms->infile == -2 || msh->comms->infile > 0)
		// {
		// 	infiles_child(msh, i, k ,  pid);
		// 	k++;
		// }
		// first_child(msh , k,  &pid[k]);
		// k++;
		// if(*msh->comms->outfiles || *msh->comms->append) // this is when we stoped 
		// {
		// 	outfiles_child(msh, i, k, &pid[k]);
		// 	k++;
		// }
		// //////////////////////////////////////////////////////////////////////////////////////////
		// i++;
		// while(j < msh->child_nb)
		// {
		// 	// printf("*/*/*/***/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/**\n");
			
		// 	t_comm * com = get_right_comm(msh, i);
		// 	if(*com->infiles)
		// 	{
		// 		infiles_child(msh, i, k ,  &pid[k]);
		// 		k++;
		// 	}
		// 	middle_child(msh , i , k, &pid[k]);
		// 	k++;
		// 	if(*com->outfiles || *com->append)
		// 	{
		// 		outfiles_child(msh, i, k, &pid[k]);
		// 		k++;
		// 	}
		// 	i++;
		// 	j++;
		// 	//this part need some work to be right
		// }

		// //////////////////////////////////////////////////////////////////////////////////////////
		// t_comm * com = get_right_comm(msh, i);
		// if(*com->infiles)
		// {
		// 	infiles_child(msh, i, k ,  &pid[k]);
		// 	k++;
		// }
		// last_child(msh,i , k, &pid[k]);
		// k++;
		// if(*com->outfiles || *com->append)
		// {
		// 	outfiles_child(msh, i, k, &pid[k]);
		// 	k++;
		// }
		// //////////////////////////////////////////////////////////////////////////////////////////
	}
	else
	if(msh->child_nb == 1)
	{
        // if(msh->comms->infile == -2 || msh->comms->infile > 0)
        // {
        //     infiles_child(msh, i, k ,  pid);
        //     k++;
        // }
		// puts(msh->env[0]);

		// puts("mehdi***");
		// puts(msh->env[0]);

        first_child(msh , k,  &pid[k]);
        k++;
        // if(msh->comms->outfile)
        // {
        //     // outfiles_child(msh, i, k, &pid[k]);
        // }
	}
	close_all_pipes(msh);
	wait_for_all(pid, msh->pipe_nb);
	free(pid);
}


void  open_pipes(t_minishell *msh)
{
	int i;

	i = 0;
	msh->pipe = malloc (sizeof(int) * (msh->pipe_nb + 1) * 2  );

	if(!msh->pipe)
	{
		msh->pipe = NULL;
		return ;
	}
	while(i < msh->pipe_nb)
	{
		pipe(&msh->pipe[i * 2]);
        // printf("%d -- %d\n", msh->pipe[i] ,msh->pipe[i+1] );
		i++;
	}
}

void initialize_data(t_minishell *msh)
{
	int i;

	// msh->pipe_nb = get_nb_of_pipes(msh->comms);
	msh->child_nb = get_comm_lenght(msh->comms);
	msh->pipe_nb = msh->child_nb;
								// printf("*/*/*/*/*/**/*/*/*/ %d\n", msh->pipe_nb);
								// printf("*/*/*/*/*/**/*/*/*/ %d\n", msh->child_nb);
}

int main_function_exec(t_cmd *comms , char **env)
{
    t_minishell *msh;
    msh = ft_calloc(sizeof(t_minishell), 1);
	msh->env = env;
    msh->comms = comms;
				// printf("~~~~~~~~~~%d , %d\n", msh->child_nb , msh->pipe_nb);
    
    initialize_data(msh);
    open_pipes(msh);
	
	fork_it_for_me(msh);
	
    // t_cmd *head = msh->comms;
    // puts("hello from mainFunctionExec");
    // while (head)
    // {
	// 	proccesing_cmd(head , env);
    //     puts("**********************************************************************************************************");
    //     printf("str === :%s:\ninfile %d --- outfile %d ---  cmd :%s:, here_doc --> %s\n", head->str, head->infile, head->outfile, head->cmd_path, head->her_doc);
    //     int i = 0;
    //     while (head->cmd_args[i])
    //         printf("opts == %s\n", head->cmd_args[i++]);
    //     head = head->next;
    // }


    
    return (0);
}
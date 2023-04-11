/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:52:15 by eboulhou          #+#    #+#             */
/*   Updated: 2023/04/11 21:14:21 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void first_child(t_minishell *msh , int idx, int *pid)
{
	t_cmd *com;

	*pid = fork();
	if(*pid == 0)
	{
		com = get_right_comm(msh , 0);
		proccesing_cmd(com, msh->env);
	
		if(com->infile > 0)
			dup2(com->infile, 0);
		if(com->outfile != 1)
			dup2(com->outfile, 1);
		if(execve(msh->comms->cmd_path, msh->comms->cmd_args, msh->env) == -1)
			exit(12);
	}

}

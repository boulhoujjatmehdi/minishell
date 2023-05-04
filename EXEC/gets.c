/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:35:07 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/04 14:03:13 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int get_comm_lenght(t_cmd *comms)
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

int get_nb_of_pipes(t_cmd *comms)
{
	int i;
	
	i = 0;
	while(comms)
	{
		if(comms->infile > 0 || comms->infile == -2)
			i++;
		i++;
		comms = comms->next;
	}
	return i;
}

t_cmd *get_right_comm(t_minishell *msh, int idx)
{
	t_cmd *tmp;
	tmp = msh->comms;
    int i = 0;
	while(i < idx)
	{
		tmp = tmp->next;
        i++;
		if(i == idx)
			return tmp;
	}
	
	return tmp;
}

void fill_env_list(t_list **lenv, char **env)
{
	while(*env)
	{
		ft_lstadd_back(lenv, ft_lstnew(ft_strdup(*env)));
		env++;
	}
}

char *get_path_line(t_list *lenv)
{
    while(lenv)
    {
        if(ft_strncmp(lenv->content, "PATH=", 5))
        {
            return(lenv->content);
        }
    }
    return "";
}
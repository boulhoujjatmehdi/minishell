/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:48:00 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/12 14:55:17 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"


t_comm *new_comm(char **com, int idx)
{
	t_comm *new;
	new = malloc(sizeof(t_comm));
	new->com = com[0];
	new->flags = com;
	new->idx = idx;
	new->next = NULL;
	new->prev = NULL;
	new->infiles = NULL;
	new->outfiles = NULL;
	return new;
}

char *get_right_path(char *str, char **env)
{
	int i;
	char **path;
	i = 0;
	while(env[i])
	{
		if(!ft_strncmp(env[i], "PATH=", 5))
		{
			// env = ft_split(env[i], '=');
			// ft_free_mat(env);
			path = ft_split(&env[i][5], ':');
			i = 0;
			while(path[i])
			{
				char *str1 = ft_strjoin("/", str);
				path[i] = ftt_strjoin(path[i], str1);
				free(str1);
				if(!access(path[i], F_OK))
				{
					char *strr = ft_strdup(path[i]);
					ft_free_mat(path);
					return strr;
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
	t_comm *prevtmp;
	
	tmp = *comms;
	if (!*comms)
	{
		*comms = new;
	}
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
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

void ft_free_mat(char **mat)
{
	int i;

	i = 0;
	while(mat[i])
	{
		free(mat[i]);
		i++;
	}	
	free(mat);
}

t_comm *ft_get_commands(t_minishell *msh, char *str, char **env)
{
	char **ret = ft_split(str, '|');
	int i = 0;
	t_comm *comms;
	char **com;
	char **inputs;
	char **outputs;
	// *inputs = NULL;
	// *outputs = NULL;
	com = NULL;
	comms = NULL;
	while(ret[i])
	{
		inputs = ft_calloc(sizeof(char *) , 10);
		outputs = ft_calloc(sizeof(char *) , 10);
		ft_replace(ret[i], '\'', ' ', '|');
		combine_rdir(inputs, outputs, ret[i]);
		com  = ft_split(ret[i], ' ');
		ft_replace_mat(com, '\'', '|', ' ');
		t_comm *tmp = new_comm(com, i);
		tmp->infiles = inputs;
		tmp->outfiles = outputs;
		tmp->com = get_right_path(tmp->com, env);
		// puts(tmp->infiles[0]);
		add_back_comm(&comms, tmp);
		inputs = NULL;
		outputs = NULL;
		i++;
	}
	ft_free_mat(ret);
	msh->comms = comms;
	return comms;
}

void ft_free_commands(t_comm *comms)
{
	t_comm *tmp;
	while(comms)
	{
		tmp = comms;
		free(comms->com);
		comms->com = NULL;
		ft_free_mat(comms->flags);
		free(tmp);
		comms = comms->next;
	}
}
void ft_free_command(t_comm *comms)
{
	t_comm *tmp;
	if(comms)
	{
		tmp = comms;
		free(comms->com);
		comms->com = NULL;
		ft_free_mat(comms->flags);
		free(tmp);
	}
}

t_comm *get_right_comm(t_minishell *msh, int idx)
{
	t_comm *tmp;
	tmp = msh->comms;
	while(tmp)
	{
		if(tmp->idx == idx)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}
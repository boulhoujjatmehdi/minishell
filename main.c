/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:35:53 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/18 20:16:16 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"


void signal_handler(int sig)
{
	if(sig == SIGINT)
	{
		rl_redisplay();
		ft_putstr_fd("  \n",1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_msh->stat =1;
	}
}

void	sigquit_handler(int sig)
{
	if(sig == 3)
	{
		rl_on_new_line();
		rl_replace_line(NULL, 1);
		rl_redisplay();
	}
	return ;
}

int skip_char(char *str, char c)
{
	int i;

	i = 0;
	while(str[i] && str[i] == c)
		i++;
	return i;
}
void free_cmd_mehdi(t_cmd **head)
{
	t_cmd *hd;
	t_cmd *tmp;

	hd = *head;
	while(hd)
	{
		if(hd->cmd_path)
			free(hd->cmd_path);
		free_2darrary(hd->cmd_args);
		if(hd->str)
			free(hd->str);
		tmp = hd;
		hd = hd->next;
		free(tmp);
	}
}

int main(int ac, char **av, char **env)
{
	t_cmd	*head;
	t_list  *lenv;

	g_msh = ft_calloc(sizeof(t_minishell), 1);
	char *str;
	lenv = NULL;
	fill_env_list(&lenv, env);//to check

	add_history("ls -la");
	while(1)
	{
		g_msh->last_st = g_msh->exit_st;
			if(g_msh->exit_st == -1)
					g_msh->last_st = 0;
		signal(SIGINT, &signal_handler);
		signal(SIGQUIT, &sigquit_handler);

		str = readline("minishell->");
		if(str== NULL)
			exit(g_msh->exit_st);

		if(*str && str[skip_char(str, ' ')] != 0)
		{
			g_msh->exit_st = -1;
			add_history(str);
			head = main_function(ac, str, &lenv);
			if(head)
			{
				execution_function(head , &lenv);
			}
			else
				g_msh->exit_st = 2;
		}
		if(g_msh->stat)
		{
			if(g_msh->exit_st != -1)
				g_msh->exit_st = 130;
			else 
				g_msh->exit_st = g_msh->stat;
		}
		g_msh->stat = 0;
	}
}

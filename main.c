/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:35:53 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/19 15:23:18 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_redisplay();
		ft_putstr_fd("  \n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		g_msh->stat = 1;
	}
}

void	sigquit_handler(int sig)
{
	if (sig == 3)
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

int	skip_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	return (i);
}

void	ft_rd_and_run(t_cmd **head, t_list **lenv)
{
	char	*str;

	str = readline("minishell->");
	if (str == NULL)
		exit(g_msh->exit_st);
	if (*str && str[skip_char(str, ' ')] != 0)
	{
		g_msh->exit_st = -1;
		add_history(str);
		*head = main_function(0, str, lenv);
		if (*head)
		{
			execution_function(*head, lenv);
			free_cmdlist(*head);
		}
		else
			g_msh->exit_st = 2;
	}
	free(str);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	*head;
	t_list	*lenv;

	(void)ac;
	(void)av;
	g_msh = ft_calloc(sizeof(t_minishell), 1);
	lenv = NULL;
	fill_env_list(&lenv, env);
	while (1)
	{
		g_msh->last_st = g_msh->exit_st;
		if (g_msh->exit_st == -1)
				g_msh->last_st = 0;
		signal(SIGINT, &signal_handler);
		signal(SIGQUIT, &sigquit_handler);
		ft_rd_and_run(&head, &lenv);
		if (g_msh->stat)
		{
			if (g_msh->exit_st != -1)
				g_msh->exit_st = 130;
			else
				g_msh->exit_st = g_msh->stat;
		}
		g_msh->stat = 0;
	}
}

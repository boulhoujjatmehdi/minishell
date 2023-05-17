/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:35:53 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/17 12:23:39 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int g_exit = -1;
int stat;

void signal_handler(int sig)
{
	if(sig == SIGINT)
	{
        waitpid(-1, NULL, 0);
		rl_redisplay();
		ft_putstr_fd("\n",1);
		rl_on_new_line();
		rl_redisplay();
        stat =1;
	}
}
int skip_char(char *str, char c)
{
    int i;

    i = 0;
    while(str[i] && str[i] == c)
        i++;
    return i;
}


int main(int ac, char **av, char **env)
{
    
    t_cmd	*head;
    t_list  *lenv;

    g_msh = ft_calloc(sizeof(t_minishell), 1);
    char *str;
    lenv = NULL;
	fill_env_list(&lenv, env);
    while(1)
    {
        signal(SIGINT, *signal_handler);
        // ft_putnbr_fd(g_exit, 1);
        // ft_putstr_fd("\n", 1);
        // g_exit = -1;
        str = readline("minishell->");
        // str = get_next_line(0);
        if(str== NULL)
        {
			exit(g_msh->exit_st);
        }
        // if(*str )
            
        if(*str&& str[skip_char(str, ' ')] != 0)
        {
            // str[ft_strlen(str)-1] = 0;
                
            add_history(str);
            head = main_function(ac, str, &lenv);
            if(head)
			{
				g_msh->last_st = g_msh->exit_st;
                if(g_msh->exit_st == -1)
                        g_msh->last_st = 0;
                g_msh->exit_st = -1;
                main_function_exec(head , &lenv);
			}
            else
                g_msh->exit_st = 2;
        }
        if(stat)
        {
            if(g_msh->exit_st != -1)
                g_msh->exit_st = 130;
            else 
                g_msh->exit_st = stat;
        }
        stat = 0;
    }
}





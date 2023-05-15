/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:35:53 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/15 14:05:32 by eboulhou         ###   ########.fr       */
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
		// rl_replace_line("", 0);
		rl_redisplay();
        stat =1;
	}
}

int main2(int ac, char **av, char **env)
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
        // str = readline("minishell->");
        str = get_next_line(0);
        if(str== NULL)
        {
			exit(g_msh->exit_st);
            
        }
        if(*str)
        {
            str[ft_strlen(str)-1] = 0;
            add_history(str);
            head = main_function(ac, str, &lenv);
            if(head)
			{
				g_msh->exit_st = -1;
                main_function_exec(head , &lenv);
			}
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
        return g_msh->exit_st;
}

int main(int ac, char **av, char **env)
{
    
    // add_history("cat <out <<eof | cat -e");
    // add_history("echo $PATH");
    // add_history("cat -e <<eof");
    main2(ac, av, env);
    return g_msh->exit_st;

}




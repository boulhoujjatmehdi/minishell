/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:35:53 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/10 14:46:00 by eboulhou         ###   ########.fr       */
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
		rl_replace_line("", 0);
		rl_redisplay();
        stat =1;
	}
}

int main(int ac, char **av, char **env)
{
    t_cmd	*head;
    t_list  *lenv;
    char *str;
    lenv = NULL;
	fill_env_list(&lenv, env);
    add_history("cat <out <<eof | cat -e");
    add_history("echo $PATH");
    add_history("cat -e <<eof");
    while(1)
    {
        signal(SIGINT, *signal_handler);
        // ft_putnbr_fd(g_exit, 1);
        // ft_putstr_fd("\n", 1);
        g_exit = -1;
        str = readline("minishell->");
        if(str== NULL)
			exit(0);
        if(*str)
        {
            add_history(str);
            head = main_function(ac, str, &lenv);
            if(head)
                main_function_exec(head , &lenv);
        }
        if(stat)
        {
            if(g_exit != -1)
                g_exit = 130;
            else 
                g_exit = stat;
        }
        stat = 0;
        // mainfunctiongoto:
        // t_list *tmp = lenv;
        // while(tmp)
        // {
        //     printf("%s\n======", tmp->content);
        //     tmp = tmp->next;
        // }


        // while (head)
        // {
        //     puts("**********************************************************************************************************");
        //     printf("str === :%s:\ninfile %d --- outfile %d -  cmd :%s:, here_doc --> %s\n", head->str, head->infile, head->outfile, head->cmd_path, head->her_doc);
        //     int i = 0;
        //     while (head->cmd_args[i])
        //         printf("opts == %s\n", head->cmd_args[i++]);
        //     head = head->next;
        // }
    }
}




// fd[1]   * file.txt
// 1       * stdout

// dup2(fd[1], 1);

// 1       * file.txt

// 1
// -------------------
// fd0             fd
// -------------------





// fd[0]   * file.txt
// 0       * stdin


// dup2(fd[0], 0);

// 0       * file.txt


// ft_putstr_fd("mehdi", 1);
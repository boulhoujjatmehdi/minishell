/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:35:53 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/04 14:33:21 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"



int main(int ac, char **av, char **env)
{
    t_cmd	*head;
    t_list  *lenv;
    char *str;
    lenv = NULL;
	fill_env_list(&lenv, env);
    add_history("cat <out | cat -e");
    add_history("cat <out <<eof | cat -e");
    add_history("echo $PATH");
    while(1)
    {
        str = readline("minishell->");
        if(str== NULL)
			exit(0);
		rl_redisplay();
        add_history(str);
        // env[0] = get_path_line(lenv);
        // env[1] = 0;
        // char **sstr = ft_calloc(sizeof(char*), 2);
        // sstr[0] = ft_strdup(get_path_line(lenv));
        // if(!sstr[0])
        //     sstr[0] = ft_calloc(sizeof(char *), 1);
        head = main_function(ac, str, env);
        main_function_exec(head , &lenv);
        
        





        
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
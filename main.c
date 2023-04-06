/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:35:53 by eboulhou          #+#    #+#             */
/*   Updated: 2023/04/06 17:17:37 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "parser/parse.h"

int main(int ac, char **av, char **env)
{
    t_cmd		*head;
    char *str;
    add_history("cat <infile > boulhoujjat <<here -ls -la ");
    add_history("cat <infile > boulhoujjat <<here -ls -la | ls -la | cat -e");
    while(1)
    {
        str = readline("minishell->");
        head = main_function(ac, str, env);
        
        
        
        
        
        
        
        // while (head)
        // {
        //     printf("**********************************************\nstr === :%s:\ninfile %d --- outfile %d -  cmd :%s:, here_doc --> %s\n", head->str, head->infile, head->outfile, head->cmd_path, head->her_doc);
        //     int i = 0;
        //     while (head->cmd_args[i])
        //         printf("opts == %s\n", head->cmd_args[i++]);
        //     head = head->next;
        // }
    }
}
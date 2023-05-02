/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:20 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/02 13:38:59 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


int ft_echo(t_cmd *com)
{
    char **to_print;

    to_print = com->cmd_args;
    while(to_print)
    {
        printf("%s ", *to_print);
        to_print++;
    }
    printf("\n");
    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:16:41 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/06 12:39:34 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void ft_replace(char *str , char sign, char c, char r)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == sign || sign == 0)
        {
            i ++;
            while(str[i])
            {
                if(str[i] == c)
                    str[i] = r;
                else if(str[i] == sign)
                    break ;
                i++;
            }
        }
        i++;
    }
}

void ft_replace_mat(char **str , char sign, char c, char r)
{
    char *tmp;
    while(*str)
    {
        ft_replace(*str, sign, c, r);
        tmp = *str;
        *str = ft_strtrim(*str, "\' ");
        free(tmp);
        // puts(*str);
        str++;
    }
}
// void ft_add_pre_operator(char *str, char ope)
// {
//     int i;
//     int count;
//     char *tmp;

//     i = 0;
//     count = 0;
//     while(str[i])
//         if(str[i++] = ope)
//             count++;
//     tmp = malloc(sizeof(char) * (ft_strlen(str) + count));
//     i = 0;
//     j = 0;
//     while(str[i])
//     {
//         if(str[i] != ope)
//             tmp[i + j] = str[i];
//         else
//         {
//             tmp[i + j] = ;
            
//         }
        
//     }
// }
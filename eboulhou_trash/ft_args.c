/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:16:41 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/08 14:56:43 by eboulhou         ###   ########.fr       */
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

void ft_skipwhite(char *str ,int *i)
{
    while ((str[*i] > 8 && str[*i] < 14) || str[*i] == 32)
		*i = *i + 1;
}

void combine_rdir(char **inputs, char **outputs, char *str)
{
    int i;
    int chr;

    i = 0;
    while(str[i])
    {
        if(str[i] == '<' || str[i] == '>')
        {
            chr = str[i];
            str[i] = 32;
            i++;
            ft_skipwhite(str , &i);
            int j = i;
            while (str[j] && !(str[j] > 8 && str[j] < 14) && str[j] != 32)
            {
                // write(1, &str[j], 1);
                // str[j] = 32;
                j++;
            }
            if(chr == '<')
            {
                *inputs = ft_calloc(sizeof(char) , 10);
                *inputs = ft_memcpy(*inputs, &str[i] , j - i);
                ft_memset(&str[i], ' ', j - i);
                inputs++;
            }
            else 
            if(chr == '>')
            {
                char *out ;
                out = ft_calloc(sizeof(char) , (j - i + 1));
                ft_memcpy(out, &str[i], j-i);
                ft_memset(&str[i], ' ', j - i);
                *outputs = out;
                outputs++;
                // outputs = NULL;
            }
            i = j;
        }
        i++;
    }
}


int ft_ifcinstr(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return i;
        i++;
    }
    return (-1);
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
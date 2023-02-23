/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:04:02 by eboulhou          #+#    #+#             */
/*   Updated: 2023/02/21 20:24:17 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// typedef struct s_flag
// {
// 	int idx;
// 	char *flg;
// 	struct s_flag *next;
// }t_flag;

typedef struct s_comm
{
	int idx;
	char *com;
	char **flags;
	struct s_comm *next;
	struct s_comm *prev;
}t_comm;


#endif
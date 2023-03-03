/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:04:02 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/03 12:50:02 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

#include "libft/libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <stdio.h>
#include <stdarg.h>
#include <readline/readline.h>
#include <readline/history.h>

#define NX_PIPE
#define NX_OUT
#define PR_PIPE
#define PR_IN
#define PR_FRST


typedef struct s_comm
{
	int idx;
	char *com;
	char **flags;
	int nxt;
	struct s_comm *next;
}t_comm;
typedef struct s_minishell
{
	t_comm *comms;
	int *pipe;
	int pipe_nb;
	int child_nb;
	char **env;
}t_minishell;


//ft_commands.c

t_comm *new_comm(char **com, int idx);
char *get_right_path(char *str, char **env);
void add_back_comm(t_comm **comms, t_comm *new);
int get_comm_lenght(t_comm *comms);
t_comm *ft_get_commands(char *str, char **env);






#endif
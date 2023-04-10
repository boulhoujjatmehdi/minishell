/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:04:02 by eboulhou          #+#    #+#             */
/*   Updated: 2023/04/10 17:25:07 by fhihi            ###   ########.fr       */
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

#define NX_PIPE
#define NX_OUT
#define PR_PIPE
#define PR_IN
#define PR_FRST

// imported from parser folder
typedef struct s_cmd
{
	int key;
	char *tmp;
	char *str;
	int infile;
	int outfile;
	char *her_doc;
	char **cmd_args;
	char *cmd_path;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_cmd_list
{
	t_cmd	*current;
	struct s_cmd_list *next;
}	t_cmd_list;

typedef struct s_tokens
{
	int				pos;
	int				token_type;
	char			*token;
	struct s_tokens *next;
}	t_tokens;

// -------- end of imports ////////

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
}t_minishell;

#endif
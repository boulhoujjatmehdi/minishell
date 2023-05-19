/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:04:02 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/19 16:49:25 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NX_PIPE
# define NX_OUT
# define PR_PIPE
# define PR_IN
# define PR_FRST
# include "ft_struct.h"
# include "EXEC/exec.h"
# include "PARSER/parse.h"
# include "./other_src/get_next_line.h"

t_minishell	*g_msh;

void	rl_replace_line(const char *text, int clear_undo);
void	signal_handler(int sig);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:05:47 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/19 14:12:15 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H
# include "libft/libft.h"

typedef struct s_cmd
{
	char			*cmd_path;
	char			**cmd_args;
	int				infile;
	int				outfile;
	int				key;
	char			*str;
	char			*exit_msg;
	int				exit_stat;
	int				ctr_c;
	t_list			**env;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_cmd_list
{
	t_cmd				*current;
	struct s_cmd_list	*next;
}	t_cmd_list;

typedef struct s_tokens
{
	int				pos;
	int				token_type;
	char			*token;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}	t_tokens;

// -------- end of imports ////////

typedef struct s_comm
{
	int				idx;
	char			*com;
	int				begin_com;
	char			**flags;
	int				red;
	char			**infiles;
	char			**heredoc;
	char			**outfiles;
	char			**append;
	struct s_comm	*next;
	struct s_comm	*prev;
}t_comm;

typedef struct s_minishell
{
	t_cmd		*comms;
	t_cmd		*c_tmp;
	int			*pipe;
	int			pipecount;
	int			pipe_nb;
	int			child_nb;
	char		**env;
	t_list		**lenv;
	t_tokens	**list;
	int			stat;
	int			exit_st;
	int			last_st;
}t_minishell;
#endif
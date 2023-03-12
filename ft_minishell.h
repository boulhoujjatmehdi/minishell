/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:04:02 by eboulhou          #+#    #+#             */
/*   Updated: 2023/03/12 15:08:38 by eboulhou         ###   ########.fr       */
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


#define REDIRECT_INPUT 1
#define REDIRECT_OUTPUT 2


// #define PR_FRST
#define BEGIN_COM 1
#define BEGIN_REDIR 2


typedef struct s_comm
{
	int idx;
	char *com;
	int begin_com;
	char **flags;
	int red;
	char **infiles;
	char **outfiles;
	struct s_comm *next;
	struct s_comm *prev;
}t_comm;

typedef struct s_minishell
{
	t_comm *comms;
	int *pipe;
	int pipecount;
	int pipe_nb;
	int child_nb;
	char **env;
}t_minishell;




//ft_main.c

void initialize_data(t_minishell *msh);
void  open_pipes(t_minishell *msh);
void wait_for_all(int *pids , int nb);
void fork_it_for_me(t_minishell *msh);
void close_all_pipes(t_minishell *msh);


//ft_commands.c=

t_comm *new_comm(char **com, int idx);
char *get_right_path(char *str, char **env);
void add_back_comm(t_comm **comms, t_comm *newc);
int get_comm_lenght(t_comm *comms);
t_comm *ft_get_commands(t_minishell *msh, char *str, char **env);
void ft_free_commands(t_comm *comms);
void ft_free_command(t_comm *comms);
void ft_free_mat(char **mat);
t_comm *get_right_comm(t_minishell *msh, int idx);

//ft_childs

void last_child(t_minishell *msh,int comidx,  int idx, int *pid);
void printer_child(t_minishell *msh, int idx, int *pid);
void middle_child(t_minishell *msh, int comidx, int idx , int *pid);
void first_child(t_minishell *msh ,int idx,  int *pid);
void infiles_child(t_minishell *msh,int comidx, int idx, int *pid);
void outfiles_child(t_minishell *msh, int comidx, int idx, int *pid);

//ft_args.c

void ft_replace(char *str , char sign, char c, char r);
void ft_replace_mat(char **str , char sign, char c, char r);
void combine_rdir(char **inputs, char **outputs, char *str);

#endif
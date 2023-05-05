/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:30:48 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/05 14:17:09 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../ft_minishell.h"

typedef struct s_env
{
    char *content;
    struct s_env* next;
}t_env;

int main_function_exec(t_cmd *comms , t_list **env);
//exec.c
void close_all_pipes(t_minishell *msh);


//gets.c
int get_comm_lenght(t_cmd *comms);
int get_nb_of_pipes(t_cmd *comms);
t_cmd *get_right_comm(t_minishell *msh, int idx);
void fill_env_list(t_list **lenv, char **env);
char *get_path_line(t_list *lenv);

//childs.c
void child_forked(t_minishell *msh , int idx, int *pid);


//builtins.c
int check_builtis(t_cmd *cmd , t_minishell *msh);
int ft_export(t_minishell msh , t_cmd *cmd);
int ft_echo(t_cmd *cmd);
#endif
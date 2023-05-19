/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:30:48 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/19 15:20:06 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../ft_minishell.h"

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}t_env;

//exec.c
int		execution_function(t_cmd *comms, t_list **env);
void	open_pipes(void);
void	fork_it_for_me(void);
void	forking(int k, int *stat, int *pid);
void	close_all_pipes(t_minishell *msh);
void	wait_for_all(int *pids, int nb);

//gets.c
char	*get_from_env(t_list *lenv, char *str, int n);
void	fill_env_list(t_list **lenv, char **env);
t_cmd	*get_right_comm(t_minishell *msh, int idx);
int		get_nb_of_pipes(t_cmd *comms);
int		get_comm_lenght(t_cmd *comms);
char	*get_from_env(t_list *lenv, char *str, int n);

//childs.c
void	child_forked(t_minishell *msh, int idx, int *pid);

//builtins.c
int		exec_builtins(t_cmd *cmd, int par);
int		ft_exit(t_cmd *cmd);
int		ft_unset(t_minishell *msh, t_cmd *cmd);
void	ft_unset_1(t_list *tmp, t_list *prv, char *arg, char *str);
int		ft_env_cmd(t_minishell *msh);
void	ft_pwd(void);
int		ft_echo(t_cmd *cmd);
void	ft_echo_1(char **to_print, int *trigger, char *str);
int		ft_cd(t_cmd *cmd, t_minishell *msh);
void	ft_cd_err(char *str);
int		ft_export(t_minishell msh, t_cmd *cmd);
t_list	*find_var_env(t_list *tmp, char *str2);
void	ft_export_list(void);
int		export_error(char *s);
int		ret_cases(char *s);

#endif
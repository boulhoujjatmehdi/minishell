/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:24:46 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/19 15:19:59 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_echo_1(char **to_print, int *trigger, char *str)
{	
	int	i;

	while (*to_print)
	{
		if (*to_print[0] == '-')
		{
			i = 1;
			str = *to_print;
			while (str[i] && str[i] == 'n')
				i++;
			if (str[i])
				break ;
			to_print++;
		}
		else
			break ;
			*trigger = 1;
	}
	while (*to_print)
	{
		printf("%s", *to_print);
		to_print++;
		if (*to_print && (*to_print)[0] != 0)
			printf(" ");
	}
}

void	ft_unset_1(t_list *tmp, t_list *prv, char *arg, char *str)
{
	while (tmp && tmp->content)
	{
		if (!ft_strncmp(tmp->content, arg, ft_strlen(arg)))
		{
			str = (char *)tmp->content;
			if (str[ft_strlen(arg)] == 0 || str[ft_strlen(arg)] == '=')
			{
				if (prv)
					prv->next = tmp->next;
				else
					*g_msh->lenv = tmp->next;
				free(tmp->content);
				free(tmp);
				break ;
			}
		}
		prv = tmp;
		tmp = tmp->next;
	}
}

int	ft_exit(t_cmd *cmd)
{
	int	boel;

	boel = 0;
	if (cmd->cmd_args[1])
	{
		ft_atoi_mod(cmd->cmd_args[1], &boel);
		if (boel)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->cmd_args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(-1);
		}
		else if (cmd->cmd_args[1] && cmd->cmd_args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_msh->exit_st = 1;
			return (1);
		}
		exit(ft_atoi_mod(cmd->cmd_args[1], &boel));
	}
	exit(g_msh->last_st);
	return (1);
}

int	ft_cd(t_cmd *cmd, t_minishell *msh)
{
	char	*str;
	char	*sss;

	sss = cmd->cmd_args[1];
	if (cmd->cmd_args[1] && sss[0] != 0)
		str = cmd->cmd_args[1];
	else
	{
		str = get_from_env(*msh->lenv, "HOME=", 5);
		if (!str)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_msh->exit_st = 1;
			return (1);
		}
		str = str + 5;
	}
	if (chdir(str) == -1)
	{
		ft_cd_err(str);
		return (1);
	}
	g_msh->exit_st = 0;
	return (1);
}

void	ft_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
	exit(0);
}

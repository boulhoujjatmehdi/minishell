/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:22:06 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/19 14:17:16 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ret_cases(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-' && s[1])
		return (2);
	while (s[i] && s[i] != '=' )
	{
		if (!ft_isalnum(s[i]) && s[i] != '_' )
			return (1);
		i++;
	}
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (1);
	return (0);
}

int	export_error(char *s)
{
	int	i;

	i = ret_cases(s);
	if (i == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_msh->exit_st = 1;
		return (1);
	}
	else if (i == 2)
	{
		printf("bash: export: -%c: invalid option\n", s[1]);
		g_msh->exit_st = 1;
		return (1);
	}
	g_msh->exit_st = 0;
	return (0);
}

void	ft_export_list(void)
{
	t_list	*prt;
	int		i;
	int		nb;

	prt = *g_msh->lenv;
	while (prt && prt->content)
	{
		write(1, "declare -x ", 11);
		i = -1;
		nb = 0;
		while (((char *)prt->content)[++i])
		{
			if (((char *)prt->content)[i] == '\"'
			|| ((char *)prt->content)[i] == '$')
				write(1, "\\", 1);
			write(1, &((char *)prt->content)[i], 1);
			if (!nb && ((char *)prt->content)[i] == '=' && !nb++)
				write(1, "\"", 1);
		}
		if (nb)
			write(1, "\"", 1);
		write(1, "\n", 1);
		prt = prt->next;
	}
}

t_list	*find_var_env(t_list *tmp, char *str2)
{
	int		j;
	char	*str;

	while (tmp && tmp->content)
	{
		j = 0;
		str = (char *)tmp->content;
		while (str[j] && str[j] != '=' && str2[j] && str2[j] != '=')
		{
			if (str[j] != str2[j])
				break ;
			j++;
		}
		if ((str[j] == 0 || str[j] == '=') && str2[j] == '=')
		{
			free(tmp->content);
			tmp->content = ft_strdup(str2);
			break ;
		}
		if ((str[j] == '=' && str2[j] == 0) || (!str[j] && !str2[j]))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_cd_err(char *str)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_msh->exit_st = 1;
}

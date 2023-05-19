/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing_Utils6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:16:10 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 20:16:39 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

char	*ft_rplc(char *from, int *l, t_list **env)
{
	char	*new;
	char	*env1;
	int		i;

	i = 1;
	*l = 0;
	while (from[i] && (ft_isalnum(from[i]) || \
	from[i] == '_' || from[1] == '?' || from[1] == '@'))
	{
		i++;
		if (from[1] == '?' || from[1] == '@' || ft_isdigit(from[1]))
			break ;
	}
	*l = i;
	env1 = ft_substr(from, 1, i - 1);
	if (env1[0] == '?')
		return (ft_exit_status(env1));
	new = get_assos(env1, env, 0);
	return (new);
}

char	*herdoc_env(char *str, t_list **env)
{
	t_var	var;
	char	*tmp;

	var.new = (char *)ft_calloc(sizeof(char), 1);
	if (!var.new)
		return (NULL);
	var.i = 0;
	var.j = 0;
	while (str[var.i])
	{
		if (str[var.i] == '$')
		{
			tmp = ft_rplc(&str[var.i], &var.j, env);
			var.new = ft_strjoin2(var.new, tmp);
			var.i += var.j;
		}
		else
		{
			var.new = ft_joinchar(var.new, str[var.i]);
			var.i++;
		}
	}
	free(str);
	return (var.new);
}

int	check_delimeter(char *s)
{
	int	len;

	len = ft_strlen(s) - 1;
	if (s[len] == 5)
	{
		s[len] = 0;
		return (1);
	}
	return (0);
}

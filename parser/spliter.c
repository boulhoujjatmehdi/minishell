/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:25:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/19 15:39:51 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

//this function return 1 if ihave a RED or PIPE
// or SPACE or im at the starts of quotes
int	is_not_arg(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\0' \
	|| c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*ft_part_one(char **ss, char *s, int *l)
{
	char	*new;
	int		i;

	i = *l;
	new = NULL;
	if (s[i] == '$' && i == 0)
	{
		i = get_env_var(s);
		new = ft_substr(s, 0, i);
		*ss = s + i;
		return (new);
	}
	else if ((is_not_arg(s[i]) || s[i] == '$') && i > 0)
	{
		new = ft_substr(s, 0, i);
		*ss = s + i;
		return (new);
	}
	else if (is_not_arg(s[i]) && i == 0)
	{
		new = ft_substr(s, 0, 1);
		*ss = s + 1;
	}
	return (new);
}

char	*quoted_token(char **ss, char *s, int *l)
{
	char	*new;
	int		i;

	i = *l;
	i = skip_opt(s, s[i]) + 1;
	new = ft_substr(s, 0, i);
	*ss = s + i;
	if (quote_error(new [0], new[i - 1]) == 1)
	{
		free(new);
		return (ft_strdup("SSYY"));
	}			
	return (new);
}

// this function is used to tokenis my initial string
char	*my_strtok(char **ss)
{
	t_var	var;
	char	*s;

	var.i = 0;
	s = *ss;
	var.new = NULL;
	while (var.i <= (int)ft_strlen(s))
	{
		if (!s[var.i] && var.i == 0)
			return (NULL);
		if ((s[var.i] == '\'' || s[var.i] == '\"') && var.i == 0)
		{
			var.new = quoted_token(ss, s, &var.i);
			break ;
		}
		if ((s[var.i] == '$' && var.i == 0) || \
		((is_not_arg(s[var.i]) || s[var.i] == '$') && var.i > 0) || \
		(is_not_arg(s[var.i]) && var.i == 0))
		{
			var.new = ft_part_one(ss, s, &var.i);
			break ;
		}
		var.i++;
	}
	return (var.new);
}

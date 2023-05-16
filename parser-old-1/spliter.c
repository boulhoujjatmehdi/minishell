/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:25:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/12 20:00:43 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

//this function return 1 if ihave a RED or PIPE or SPACE or im at the starts of quotes
int	is_not_arg(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\0' \
|| c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*ft_part_one(char **ss, char *s, int *l)
{
	int	i;
	char *new;

	i = *l;
	if (s[i] == '$' && i == 0)
	{
		i = get_env_var(s);
		new = ft_substr(s, 0, i);
		*ss = s + i;
		return (new) ;
	}
	//whne i have an ARG token
	if ((is_not_arg(s[i]) || s[i] == '$') && i > 0)
	{
		new = ft_substr(s, 0, i);
		*ss = s + i;
		return (new);
	}
	//whne i have a RED OR PIPE OR SPACE token
	if (is_not_arg(s[i]) && i == 0)
	{
		new = ft_substr(s, 0, 1);
		*ss = s + 1;
		return (new);
	}
	return (new);
}

// this function is used to tokenis my initial string
char	*my_strtok(char **ss)
{
	int i = 0;
	char *new;
	char *s = *ss;

	while (i <= ft_strlen(s))
	{
		//when i reach the end of the string
		if (!s[i] && i == 0)
			return NULL;
		//here the case of quotes in my string
		if ((s[i] == '\'' || s[i] == '\"') && i == 0)
		{
			i = skip_opt(s, s[i]) + 1;
			new = ft_substr(s, 0, i);
			*ss = s + i;
			if (quote_error(new [0], new[i - 1]) == 1)
				return (ft_strdup("SSYY"));
			break;
		}
		if ((s[i] == '$' && i == 0) || ((is_not_arg(s[i]) || s[i] == '$') && i > 0) || (is_not_arg(s[i]) && i == 0))
		{
			new = ft_part_one(ss, s, &i);
			break ;
		}
		i++;
	}
	return (new);
}

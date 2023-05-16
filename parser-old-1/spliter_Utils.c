/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_Utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:03:38 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/15 23:23:12 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

//used to skip whats between the quotes
int	skip_opt(char *s, char c)
{
	int i;
	int n;
	
	n = 0;
	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			break;
		i++;
	}
	return (i);
}

int	get_env_var(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (is_not_arg(s[i]))
			break ;
		i++;
	}
	return (i);
}

int	quote_error(char start, char end)
{
	if (start != end)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching\n", 2);
		return (1);
	}
	return (0);
}

char	*ft_joinchar(char *s, char c)
{
	size_t	size;
	size_t	i;
	size_t	j2;
	char	*new;

	if (!s)
		return (NULL);
	size = ft_strlen2(s) + 1;
	new = (char *)malloc((size + 1) * sizeof(char));
	if (!new)
		return (0);
	i = 0;
	j2 = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = c;
	i++;
	new[i] = '\0';
	free(s);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:25:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/04/27 20:27:04 by fhihi            ###   ########.fr       */
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
		if (!ft_isalnum(s[i]))
			break ;
		i++;
	}
	return (i);
}

void	quote_error(char start, char end)
{
	if (start != end)
		exit(1);
}


//this function is used to tokenis my initial string
char	*my_strtok(char **ss)
{
	int i = 0;
	char *new;
	char *s = *ss;
	// puts("here");
	while (i <= ft_strlen(s))
	{
		//when i reach the end of the string
		if (!s[i] && i == 0)
			return NULL;
		if (s[i] == '$')
		{
			i = get_env_var(s);
			new = ft_substr(s, 0, i);
			*ss = s + i;
			break ;
		}
		//here the case of quotes in my string
		if ((s[i] == '\'' || s[i] == '\"') && i == 0)
		{
			i = skip_opt(s, s[i]) + 1;
			new = ft_substr(s, 0, i);
			quote_error(new [0], new[i - 1]);
			*ss = s + i;
			break;
		}
		//whne i have an ARG token
		if (is_not_arg(s[i]) && i > 0)
		{
			new = ft_substr(s, 0, i);
			*ss = s + i;
			break;
		}
		//whne i have a RED OR PIPE OR SPACE token
		if (is_not_arg(s[i]) && i == 0)
		{
			new = ft_substr(s, 0, 1);
			*ss = s + 1;
			break;
		}
		i++;
	}
	return (new);
}

// int main (int ac, char **av)
// {
// 	char *new, *s;
// 	int i = 0;

// 	s = strdup(av[1]);
// 	new = my_strtok(&s);
// 	while (new)
// 	{
// 		printf(":%s:\n", new);
// 		new = my_strtok(&s);
// 		// printf("\n----------:%s:\n", s);
// 	}
// 	return (0);
// }
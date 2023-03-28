/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:25:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/03/28 17:59:01 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

char **spliter2(char *s);

int	is_not_arg(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_red(char c1, char c2)
{
	if (c1 == '|' || c1 == ' ')
		return (1);
	else if (c1 == '<' && c2 == '<')
		return (2);
	else if (c1 == '>' && c2 == '>')
		return (2);
	else
		return (1);
}

int cont(char *s)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (is_not_arg(s[i]))
		{
			if (is_not_arg(s[i - 1]))
			{
				if (check_red(s[i], s[i + 1]) == 1)
				{
					count+= 1;
					i++;
				}
				else if (check_red(s[i], s[i + 1]) == 2)
				{
					count+= 1;
					i+= 2;
				}
			}
			else if (!(is_not_arg(s[i - 1])))
			{
				if (check_red(s[i], s[i + 1]) == 1)
				{
					count+= 2;
					i++;
				}
				else if (check_red(s[i], s[i + 1]) == 2)
				{
					count+= 2;
					i+= 2;
				}
			}
		}
		else if (s[i] == '\0')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

int	ft_has_red(char *s)
{
	if (ft_strchr(s, '<') || ft_strchr(s, '>'))
		return (1);
	return (0);
}

char	**get_red(char *s)
{
	int i;
	int len;
	char **new;

	new = (char **)malloc(2 * sizeof(char *));
	if (!new)
		return (NULL);
	if (is_not_arg(s[0]))
	{
		new[1] = ft_strdup(s + 1);
		printf("this ;%s;\n", new[1]);
		puts("here");
		new[0][0] = s[0];
		new[0][1] = '\0';
	}
	else
	{
		len = ft_strlen(s) - 2;
		new[0] = ft_strdup(s);
		new[0][len] = '\0';
		new[1][0] = s[len];
		new[1][1] = '\0';
	}
	return (new);
}

char	**spliter(char *s)
{
	int	i, j;
	char **new;
	char **end;

	new = ft_split(s, ' ');
	i = 0;
	j = 0;
	while (new[i])
	{
		if (ft_has_red(new[i]) && ft_strlen(new[i]) > 2)
		{
			spliter2(new[i]);
			exit(0);
		}
		else
		{
			end[j] = ft_strdup(new[i]);
			// printf("args :%s:\n", end[j]);
			j++;
		}
		i++;
	}
	return (end);
}

char	**spliter2(char *s)
{
	char **new;
	int i, j, k, count;
	
	count = cont(s);
	new = (char **)malloc((count + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	k = 0;
	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (is_not_arg(s[i]))
		{
			new[j] = malloc(1000);
			new[j] = ft_substr(s, k, i - k);
			printf("---%s\n", new[j]);
			j++;
			new[j] = malloc(1000);
			new[j] = ft_substr(s, i, 1);
			// exit(0);
			// i--;
			k = i;
		}
		if (!s[i])
		{
			new[j] = malloc(1000);
			new[j] = ft_substr(s, k, i - k);
		}
		i++;

	}
	return (new);
}

int main (int ac, char **av)
{
	char **new;
	int i = 0;

	new = spliter(av[1]);
	// exit(0);
	// while (new[i])
	// 	printf(":%s:\n", new[i++]);
	return (0);
}
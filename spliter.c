/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:25:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/03/23 18:04:09 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

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
			
		}
		else
			end[j] = new[i];
		i++;
	}
	return (new);
}

char	**spliter2(char *s)
{
	char **new;
	char tmp[256];
	int i, j, k, count, t, t1;
	
	count = cont(s);
	new = (char **)malloc((count + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (i <= ft_strlen(s))
	{
		if (is_not_arg(s[i]))
		{
			tmp[k] = '\0';
			new[j] = ft_strdup(tmp);
			k = 0;
			t = 0;
			j++;
		}
		tmp[k] = s[i];
		i++;
		k++;
	}
	return (new);
}

int main (int ac, char **av)
{
	char **new;
	int i = 0;

	new = spliter(av[1]);
	// exit(0);
	while (new[i])
		printf(":%s:\n", new[i++]);
}
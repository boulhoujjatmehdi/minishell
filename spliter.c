/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:25:50 by fhihi             #+#    #+#             */
/*   Updated: 2023/03/20 10:17:18 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

int	is_not_arg(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
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

char	**spliter(char *s)
{
	int	i, j, i0;
	char **new;
	int count;

	count = 0;
	i = 0;
	j = 0;
	s = ft_strtrim(s, " 	");
	i0 = i;
	new = (char **)malloc((cont(s) + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (is_not_arg(s[i]))
		{
			if (is_not_arg(s[i - 1]))
			{
				if (check_red(s[i], s[i + 1]) == 1)
				{
					new[j] = ft_substr(s, i0, i - i0);
					j++;
					new[j] = ft_substr(s, i, 1);
					j++;
					i++;
					i0 = i;
				}
				else 
				{
					new[j] = ft_substr(s, i0, i - i0);
					j++;
					new[j] = ft_substr(s, i, 2);
					j++;
					i+= 2;
					i0 = i;
				}
			}
			else if (!(is_not_arg(s[i - 1])))
			{
				if (check_red(s[i], s[i + 1]) == 1)
				{
					new[j] = ft_substr(s, i0, 1);
					j++;
					i++;
					i0 = i;
				}
				else if (check_red(s[i], s[i + 1]) == 2)
				{
					new[j] = ft_substr(s, i0, 2);
					j++;
					i+= 2;
					i0 = i;
				}
			}

		}
		else if (s[i] == '\0')
		{
			new[j] = ft_substr(s, i0, i - i0);
			j++;
			i++;
		}
		else
			i++;
	}
	new[j] = NULL;
	return (new);
}

int main (int ac, char **av)
{
	char **new;
	printf("len = %d\n", cont(av[1]));
	// exit(0);
	new = spliter(av[1]);
	for(int i = 0; i < cont(av[1]); i++)
		printf(":%s:\n", new[i]);
}
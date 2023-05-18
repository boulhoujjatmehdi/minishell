/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing_Utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:51:08 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 20:20:46 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

char	*ft_strchr1(char *s, int c, int c1)
{
	int				i;
	unsigned char	cc;

	cc = c;
	i = 0;
	while (s[i] != cc)
	{
		if (!s[i])
			return (0);
		i++;
	}
	s[i] = c1;
	i += 1;
	return ((char *)(s + i));
}

char	*ft_strchr2(char *s, int c, int c1)
{
	int				i;
	unsigned char	cc;

	cc = c;
	i = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] == cc && s[i + 1] && s[i + 1] == cc)
		{
			s[i] = c1;
			s[i + 1] = c1;
			i += 2;
			return ((char *)s + i);
		}
		i++;
	}
	return (0);
}

char	*get_filename(char *s, int c, int c1)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	while (s[i] != c)
	{
		new[i] = s[i];
		s[i] = c1;
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strrchr1(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char )c)
			return (i);
		i--;
	}
	return (0);
}

void	return_red(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] == 3)
			s[i] = '<';
		if (s[i] == 4)
			s[i] = '>';
		i++;
	}
}

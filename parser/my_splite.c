/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:26:26 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/16 22:59:59 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	i1;
	int	count;

	i = 0;
	i1 = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && i1 == 0)
		{
			count++;
			i1 = 1;
		}
		else if (s[i] == c)
			i1 = 0;
		i++;
	}
	return (count);
}

char	**ft_my_split(char const *s, char c)
{
	char	**new;
	int		i[3];

	if (!s)
		return (NULL);
	new = (char **)malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	i[2] = -1;
	while (i[0] <= (int)ft_strlen(s))
	{
		if ((s[i[0]] != c || s[i[0]] == '\0') && i[2] < 0)
			i[2] = i[0];
		else if ((s[i[0]] == c || s[i[0]] == '\0') && i[2] >= 0)
		{
			new[i[1]++] = ft_substr(s, i[2], i[0] - i[2]);
			i[2] = -1;
		}
		i[0]++;
	}
	new[i[1]] = NULL;
	return (new);
}

char	*ft_my_strtrim(char const *s1, char const *set)
{
	int	i;
	int	len;
	int	size;

	i = 0;
	if (!s1)
		return (NULL);
	while ((int)strchr(set, s1[i]) && s1[i])
		i++;
	if (i == (int)strlen(s1))
		return (ft_my_substr(s1, i, 0));
	len = (int)strlen(s1) - 1;
	while ((int)strchr(set, s1[len]))
		len--;
	size = len - i + 1;
	return (ft_my_substr(s1, i, size));
}

char	*ft_my_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		l;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub = (char *)malloc(len * sizeof(char ) + 100);
	if (!sub)
		return (0);
	l = (int)len;
	i = 0;
	while (i < l)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_my_strdup(const char *s1)
{
	char	*s;
	size_t	i;

	s = (char *)malloc(ft_strlen(s1) * sizeof(char ) + 1);
	if (!s)
		return (0);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
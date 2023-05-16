/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:47:04 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/16 17:30:46 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_of_strings(const char *s, char c, int *l)
{
	int	i[3];
	int	nb;

	i[0] = 0;
	i[2] = 0;
	nb = 0;
	while (s[i[0]])
	{
		while (s[i[0]] && s[i[0]] == c)
			i[0]++;
		i[1] = 0;
		while (s[i[0] + i[1]] && s[i[0] + i[1]] != c)
			i[1]++;
		if (i[1])
		{
			l[i[2]++] = i[0];
			l[i[2]++] = i[0] + i[1];
			nb++;
		}
		i[0] += i[1];
	}
	return (nb);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		nb;
	int		*l;
	char	**ret;

	if (!s)
		return (0);
	l = (int *)malloc(sizeof(int) * (ft_strlen(s)));
	if (!l)
		return (0);
	nb = nb_of_strings(s, c, l);
	ret = (char **)ft_calloc (nb + 1, sizeof(char *));
	if (!ret)
		return (0);
	i = 0;
	while (i < nb * 2)
	{
		ret[i / 2] = (char *)ft_calloc((l[i + 1] - l[i] + 1), sizeof(char));
		if (!ret[i / 2])
			return (NULL);
		ft_memcpy (ret[i / 2], s + l[i], l[i + 1] - l[i]);
		i += 2;
	}
	free(l);
	return (ret);
}

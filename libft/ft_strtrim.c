/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:48:23 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/20 16:22:06 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	found_char(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i[2];
	char	*ret;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	i[0] = 0;
	i[1] = ft_strlen(s1)-1;
	while (found_char(set, s1[i[0]]) && s1[i[0]])
		i[0]++;
	if (!s1[i[0]])
		return (ft_strdup(""));
	while (found_char(set, s1[i[1]]) && s1[i[1]])
		i[1]--;
	ret = (char *)malloc(sizeof(char) * (i[1] - i[0] + 2));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1 + i[0], i[1] - i[0] + 2);
	return (ret);
}

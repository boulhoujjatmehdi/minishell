/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:28:21 by eboulhou          #+#    #+#             */
/*   Updated: 2023/02/21 14:58:49 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!len && !haystack)
		return (0);
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (needle[j + 1] == 0)
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strnstr_mod(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack)
		return (-1);
	if (needle[0] == 0)
		return (-2);
	while (haystack[i])
	{
		j = 0;
		while (needle[j])
		{
			if (haystack[i] == needle[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-3);
}

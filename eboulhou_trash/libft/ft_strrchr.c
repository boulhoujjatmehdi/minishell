/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:11:55 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/17 15:47:04 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				j;
	unsigned char	cc;

	cc = c;
	i = 0;
	j = -1;
	while (s[i])
	{
		if (s[i] == cc)
			j = i;
		i++;
	}
	if (cc == 0)
		return ((char *)s + i);
	if (j == -1)
		return (0);
	return ((char *)s + j);
}

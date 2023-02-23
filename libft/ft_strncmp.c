/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:16:10 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/14 15:39:55 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*n_s1;
	unsigned char	*n_s2;

	i = 0;
	n_s1 = (unsigned char *)s1;
	n_s2 = (unsigned char *)s2;
	while ((i < n && n_s1[i] == n_s2[i]))
	{
		if (!n_s1[i] && !n_s2[i])
			return (0);
		i++;
	}
	if (n_s1[i] != n_s2[i] && i < n)
		return (n_s1[i] - n_s2[i]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:03:32 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/12 18:47:11 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*n_s1;
	unsigned char	*n_s2;
	int				i;

	if (n == 0)
		return (0);
	i = 0;
	n_s1 = (unsigned char *)s1;
	n_s2 = (unsigned char *)s2;
	while (n_s1[i] == n_s2[i] && i < (int) n -1)
		i++;
	if (n_s1[i] != n_s2[i])
		return (n_s1[i] - n_s2[i]);
	return (0);
}

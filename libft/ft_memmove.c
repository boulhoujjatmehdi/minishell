/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:19:26 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/15 15:56:20 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	char	*n_dest;
	char	*n_src;

	if ((!dest && !src) || !n)
		return (dest);
	if (dest < src)
		ft_memcpy (dest, src, n);
	else
	{
		n_dest = (char *)dest;
		n_src = (char *)src;
		while (n--)
			n_dest[n] = n_src[n];
	}
	return (dest);
}

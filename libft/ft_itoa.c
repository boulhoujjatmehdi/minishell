/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:46:42 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/20 16:23:15 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_pos(int n)
{
	int	pos;

	pos = 1;
	if (n < 0)
		pos = -1;
	return (pos);
}

static int	len_of_int(long n, int pos)
{
	int	i;
	int	spare;

	spare = n;
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	if (pos == -1 || spare == 0)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ret;
	long	nn;
	int		pos;
	int		len;

	nn = n;
	pos = is_pos(nn);
	len = len_of_int(nn * pos, pos);
	ret = (char *)ft_calloc (len + 1, sizeof(char));
	if (!ret)
		return (0);
	nn *= pos;
	if (nn == 0)
		ret[0] = 0 + '0';
	while (len--)
	{
		ret[len] = nn % 10 + '0';
		nn -= nn % 10;
		nn /= 10;
	}
	if (pos == -1)
		ret[0] = '-';
	return (ret);
}

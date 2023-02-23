/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:40:20 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/20 17:23:34 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	ret;
	int		neg;

	i = 0;
	ret = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if ((str[i] == '-' || str[i] == '+') && ++i)
		if (str[i - 1] == '-')
			neg = -1;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + str[i] - 48;
		if (ret > 2147483647 && neg == 1)
			return (-1);
		if (ret > 2147483648 && neg == -1)
			return (0);
		i++;
	}
	return (ret * neg);
}

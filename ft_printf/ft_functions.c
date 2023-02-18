/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:31:41 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/26 20:44:14 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putstr(char *str )
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		count += 6;
	}
	else
	{
		while (str[i])
		{
			count += ft_putchar(str[i]);
			i++;
		}
	}
	return (count);
}

int	ft_conv(unsigned long dec, char *base, int boole)
{
	int	count;

	count = 0;
	if (!boole)
	{
		boole = 1;
		write(1, "0x", 2);
		count += 2;
	}
	if (dec >= 16)
		count += ft_conv(dec / 16, base, boole);
	count += ft_putchar(base[dec % 16]);
	return (count);
}

int	ft_itohex(long dec, char *base, char c)
{
	int	count;

	count = 0;
	if (c == 'X')
	{
		base = "0123456789ABCDEF";
	}
	if (dec < 0)
	{
		dec *= -1;
		write(1, "-", 1);
		count++;
	}
	if (dec >= 16)
		count += ft_itohex(dec / 16, base, c);
	count += ft_putchar(base[dec % 16]);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:46:28 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/26 20:30:46 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_loops(char *form, va_list vlist, int count, char *xx)
{
	while (*form)
	{
		if (*form == '%' && form++)
		{
			if (*form == 'c')
				count += ft_putchar(va_arg(vlist, int));
			else if (*form == 's')
				count += ft_putstr(va_arg(vlist, char *));
			else if (*form == 'p')
				count += ft_conv((unsigned long)(va_arg(vlist, void *)), xx, 0);
			else if (*form == 'd' || *form == 'i')
				count += ft_itoa(va_arg(vlist, int));
			else if (*form == 'u')
				count += ft_uitoa(va_arg(vlist, unsigned int));
			else if (*form == 'x' || *form == 'X')
				count += ft_itohex(va_arg(vlist, unsigned int), xx, *form);
			else if (*form == '%')
				count += ft_putchar('%');
		}
		else
			count += ft_putchar(*form);
		form++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	vlist;
	int		count;
	char	*form;

	count = 0;
	form = (char *)format;
	va_start(vlist, format);
	count = ft_printf_loops(form, vlist, 0, "0123456789abcdef" );
	return (count);
}

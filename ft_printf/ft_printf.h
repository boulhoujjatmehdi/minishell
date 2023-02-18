/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:39:12 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/26 20:44:36 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(char c);
int	ft_putstr(char *str );
int	ft_conv(unsigned long dec, char *base, int boole);
//--------SECOND FILE------------
int	ft_itoa(int nb);
int	ft_uitoa(unsigned int nb);
int	ft_itohex(long dec, char *base, char c);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:51:40 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/17 17:09:41 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*ret;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (0);
	while (s[i])
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	return (ret);
}

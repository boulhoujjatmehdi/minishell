/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:56:30 by eboulhou          #+#    #+#             */
/*   Updated: 2022/10/17 17:27:26 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*str;

	size = ft_strlen(s1)+1;
	str = (char *)malloc(size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, size);
	return (str);
}

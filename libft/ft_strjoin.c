/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:33:02 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/10 19:50:48 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		size1;
	int		size2;
	char	*str;

	if (!s1 || !s2)
		return (0);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	str = (char *)malloc(size1 + size2 + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s1, size1 + 1);
	ft_strlcat(str + size1, s2, size2 + 1);
	free(s1);
	return (str);
}

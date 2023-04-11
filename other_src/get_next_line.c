/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:53:04 by eboulhou          #+#    #+#             */
/*   Updated: 2023/04/10 15:06:31 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

int	found_back_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != 10)
		i++;
	if (str[i] == 10)
		return (1);
	return (0);
}

char	*ft_get_line(char *temp)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if (!temp)
		return (NULL);
	while (temp[i] && temp[i] != 10)
		i++;
	if (temp[i] == 10)
		i++;
	line = malloc(i + 1);
	i = 0;
	while (temp[i] != 10 && temp[i])
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == 10)
		line[i++] = 10;
	line[i] = 0;
	return (line);
}

char	*read_function(int fd, char *temp)
{
	char	buff[BUFFER_SIZE + 1];
	int		rd;

	rd = 1;
	while (rd && !found_back_n(temp))
	{
		buff[0] = 0;
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
			break ;
		buff[rd] = 0;
		if (rd)
			temp = ftt_strjoin(temp, buff);
	}
	return (temp);
}

void	ft_set_stat(char *temp, char *stat)
{
	int	i;
	int	n;

	n = -1;
	i = -1;
	*stat = 0;
	while (temp[++i])
	{
		if (temp[i] == 10)
		{
			n = i;
			break ;
		}
	}
	i = 0;
	if (n++ >= 0)
	{
		while (temp[n + i])
		{
			stat[i] = temp[n + i];
			i++;
			stat[i] = 0;
		}
	}
}

char	*get_next_line(int fd)
{
	char static	stat[BUFFER_SIZE];
	char		*temp;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = NULL;
	line = NULL;
	if (stat[0])
		temp = ftt_strjoin (temp, stat);
	temp = read_function(fd, temp);
	if (!temp)
	{
		return (NULL);
	}
	line = ft_get_line (temp);
	ft_set_stat (temp, stat);
	if (!temp[0] && !stat[0])
	{
		line = NULL;
	}
	free(temp);
	return (line);
}

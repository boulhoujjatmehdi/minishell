/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing_Utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:47:02 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 19:08:27 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

int	procces_readfiles(char *s, t_cmd *node)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	var.new = ft_strchr1(s, '<', 1);
	while (var.new)
	{
		if (var.i != 0)
			close(var.i);
		var.new++;
		var.new = get_filename(var.new, 1, 1);
		if (!var.new)
			return (0);
		var.j = processe_exten_in(&var, node);
		if (var.j)
			return (var.j);
		free (var.new);
		var.new = ft_strchr1(s, '<', 1);
	}
	return (var.i);
}

int	procces_writefiles(char *s, t_cmd *node)
{
	t_var	var;

	var.i = 1;
	var.j = 0;
	var.new = ft_strchr1(s, '>', 1);
	while (var.new)
	{
		var.new++;
		var.new = get_filename(var.new, 1, 1);
		var.j = processe_exten_out(&var, node);
		if (var.j)
			return (var.j);
		free (var.new);
		var.new = ft_strchr1(s, '>', 1);
	}
	return (var.i);
}

int	procces_appendfiles(char *s, t_cmd *node)
{
	t_var	var;

	var.i = 1;
	var.j = 0;
	var.new = ft_strchr2(s, '>', 1);
	while (var.new)
	{
		var.new++;
		var.new = get_filename(var.new, 1, 1);
		var.j = processe_exten_app(&var, node);
		if (var.j)
			return (var.j);
		free (var.new);
		var.new = ft_strchr2(s, '>', 1);
	}
	return (var.i);
}

int	input_file(t_cmd *node)
{
	int		fd1;
	int		fd2;
	char	*s;
	int		last;
	int		t;

	s = node->str;
	t = 0;
	fd1 = 0;
	fd2 = 0;
	if (!s)
		return (0);
	last = ft_strrchr1(s, '<');
	if (s[last - 1] == '<')
		t = 1;
	fd2 = procces_her_doc(s, node);
	fd1 = procces_readfiles(s, node);
	if (t == 1)
		return (fd2);
	return (fd1);
}

int	output_file(t_cmd *node)
{
	int		fd1;
	int		fd2;
	char	*s;
	int		last;
	int		t;

	s = node->str;
	t = 0;
	fd1 = 1;
	fd2 = 1;
	if (!s)
		return (1);
	last = ft_strrchr1(s, '>');
	if (s[last - 1] == '>')
		t = 1;
	fd2 = procces_appendfiles(s, node);
	fd1 = procces_writefiles(s, node);
	if (t == 1)
		return (fd2);
	return (fd1);
}

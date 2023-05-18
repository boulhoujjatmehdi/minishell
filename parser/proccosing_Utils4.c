/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccosing_Utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:16:21 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 19:08:55 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

int	processe_exten_in(t_var *var, t_cmd *node)
{
	if (var->new[ft_strlen(var->new) - 1] == 5)
		var->new[ft_strlen(var->new) - 1] = 0;
	if ((var->new[0] == 2 && var->new[1] == '\0') || has_space(var->new))
	{
		if (file_errors(var->new, -2, node) == 1)
			return (-1);
	}
	var->new = triiim_char(var->new, 7);
	return_space(var->new);
	var->i = open(var->new, O_RDONLY);
	if (var->i == -1)
	{
		if (file_errors(var->new, 0, node) == 0)
		{
			free(var->new);
			return (-1);
		}
	}
	return (0);
}

int	processe_exten_out(t_var *var, t_cmd *node)
{
	if ((var->new[0] == 2 && var->new[1] == 2 && var->new[2] == '\0') || \
	(var->new[0] == 6 && var->new[1] == 5 && var->new[2] == 0))
	{
		free(var->new);
		var->new = ft_strdup("");
	}
	if (var->new[ft_strlen(var->new) - 1] == 5)
		var->new[ft_strlen(var->new) - 1] = 0;
	if ((var->new[0] == 2 && var->new[1] == '\0') || has_space(var->new))
	{	
		if (file_errors(var->new, -2, node) == 1)
			return (-1);
	}
	var->new = triiim_char(var->new, 7);
	var->i = open(var->new, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (var->i == -1)
	{
		if (file_errors(var->new, 1, node) == 1)
			return (-1);
	}
	return (0);
}

int	processe_exten_app(t_var *var, t_cmd *node)
{
	if ((var->new[0] == 2 && var->new[1] == 2 && var->new[2] == '\0') || \
	(var->new[0] == 6 && var->new[1] == 5 && var->new[2] == 0))
	{
		free(var->new);
		var->new = ft_strdup("");
	}
	if (var->new[ft_strlen(var->new) - 1] == 5)
		var->new[ft_strlen(var->new) - 1] = 0;
	if ((var->new[0] == 2 && var->new[1] == '\0') || has_space(var->new))
	{	
		if (file_errors(var->new, -2, node) == 1)
			return (-1);
	}
	var->new = triiim_char(var->new, 7);
	var->i = open(var->new, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (var->i == -1)
	{
		if (file_errors(var->new, 1, node) == 1)
			return (-1);
	}
	return (0);
}

int	file_errors(char *name, int key, t_cmd *node)
{
	if (key == -2)
	{
		ft_ambiguous(1, node);
		free(name);
		return (1);
	}
	if (access(name, F_OK) == -1)
		ft_no_file_diractory(name, 1, node);
	else if (access(name, R_OK) == -1 && key == 0)
		ft_permision(name, 1, node);
	else if (access(name, W_OK) == -1 && key == 1)
		ft_permision(name, 1, node);
	return (0);
}

char	*remove_non_printble(char *s)
{
	t_var	var;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	var.new = (char *)malloc(len + 1);
	if (!var.new)
		return (NULL);
	var.i = 0;
	var.j = 0;
	while (var.i <= len)
	{
		if (s[var.i] != 5 && s[var.i] != 7)
			var.new[var.j++] = s[var.i];
		var.i++;
	}
	free(s);
	return (var.new);
}

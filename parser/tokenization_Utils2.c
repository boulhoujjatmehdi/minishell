/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_Utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:53:55 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/18 20:03:30 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

int	env_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i + 1);
}

char	*env_var(char *s)
{
	int		i;
	char	*var;

	var = (char *)malloc(env_len(s) * sizeof(char ) + 1);
	if (!var)
		return (NULL);
	i = 0;
	while (s[i] != '=')
	{
		var[i] = s[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

void	replace_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			s[i] = 7;
		i++;
	}
	return ;
}

char	*get_assos(char *s, t_list **env, int type)
{
	t_var	var;
	char	*tmp;
	t_list	*head;

	head = *env;
	while (head->content)
	{
		tmp = env_var(head->content);
		if (ft_strncmp(s, tmp, ft_strlen(tmp) + 1) == 0)
		{
			free(tmp);
			break ;
		}
		free(tmp);
		head = head->next;
	}
	free(s);
	if (!head->content)
		return (ft_strdup(""));
	var.i = env_len(head->content);
	var.k = ft_strlen(head->content) - var.i;
	var.new = ft_substr(head->content, var.i, var.k);
	if (type == 5)
		replace_space(var.new);
	return (var.new);
}

char	*ft_exit_status(char *str)
{
	char	*new;

	if (g_msh->last_st == -1)
		new = ft_strjoin2(ft_strdup("0"), str + 1);
	else
		new = ft_strjoin2(ft_itoa(g_msh->last_st), str + 1);
	free(str);
	return (new);
}

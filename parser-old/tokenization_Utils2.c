/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_Utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:53:55 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/15 15:19:01 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"parse.h"

extern int g_exit;

int	env_len(char *s)
{
	int i;

	i = 0;
	while(s[i] != '=')
		i++;
	return (i + 1);
}

char	*env_var(char *s)
{
	int i;
	char *var;

	var = (char *)malloc(env_len(s) * sizeof(char ) + 1);
	if (!var)
		return NULL;
	i = 0;
	while(s[i] != '=')
	{
		var[i] = s[i];
		i++;	
	}
	var[i] = '\0';
	return (var);
}

char	*get_assos(char *s, t_list **env)
{
	int len;
	int size;
	char *new;
	char *tmp;
	t_list *head;

	head = *env;
	while (head->content)
	{
		tmp = env_var(head->content);
		if (ft_strncmp(s, tmp, ft_strlen(tmp) + 1) == 0)
			break ;
		free(tmp);
		head = head->next;
	}
	if (!head->content)
		return (ft_strdup(""));
	len = env_len(head->content);
	size = ft_strlen(head->content) - len;
	new = ft_substr(head->content, len, size);
	return (new);
}

char	*ft_exit_status(char *str)
{
	char 	*new;

	if (g_exit == -1)
		new = ft_strjoin2(ft_strdup("0"), str + 1);
	else 
		new = ft_strjoin2(ft_itoa(g_exit), str + 1);
	free(str);
	return (new);
}

char	*ft_replace(t_tokens *node, char *from, int *l, t_list **env)
{
	char	*new;
	char	*env1;
	int		i;

	i = 1;
	*l = 0;
	if (from[i] == '\0' &&((!node->next) || (node->next && node->next->token_type == 4)))
	{
		*l = 1;
		return (ft_strdup(from));
	}
	while (from[i] && (ft_isalnum(from[i]) || from[i] == '_' || from[1] == '?'))
	{
		i++;
		if (from[1] == '?' || ft_isdigit(from[1]))
			break ;
	}
	*l = i;
	env1 = ft_substr(from, 1, i - 1);
	if (env1[0] == '?')
		return (ft_exit_status(env1));
	new = get_assos(env1, env);
	return (new);
}

char	*swap_env(char *str, t_tokens *node, t_list **env)
{
	int i;
	int l;
	char *new;
	char	*tmp;

	if (!(new = (char *)malloc(sizeof(char))))
		return 0;
	i = 0;
	l = 0;
	new[0] = '\0';
	while(str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_replace(node, &str[i], &l, env);
			new = ft_strjoin2(new, tmp);
			i += l;
		}
		else
		{
			new = ft_joinchar(new, str[i]);
			i++;
		}
	}
	free(str);
	return (new);
}
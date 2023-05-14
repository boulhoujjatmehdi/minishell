/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:20 by eboulhou          #+#    #+#             */
/*   Updated: 2023/05/13 16:13:39 by eboulhou         ###   ########.fr       */
/*   Updated: 2023/05/13 16:57:52 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int g_exit;
int ret_cases(char *s)
{
	int pos_eq;
	int pos_at;
	int i;


	i = 0;
	if(s[0] == '-' && s[1])
		return 2;
	while(s[i] && s[i]!= '=' )
	{
		if(!ft_isalnum(s[i]) && s[i] != '_' )
			return 1;
		i++;
	}
	if(!ft_isalpha(s[0]) && s[0] != '_')
		return 1;
	return 0;
}
int	export_error(char *s)
{
	int i;


	// i = 0;
	i = ret_cases(s);
	if (i == 1) // check for @ in the first section abc@def=foooo
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	else if(i == 2)
	{
		printf("bash: export: -%c: invalid option\n", s[1]);
		return (1);
	}
	return (0);
}

int ft_export(t_minishell msh , t_cmd *cmd)
{
    t_list *tmp;
	int i;

	i = 1;
	// printf("-----%s----\n", cmd->cmd_args[1]);
	// exit(22);
	if(!cmd->cmd_args[1])
	{
		ft_env_cmd(&msh, 1);
		return 0;
	}
	while (cmd->cmd_args[i])
	{
    	tmp = *msh.lenv;
		
		if (!export_error(cmd->cmd_args[i]))
		{		
    		while(tmp && tmp->content)
    		{
				int j=0;
				char *str = (char *)tmp->content;
				char *str2 = cmd->cmd_args[i];
				while(str[j] && str[j] != '=' && str2[j] && str2[j] != '=')
				{
					if(str[j] != str2[j])
						break;
					j++;
				}
				if(str[j] == 0 && str2[j] == '=')
				{
					tmp->content = cmd->cmd_args[i];
					break;
				}
				if(str[j] == '='  && str2[j] == '=')
				{
					tmp->content = cmd->cmd_args[i];
					break;
				}
				
				if(str[j] == '=' && str2[j] == 0)
					break;
				if(!str[j] && !str2[j])
					break;
    		   	tmp = tmp->next;
    		}
			if(!tmp || !tmp->content)
			{
				ft_lstlast(*msh.lenv)->content = cmd->cmd_args[i];
				ft_lstadd_back(msh.lenv, ft_lstnew(NULL));
			}
		}
		i++;
	}
	return 0;
}
int ft_cd(t_cmd *cmd, t_minishell *msh)
{
	char *str;
	char *sss = cmd->cmd_args[1];

	// printf("%d\n", sss[0]);
    if(cmd->cmd_args[1] && sss[0] != 0)
	{
       	str =cmd->cmd_args[1];
	}
    else
	{
        str = get_from_env(*msh->lenv, "HOME=", 5)+5;
		if(str)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n",2);
			g_msh->exit_st = 1;
			return 1;
		}
	}
	if(chdir(str) == -1)
	{
		g_msh->exit_st = 1;
		return 1;//TO_DO
	}
	g_msh->exit_st = 0;
    return 0;
}

int ft_echo(t_cmd *cmd)
{
    char **to_print;
	int trigger;
	trigger = 0;
    to_print = cmd->cmd_args;
    to_print++;
	while(*to_print)
	{
		if(*to_print[0]== '-')
		{
			int i = 1;
			char *str = *to_print;
			while(str[i] && str[i] == 'n')
			{
				i++;
			}
			if(str[i])
			{
				break;
			}
			to_print++;
		}
		else{
			break;
		}
			trigger = 1;
	}
    while(*to_print)
    {
            printf("%s", *to_print);
            to_print++;
			if(*to_print)
				printf(" ");
    }
	if(!trigger)
    	printf("\n");
    return 0;
}

int ft_pwd()
{
    printf("%s\n", getcwd(NULL, 0));
    return 0;
}
void ft_env_cmd(t_minishell *msh, int vars_type)
{
    t_list *tmp;
    
    tmp = *msh->lenv;
    while(tmp && tmp->content)
    {
		if(ft_strnstr_mod(tmp->content, "=") >= 0)
        	printf("%s\n", tmp->content);
		else if(vars_type)
			printf("%s\n", tmp->content);
		
		
        tmp = tmp->next;
    }
}

void ft_unset(t_minishell *msh, t_cmd *cmd)
{
    t_list *tmp;
    t_list *prv;
    char *arg;
	char *str;
	int i;
    
	prv = NULL;
		i = 1;
	while(cmd->cmd_args[i])
	{
    	tmp = *msh->lenv;
		arg = cmd->cmd_args[i];
		while(tmp && tmp->content)
		{
			if(!ft_strncmp(tmp->content, arg, ft_strlen(arg)))
			{
				str = (char *)tmp->content;
				if(str[ft_strlen(arg)] == 0 || str[ft_strlen(arg)] == '=')
				{
					if(prv)
						prv->next = tmp->next;
					else
						*msh->lenv = tmp->next;
					free(tmp->content);
					free(tmp);
					break;
				}
			}
			prv = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

int  check_builtis(t_cmd *cmd , t_minishell *msh, int nb)
{
    // puts(cmd->cmd_path);
    // puts("test");
	if(!cmd->cmd_path)
		return (0);
	if(!ft_strncmp(cmd->cmd_path, "export", 7))
	{
		ft_export(*msh, cmd);
        return 1;
	}
	if(!ft_strncmp(cmd->cmd_path, "unset", 6))
	{
		ft_unset(msh, cmd);
        return 1;
	}
	if(!ft_strncmp(cmd->cmd_path, "echo", 5))
	{
		ft_echo(cmd);
        return 1;
	}
	if(!ft_strncmp(cmd->cmd_path, "cd", 3))
	{
		// printf("%d\n", nb);
		if(nb == 0)
			ft_cd(cmd , msh);
        return 1;
	}
	if(!ft_strncmp(cmd->cmd_path, "pwd", 4))
	{
		ft_pwd();
        return 1;
	}
	if(!ft_strncmp(cmd->cmd_path, "env", 4))
	{
		ft_env_cmd(msh , 0);
        return 1;
	}
	if(!ft_strncmp(cmd->cmd_path, "exit", 5))
	{
		exit(0);
        return 1;
	}
    
    return 0;
}
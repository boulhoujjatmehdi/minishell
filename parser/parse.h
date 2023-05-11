#ifndef PARSE_H
# define PARSE_H

#include"../ft_minishell.h"
#include<fcntl.h>
#define	PIPE_TOKEN 1
#define	ARG_TOKEN 2
#define RED_TOKEN 3
#define SPACE_TOKEN 4
#define	ENV_VAR 5
#define	DQUOTE 6
#define	QUOTE 7


t_tokens	*lstnew(void *content);
void		addback(t_tokens **list, t_tokens *new);
t_tokens	*lstlast(t_tokens *lst);
void	give_pos(t_tokens **list);
void	delete_node(t_tokens **head, int key);
void	del_space(t_tokens **list);
void	del_empty(t_tokens **list);
void	adjest(t_tokens **list);
int		syntax_error(t_tokens **list);
void	check_double_red(t_tokens **list);
void	free_token(t_tokens **list);
char	*ft_joinchar(char *s, char c);

t_cmd	*lstnew2(void *content);
void	addback2(t_cmd **list, t_cmd *new);
t_cmd	*lstlast2(t_cmd *lst);
void	delete_node2(t_cmd **head, int key);
size_t	ft_strlen2(char *s);
char	*ft_strjoin2(char *s1, char *s2);
void	free_cmd(t_cmd **list);

char	**ft_get_paths(char *env[]);
char	*ft_env(char **env);
char	*ft_cmd_path(char *cmd, char *env[], t_cmd *node);
char	*ft_cmd_path2(char *cmd, char *env[], t_cmd *node);
int		check_diractory(char *cmd, t_cmd *node);
void	ft_is_a_diractory(char *cmd, int exit_code, t_cmd *node);
void	ft_is_not_diractory(char *cmd, int exit_code, t_cmd *node);
void	ft_no_file_diractory(char *file_name, int exit_code, t_cmd *node);
void	ft_permision(char *cmd, int exit_code, t_cmd *node);
void	ft_cmd_not_found(char *cmd, int exit_code, t_cmd *node);
void	ft_ambiguous(char *name, int exit_code, t_cmd *node);

char		*my_strtok(char **ss);
int			token_type(char *s);

t_cmd *main_function(int ac, char *av, t_list **env);
void	proccesing_cmd(t_cmd *node, char **env);
void print(t_tokens **list);

#endif
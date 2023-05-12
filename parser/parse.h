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

int check_builtins(char *cmd);
char	**ft_get_paths(char *env[]);
char	*ft_env(char **env);
int		check_diractory(char *cmd, t_cmd *node);
char	*ft_cmd_path(char *cmd, char *env[], t_cmd *node);
char	*ft_cmd_path2(char *cmd, char *env[], t_cmd *node);
void	ft_is_a_diractory(char *cmd, int exit_code, t_cmd *node);
void	ft_is_not_diractory(char *cmd, int exit_code, t_cmd *node);
void	ft_permision(char *cmd, int exit_code, t_cmd *node);
void	ft_cmd_not_found(char *cmd, int exit_code, t_cmd *node);
void	ft_no_file_diractory(char *file_name, int exit_code, t_cmd *node);
void		ft_ambiguous(int exit_code, t_cmd *node);
t_tokens	*lstnew(void *content);
void		addback(t_tokens **list, t_tokens *new);
t_tokens	*lstlast(t_tokens *lst);
void	give_pos(t_tokens **list);
void	delete_node(t_tokens **head, int key);
size_t	ft_strlen2(char *s);
char	*ft_strjoin2(char *s1, char *s2);
void	give_key(t_cmd **list);
void	free_cmd(t_cmd **list);
t_cmd	*lstnew2(void *content);
void	addback2(t_cmd **list, t_cmd *new);
t_cmd	*lstlast2(t_cmd *lst);
void	delete_node2(t_cmd **head, int key);
t_cmd *main_function(int ac, char *str, t_list **env);
char	*ft_rplc(char *from, int *l, t_list **env);
char	*herdoc_env(char *str, t_list **env);
void	check_delimeter(char *s);
int	get_here_doc(char *name, t_list **env);
int procces_her_doc(char *s, t_cmd *node);
int procces_readfiles(char *s, t_cmd *node);
int procces_writefiles(char *s, t_cmd *node);
int procces_appendfiles(char *s, t_cmd *node);
int	input_file(t_cmd *node);
int output_file(t_cmd *node);
char	*ft_strchr1(char *s, int c, int c1);
char	*ft_strchr2(char *s, int c, int c1);
char	*get_filename(char *s, int c, int c1);
int	ft_strrchr1(const char *s, int c);
int	file_errors(char *name, int key, t_cmd *node);
void	return_red(char *s);
char	**get_cmd_opt(char *s);
void	proccesing_cmd(t_cmd *node, char **env);
int	skip_opt(char *s, char c);
int	get_env_var(char *s);
int	quote_error(char start, char end);
char	*ft_joinchar(char *s, char c);
int	is_not_arg(char c);
char	*ft_part_one(char **ss, char *s, int *l);
char	*my_strtok(char **ss);
void	replace_red(char *s);
int	check_after_heredoc(t_tokens *node);
void	check_env(t_tokens **list, t_list **env);
int	env_len(char *s);
char	*env_var(char *s);
char	*get_assos(char *s, t_list **env);
char	*ft_exit_status(char *str);
char	*ft_replace(t_tokens *node, char *from, int *l, t_list **env);
char	*swap_env(char *str, t_tokens *node, t_list **env);
int8_t	join_two_nodes(t_tokens *node1, t_tokens *node2);
void	mark_delelimeter(t_tokens **list, int key);
void	adjest(t_tokens **list);
void	del_emptyyy(t_tokens **list);
int	syntax_error(t_tokens **list);
void	check_double_red(t_tokens **list);
void	free_token(t_tokens **list);
int	token_type(char *s);
void	listing_cmd(t_tokens **list1, t_cmd **list2);
void	del_space(t_tokens **list);



#endif
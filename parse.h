#include"ft_minishell.h"
#define	PIPE_TOKEN 1
#define	ARG_TOKEN 2
#define RED_TOKEN 3
#define SPACE_TOKEN 4

typedef struct s_cmd
{
	int infile;
	int outfile;
	char **cmd_args;
	char *cmd_path;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_cmd_list
{
	t_cmd	*current;
	struct s_cmd_list *next;
}	t_cmd_list;

typedef struct s_tokens
{
	int				token_type;
	char			*token;
	struct s_tokens *next;
}	t_tokens;
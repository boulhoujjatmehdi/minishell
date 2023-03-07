
all:
	clear && gcc ft_main.c -lreadline libft/libft.a get_next_line.c get_next_line_utils.c ft_args.c ft_commands.c ft_childs.c && ./a.out
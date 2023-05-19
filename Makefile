
SRC = main.c 

PRS = parser.c spliter.c LList1.c LList2.c cmd_path_Utils.c cmd_path_Utils1.c cmd_path_Utils2.c LList2_Utils.c proccosing_Utils1.c \
proccosing_Utils2.c proccosing_Utils3.c proccosing_Utils4.c proccosing_Utils5.c proccosing_Utils6.c proccosing.c spliter_Utils.c tokenization_Utils1.c tokenization_Utils2.c \
tokenization_Utils3.c tokenization_Utils4.c tokenization_Utils5.c tokenization.c my_splite.c freee.c 

EXE = exec.c gets.c childs.c builtins.c\
	builtins_2.c builtins_3.c

OTH = get_next_line.c get_next_line_utils.c

LBT = libft/libft.a

RDL = 	-lreadline \
			-L /Users/eboulhou/.brew/opt/readline/lib -I /Users/eboulhou/.brew/opt/readline/lib/include
CC = cc \
	-Wall -Wextra -Werror
NAME = minishell

HDS = ft_minishell.h ft_struct.h EXEC/exec.h PARSER/parse.h

all:$(NAME)

$(NAME): $(LBT) $(addprefix PARSER/, $(PRS)) $(addprefix EXEC/, $(EXE)) $(addprefix other_src/, $(OTH)) main.c $(HDS)
	$(CC)   $(addprefix PARSER/, $(PRS)) $(addprefix EXEC/, $(EXE)) $(RDL)  $(addprefix other_src/, $(OTH)) $(LBT)  $(SRC) -o minishell

$(LBT): 
	make -C libft bonus

clean:
	make -C libft clean


fclean:clean
	make -C libft fclean
	rm -rf minishell
re: fclean all

ex:
	clear && ./minishell
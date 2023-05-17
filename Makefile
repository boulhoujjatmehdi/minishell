

SRC = libft/libft.a main.c 

PRS = parser.c spliter.c LList1.c LList2.c cmd_path.c cmd_path_Utils1.c cmd_path_Utils2.c LList2_Utils.c proccosing_Utils1.c \
proccosing_Utils2.c proccosing_Utils3.c proccosing.c spliter_Utils.c tokenization_Utils1.c tokenization_Utils2.c \
tokenization_Utils3.c tokenization_Utils4.c tokenization.c my_splite.c freee.c

EXE = exec.c gets.c childs.c builtins.c

OTH = get_next_line.c get_next_line_utils.c

LBT = libft/libft.a

RDL = 	-lreadline \
			#-L /Users/eboulhou/.brew/opt/readline/lib -I /Users/eboulhou/.brew/opt/readline/lib/include

all: $(LBT)
	cc  $(addprefix parser/, $(PRS)) $(addprefix EXEC/, $(EXE)) $(RDL)  $(addprefix other_src/, $(OTH)) $(SRC)  -o minishell

$(LBT): 
	make -C libft bonus
	# make -C libft clean

run: clear	all	
	./minishell

clear:
	rm -rf minishell
	# make -C libft fclean

ex:
	clear && ./minishell
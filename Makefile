

SRC = libft/libft.a main.c 

PRS = parser.c spliter.c	LList1.c LList2.c  cmd_path.c 

EXE = exec.c gets.c childs.c builtins.c

OTH = get_next_line.c get_next_line_utils.c

LBT = libft/libft.a

RDL = 	-lreadline -L /Users/eboulhou/.brew/opt/readline/lib -I /Users/eboulhou/.brew/opt/readline/lib/include

all: $(LBT)
	cc  $(addprefix parser/, $(PRS)) $(addprefix EXEC/, $(EXE)) $(RDL)  $(addprefix other_src/, $(OTH)) $(SRC)  -o minishell


$(LBT): 
	make -C libft bonus
	# make -C libft clean

run: clear	all	
	./minishell

clear:
	clear
ex:
	clear && ./minishell
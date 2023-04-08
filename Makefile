

SRC = libft/libft.a main.c -lreadline

PRS = parser.c spliter.c	LList1.c LList2.c  cmd_path.c 

EXE = exec.c

LBT = libft/libft.a

all: $(LBT)
	cc $(addprefix parser/, $(PRS)) $(addprefix EXEC/, $(EXE)) $(SRC)


$(LBT): 
	make -C libft
	make -C libft clean

run: clear	all	
	./a.out

clear:
	clear
ex:
	clear && ./a.out
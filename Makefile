

SRC = libft/libft.a main.c -lreadline

PRS = parser.c spliter.c	LList1.c LList2.c  cmd_path.c 

LBT = libft/libft.a

all: $(LBT)
	gcc $(addprefix parser/, $(PRS)) $(SRC)

$(LBT): 
	make -C libft
	make -C libft clean

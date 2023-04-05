

SRC = parser.c spliter.c	LList1.c LList2.c libft/libft.a cmd_path.c 

LBT = libft/libft.a
all: $(LBT)
	gcc $(SRC)

$(LBT): 
	make -C libft
	make -C libft clean




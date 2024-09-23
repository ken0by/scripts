RM	=	rm -rf

CC	=	g++
CFLAGS	=	-std=c++17

NAME	=	script

SRC	=	script.cpp

OBJ_DIR	=	./obj/
OBJ	=	$(OBJ_DIR)/script.o

##########COLORES##########
DEF_COLOR = \033[0;39m
CUT = \033[K
R = \033[31;1m
G = \033[32;1m
Y = \033[33;1m
B = \033[34;1m
P = \033[35;1m
GR = \033[30;1m
END = \033[0m

##########REGLAS##########
all: $(OBJ_DIR) $(NAME)
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(OBJ): $(OBJ_DIR) $(SRC)
	@$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(G)Program compiled!$(DEF_COLOR)-> $@\n"

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_DIR)
	@echo "$(R)All .o files removed$(DEF_COLOR)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ_DIR)
	@echo "$(R)Executable & OBJ directory removed$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re

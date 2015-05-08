
SRC_PATH			=	src/
OBJ_PATH			=	obj/
INC_PATH			=	inc/
STYPE				=	c
SRC_FILES			=	$(shell ls $(SRC_PATH) | grep .$(STYPE)$$)
OBJ_FILES			=	$(patsubst %.$(STYPE), $(OBJ_PATH)%.o,$(SRC_FILES))

PLATFORM			:=	$(shell uname)
CC					=	gcc
HEADER				=	-I./$(INC_PATH) -I./minilibx_macos/
FLAGS				=	-Ofast -g -Wall -Wextra -Werror
VARS				=	-D_DEBUG
NAME				=	scop

LIBS				=	-framework OpenGL -framework AppKit ./minilibx_macos/libmlx.a -lm

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(OBJ_FILES) $(FLAGS) $(VARS) $(HEADER) -o $(NAME) $(LIBS)

$(patsubst %, $(OBJ_PATH)%,%.o): $(SRC_PATH)$(notdir %.$(STYPE))
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $(FLAGS) $(VARS) $(HEADER) "$<" -o "$@"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)

re: fclean all

l: re
	@./$(NAME)

launch: l

.PHONY: clean fclean re

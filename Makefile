

NAME        = cub3D

CC          = cc    

CFLAGS = -Wall -Wextra -Werror -O3 -I$(HOME)/.local/include
CFLAGS =  -O3 -I$(HOME)/.local/include
GLFW        = -L$(HOME)/.brew/Cellar/glfw/3.4/lib -lglfw
OBJ_DIR     = ./obj/

SRC_DIR     = ./

MLX = -L$(HOME)/.local/lib -lmlx42 -lm

SRCS        = $(shell find ./Mandatory -name '*.c')



OBJS        = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) Mandatory/include/cub3d.h
	$(CC) $(CFLAGS) $(OBJS) $(GLFW) $(MLX) -o $(NAME)

$(OBJ_DIR)%.o:  $(SRC_DIR)%.c Mandatory/include/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

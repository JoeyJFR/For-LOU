SRCS_DIR = src
OBJS_DIR = obj

SRCS = main.c init.c hook.c draw1.c draw2.c move.c\
game_utils1.c


OBJS=$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

NAME = cub3D

CC = cc

CFLAGS = -Wall -Werror -Wextra -Iincludes

LFLAGS = -L./includes/minilibx-linux -lmlx_Linux -lX11 -lXext -lm

MINILIBX_DIR = includes/minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a


all: $(NAME)

$(NAME): $(OBJS) $(MINILIBX)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME) 

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c includes/cub.h Makefile | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

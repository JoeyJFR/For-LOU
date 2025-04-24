include cub3d.mk

OBJS_DIR = obj/

OBJS := $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))
NAME = cub3D

CC = cc
CFLAGS = -I includes/ -g3
# -Wall -Werror -Wextra
LIBFT_FLAGS = -Llibft -Ilibft/srcs/ -lft
LFLAGS = -L./includes/minilibx-linux -lmlx_Linux -lX11 -lXext -lm

MINILIBX_DIR = includes/minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a


all: init $(NAME)

init:
	@mkdir -p $(OBJS_DIR)

$(NAME): libft/libft.a $(OBJS) $(MINILIBX)
	$(CC) $(OBJS) $(LIBFT_FLAGS) $(LFLAGS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c includes/cub.h Makefile | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

libft/libft.a: FORCE
	@$(MAKE) -C libft

clean:
	rm -rf $(OBJS_DIR)
	rm -rf libft/objs

fclean: clean
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean all

.PHONY: all clean fclean re init

.PHONY: FORCE
FORCE:

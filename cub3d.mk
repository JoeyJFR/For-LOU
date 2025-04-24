override SRCS_DIR	:= src/
override SRCS		= $(addprefix $(SRCS_DIR), $(SRC))

override PARSINGDIR		:= parsing/
override GAMEDIR		:= game/

SRC	+= $(addsuffix .c, $(MAIN))

override MAIN	:= \
main

SRC	+= $(addprefix $(GAMEDIR), $(addsuffix .c, $(GAME)))

override GAME	:= \
init \
draw \
game_utils1 \
hook \
draw_loop \
move

SRC	+= $(addprefix $(PARSINGDIR), $(addsuffix .c, $(PARSING)))

override PARSING	:= \
free_utils \
parsing \
parsing_check_map \
parsing_copy_map \
parsing_fill_struct \
parsing_fill_struct_color \
parsing_fill_struct_content \
parsing_map \
parsing_pre_check \
parsing_utils \
parsing_utils_free \
parsing_alloc_tab

NAME = cub3D

FLAGS = -Wall -Wextra -Werror #-fsanitize=leak

SRCS = main.c \
src/utils.c \
src/parse/check_input.c \
src/parse/parse_utils.c \
src/parse/get_elements.c \
src/parse/parsing.c \
src/parse/get_map.c \
src/parse/get_rgb.c \
src/parse/parse_map.c \
src/render/draw_frame.c \
src/render/draw_textures.c \
src/render/raycast.c \
src/render/draw_line.c \
src/game/start_game.c \
src/game/handle_input.c \
src/game/input_utils.c \
src/game/minimap.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I include ./libft/libft.a -Iminilibx-linux -Lminilibx-linux -lmlx -lXext -lX11 -lm -lbsd

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@make -C minilibx-linux
	$(CC) $(FLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@make clean -C minilibx-linux
	rm -rf $(OBJS)

fclean:
	@make fclean -C libft
	@make clean -C minilibx-linux
	@rm -rf $(OBJS)
	@rm -rf $(NAME)

norme:
	norminette main.c cub3d.h src libft

re: fclean all

.PHONY: all re clean fclean norme

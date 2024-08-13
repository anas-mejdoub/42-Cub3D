
SRC =	./sources/parser/parser.c ./sources/parser/parser_utils.c  ./sources/parser/texture_parsing.c ./sources/parser/map_parsing.c\
		./sources/cub3d.c \
		./sources/raycasting/utils.c \
		./sources/raycasting/raycaster.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I ./includes -I ./super_libft -fsanitize=address -g

NAME = cub3d

CC = cc

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./super_libft
	$(CC) $(CFLAGS) ./super_libft/libft.a ./MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./super_libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./super_libft
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re

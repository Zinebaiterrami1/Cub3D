NAME = cub3D

CC = cc
MLXFLAGS = -Lmlx -lmlx -lXext -lX11 -lm
CFLAGS = -Wextra -Wall -Werror -g #-fsanitize=address -g3


SOURCE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		 main.c  raycasting/draw.c parsing/parsing.c\
		 utils/ft_split.c utils/ft_strncmp.c utils/ft_memcpy.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strlcpy.c\
		 Cub3D.c raycasting/raycasting.c raycasting/texture.c raycasting/texture2.c raycasting/key_hook.c\
		 raycasting/win.c raycasting/animated_player.c raycasting/texture3.c raycasting/map.c \
		 raycasting/utils1.c  parsing/parse_color.c parsing/parse_tex.c parsing/free.c\
		 parsing/parse_map_utils.c  parsing/map_processing.c  parsing/map_validation_borders.c  parsing/map_validation_inside.c  parsing/map_validation_player.c\

OBJECT = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	 	$(CC) $(CFLAGS) $(OBJECT) $(MLXFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJECT)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY: $(OBJECT)
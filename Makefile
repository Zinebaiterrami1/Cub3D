NAME = cub3D

CC = cc
MLXFLAGS = -Lmlx -lmlx -lXext -lX11 -lm
CFLAGS = -Wextra -Wall -Werror -g #-fsanitize=address -g


SOURCE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		parsing/parse_map.c main.c  raycasting/draw.c parsing.c\
		utils/ft_split.c utils/ft_strncmp.c utils/ft_memcpy.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strlcpy.c\
		 cub3d.c raycasting/raycasting.c raycasting/texture.c raycasting/texture2.c raycasting/key_hook.c\
		 raycasting/win.c raycasting/animated_player.c\

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
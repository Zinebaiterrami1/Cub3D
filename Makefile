NAME = cub3D
BONUS_NAME = cub3D-Bonus
CC = cc
MLXFLAGS = -Lmlx -lmlx -lXext -lX11 -lm
CFLAGS = -Wextra -Wall -Werror -g3 #-fsanitize=address -g3


SOURCE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\
		 cub/raycasting/draw.c cub/raycasting/key_hook.c cub/raycasting/raycasting.c cub/raycasting/texture.c\
		 cub/raycasting/texture2.c cub/raycasting/texture3.c cub/raycasting/utils1.c cub/raycasting/win.c\
		 utils/ft_split.c utils/ft_strnstr.c utils/ft_strncmp.c utils/ft_memcpy.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strlcpy.c\
		 cub/Cub3D.c cub/init.c cub/main.c logo.c cub/parsing/helper.c\
		 cub/parsing/parse_color.c cub/parsing/parse_tex.c cub/parsing/free.c cub/parsing/parsing.c cub/parsing/parse_map_utils.c\
		 cub/parsing/map_processing.c  cub/parsing/map_validation_borders.c  cub/parsing/map_validation_inside.c  cub/parsing/map_validation_player.c\

SOURCE-BONUS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\
			   cub-Bonus/raycasting/draw.c cub-Bonus/raycasting/key_hook.c cub-Bonus/raycasting/raycasting.c cub-Bonus/raycasting/texture.c\
			   cub-Bonus/raycasting/texture2.c cub-Bonus/raycasting/texture3.c cub-Bonus/raycasting/utils1.c cub-Bonus/raycasting/win.c cub-Bonus/raycasting/animated_player.c\
			   utils/ft_split.c utils/ft_strnstr.c utils/ft_strncmp.c utils/ft_memcpy.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strlcpy.c\
			   cub-Bonus/Cub3D.c cub-Bonus/init.c cub-Bonus/main.c logo.c cub/parsing/helper.c\
			   cub-Bonus/parsing/parse_color.c cub-Bonus/parsing/parse_tex.c cub-Bonus/parsing/free.c cub-Bonus/parsing/parsing.c cub-Bonus/parsing/parse_map_utils.c\
			   cub-Bonus/parsing/map_processing.c  cub-Bonus/raycasting/map.c cub-Bonus/parsing/map_validation_borders.c  cub-Bonus/parsing/map_validation_inside.c  cub-Bonus/parsing/map_validation_player.c\

OBJECT = $(SOURCE:.c=.o)
OBJECT_BONUS = $(SOURCE-BONUS:.c=.o)

all: $(NAME)
bonus: $(BONUS_NAME)

$(NAME): $(OBJECT)
		$(CC) $(CFLAGS) $(OBJECT) $(MLXFLAGS) -o $(NAME)

$(BONUS_NAME): $(OBJECT_BONUS)
		$(CC) $(CFLAGS) $(OBJECT_BONUS) $(MLXFLAGS) -o $(BONUS_NAME)

clean:
	rm -rf $(OBJECT) $(OBJECT_BONUS)

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean all bonus

.SECONDARY: $(OBJECT) $(OBJECT_BONUS)
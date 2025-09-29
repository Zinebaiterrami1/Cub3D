NAME = cub3D

CC = cc

CFLAGS = -Wextra -Wall -Werror #-fsanitize=address

SOURCE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		parsing/parse_map.c \
		utils/ft_split.c utils/ft_memcpy.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strlcpy.c\
		  main.c cub3d.c\

OBJECT = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	 	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)

clean:
	rm -rf $(OBJECT)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY: $(OBJECT)
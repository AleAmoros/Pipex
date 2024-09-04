NAME = pipex
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRC = pipex.c utils_parse.c error.c validate.c command.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

bonus: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean bonus

.PHONY: bonus clean fclean re
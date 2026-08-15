NAME        = contamination_sim
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -I includes

SRC         = main.c \
							display.c \
							grid.c \
							simulation.c \
							contamination.c
OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
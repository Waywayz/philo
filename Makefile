NAME = philo

SRC = philo.c verif_arg.c init.c utils.c philo_day.c

OBJ = $(SRC:.c=.o)

HEADER = philo.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(HEADER)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

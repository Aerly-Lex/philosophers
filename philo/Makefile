NAME	:= philo

CC		:= gcc

CFLAGS	:= -Wall -Werror -Wextra -O2 #-fsanitize=thread -g

PTHREADS:= -lpthread

SRC		:=	main.c \
			routine.c \
			ft_error.c \
			utils.c \
			ft_forks.c \
			ft_libft.c

OBJ		:= $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(PTHREADS)
	@echo "Compiled successfully: $(NAME)"

all: $(NAME)

clean:
	rm -f *.o $(OBJ)
	@echo "Objectfiles removed"

fclean: clean
	rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all, clean, fclean, re

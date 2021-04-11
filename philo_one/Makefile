NAME = philo_one

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FILES_C = main.c\

FILES_O = $(addprefix objs/, $(FILES_C))

SRCS = $(addprefix srcs/, $(FILES_C))
OBJS = $(FILES_O:.c=.o)

objs/%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $<  -o $@
	
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

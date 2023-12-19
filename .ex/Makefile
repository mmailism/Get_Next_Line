CC = cc
CC_FLAGS = -Wall -Wextra -Werror

SRCS = 	get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

NAME = get_next_line.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

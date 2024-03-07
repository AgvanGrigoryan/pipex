CC = cc
CFLAGS = -Wall -Werror -Wextra

PROG_NAME = pipex

UTILS = utils/ft_split.c utils/pipex_utils1.c utils/pipex_utils2.c utils/get_next_line.c utils/get_next_line_utils.c

SRCS = pipex_main.c processes.c pipes.c $(UTILS)
OBJS = $(SRCS:.c=.o)


all : $(PROG_NAME)

$(PROG_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG_NAME)

%.o : %.c pipex.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(PROG_NAME)

re: fclean all

.PHONY: all clean fclean re
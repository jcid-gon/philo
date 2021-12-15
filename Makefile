NAME = philo

SRCS_MAIN = philosophers.c

SRCS = srcs/utils.c 	\
	   srcs/eat.c		\
	   srcs/threads.c	\
	   srcs/message.c

OBJS = $(SRCS:.c=.o)
OBJS_MAIN = $(SRCS_MAIN:.c=.o)
CC	= clang
CCFLAGS	= -Wall -Wextra -Werror
INCLUDE	= -lpthread -g
RM = rm -rf

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OBJS_MAIN) $(OBJS)
	$(CC) $(CCFLAGS) $(INCLUDE) $(OBJS_MAIN) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_MAIN)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

NAME        = minishell

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -I. -Ift

RM          = rm -f

SRCS        = main.c \
              ft/ft_strcmp.c \
              ft/ft_printf.c \
              ft/ft_printf_utils.c \

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re
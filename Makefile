NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft
RLFLAGS = -lreadline

SRCS = main.c signals.c add_to_history.c tokenize.c utilis.c parser.c \
     ft_execution.c redirection.c builtin_functions.c environment_variables.c \
	 utilis_builtin.c quotes.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT_LIB):
	make bonus -C $(LIBFT_DIR); 

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(RLFLAGS) $(LIBFT_LIB) -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

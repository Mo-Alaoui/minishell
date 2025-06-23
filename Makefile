NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft  #-fsanitize=address
RLFLAGS = -lreadline

SRCS = main.c tokenize_utilis.c utilis3.c utilis_builtin_two.c pipe_red_utilis.c \
	   add_to_history.c ft_calls.c ft_ft.c tokenize.c utilis.c utilis1.c  \
	   utilis2.c parser.c quotes.c ft_execution.c check_herdoc.c pipe.c pipe_utilis.c \
	   pipe_red.c quotes_utilis.c quotes_utilis_two.c builtin_functions.c \
	   builtin_functions_utilis.c environment_variables.c environment_variables_utilis.c \
	   utilis_builtin.c
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
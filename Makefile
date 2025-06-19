NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft 
RLFLAGS = -lreadline


SRCS = add_to_history.c builtin_functions_utilis.c builtin_functions.c check_herdoc.c \
       environment_variables_utilis.c environment_variables.c ft_execution.c main.c \
       parser.c pipe_red.c pipe.c quotes_utilis.c quotes.c tokenize_utilis.c tokenize.c \
	   utilis_builtin_two.c utilis_builtin.c utilis.c utilis1.c quotes_utilis_two.c
	      
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
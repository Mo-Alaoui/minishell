NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft -I.
RLFLAGS = -lreadline 

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/tokenize_utilis.c $(SRC_DIR)/utilis3.c $(SRC_DIR)/utilis_builtin_two.c $(SRC_DIR)/pipe_red_utilis.c \
       $(SRC_DIR)/add_to_history.c $(SRC_DIR)/ft_calls.c $(SRC_DIR)/ft_ft.c $(SRC_DIR)/tokenize.c $(SRC_DIR)/utilis.c $(SRC_DIR)/utilis1.c \
       $(SRC_DIR)/utilis2.c $(SRC_DIR)/parser.c $(SRC_DIR)/quotes.c $(SRC_DIR)/ft_execution.c $(SRC_DIR)/check_herdoc.c $(SRC_DIR)/pipe.c $(SRC_DIR)/pipe_utilis.c \
       $(SRC_DIR)/pipe_red.c $(SRC_DIR)/quotes_utilis.c $(SRC_DIR)/quotes_utilis_two.c $(SRC_DIR)/builtin_functions.c \
       $(SRC_DIR)/builtin_functions_utilis.c $(SRC_DIR)/environment_variables.c $(SRC_DIR)/environment_variables_utilis.c \
       $(SRC_DIR)/utilis_builtin.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT_LIB):
	make bonus -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(RLFLAGS) $(LIBFT_LIB) -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJS)

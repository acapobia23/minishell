SRC =	main.c clear_functions.c handle_signal.c data_init.c parsing/parsing_e_token.c parsing/token_utils.c \
		parsing/token_utils_two.c test.c
		
NAME = minishell
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -Llibft -lft
RM = rm -f

all: $(NAME) credit

$(LIBFT_A):
	@make -s -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LDFLAGS)

clean:
	@make -s -C $(LIBFT_DIR) clean $(LIBFT)
	@$(RM) $(OBJ)

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean $(LIBFT)
	@$(RM) $(NAME)

re: fclean all

credit:
	@echo "\033[38;5;51m minishell ready to start \033[1;38;5;39m Compiled\033[0m"

.PHONY: all clean fclean re
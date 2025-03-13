SRC =	main.c clear_functions.c handle_signal.c data_init.c parsing/parsing_e_token.c parsing/token_utils.c \
		parsing/token_utils_two.c test.c parsing/lexer.c parsing/lexer_utils.c parsing/handle_quote.c \
		parsing/handle_quote_utils.c parsing/handle_dollar.c parsing/handle_dollar_utils.c parsing/quoted_dollar.c \
		set_cdm/set_cmd.c set_cdm/set_cmd_utils.c cmd_builtin/cd.c cmd_builtin/cmdcheck.c cmd_builtin/echo.c \
		cmd_builtin/env.c cmd_builtin/export.c cmd_builtin/pwd.c cmd_builtin/setenv_utils.c \
		cmd_builtin/setenv.c cmd_builtin/syscommand.c cmd_builtin/unset.c cmd_builtin/exit.c cmd_executor.c/executor_cmd.c \
		cmd_executor.c/redirection.c 
		
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
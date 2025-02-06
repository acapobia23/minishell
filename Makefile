SRC =	main.c clear_functions.c handle_signal.c data_init.c parsing_e_token.c
		
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
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LDFLAGS)

clean:
	@make -s -C $(LIBFT_DIR) clean $(LIBFT)
	$(RM) $(OBJ)

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean $(LIBFT)
	$(RM) $(NAME)

re: fclean all

credit:
	@echo "\033[38;5;51m Made by : \033[0m"
	@echo "_________                      _________ _______       .___      "
	@echo "\_   ___ \_____  ______   ____ \_   ___ \\   _  \    __| _/____  "
	@echo "/    \  \/\__  \ \____ \ /  _ \/    \  \//  /_\  \  / __ |/ __ \ "
	@echo "\     \____/ __ \|  |_> >  <_> )     \___\  \_/   \/ /_/ \  ___/ "
	@echo " \______  (____  /   __/ \____/ \______  /\_____  /\____ |\___  >"
	@echo "        \/     \/|__|                  \/       \/      \/    \/"
	@echo ""
	@echo "\033[38;5;51m minishell ready to start \033[1;38;5;39m Compiled\033[0m"

.PHONY: all clean fclean re
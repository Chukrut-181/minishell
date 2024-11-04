NAME = minishell

CC = cc
CFLAGS = -Werror -Wall -Wextra
RM = rm -rf

SRCS    := $(shell find ./src -iname "*.c")
OBJS    := ${SRCS:.c=.o}

LIBFT   := ./lib/libft
READFLAG:= -lreadline -L/Users/$(USER)/.brew/opt/readline/lib


CLR_RMV := \033[0m
RED := \033[1;31m
GREEN := \033[1;32m
YELLOW := \033[1;33m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT)  $(READFLAG) -o $(NAME)
	@echo "$(GREEN)Compilación completada!$(CLR_RMV)"

$(LIBFT):
	@make -C libft > /dev/null 2>&1

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@make clean -C libft > /dev/null 2>&1
	@echo "$(YELLOW)Eliminando objetos!$(CLR_RMV)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft > /dev/null 2>&1
	@echo "$(RED)Eliminando todo!$(CLR_RMV)"

re: fclean all

.PHONY: all clean fclean re bonus
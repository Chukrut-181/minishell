# Program name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Werror -Wall -Wextra -g
RM = rm -rf

# Directories
SOURCES_DIR = ./src/
OBJECTS_DIR = ./objects/

# List source files manually
SRCS = \
	src/builtins/management_cd.c \
	src/builtins/management_echo.c \
	src/builtins/management_env.c \
	src/builtins/management_exit.c \
	src/builtins/management_export.c \
	src/builtins/management_pwd.c \
	src/builtins/management_unset.c \
	src/execute/management_command.c \
	src/execute/multiple_command1.c \
	src/execute/multiple_command2.c \
	src/builtin_or_path.c \
	src/builtins.c \
	src/envp.c \
	src/error.c \
	src/expand.c \
	src/extract_operators.c \
	src/free.c \
	src/heredoc.c \
	src/initialize.c \
	src/main.c \
	src/parse.c \
	src/prompt_trim.c \
	src/signal.c \
	src/trim_quotes.c \

# Generate object files list
OBJS = $(SRCS:%.c=$(OBJECTS_DIR)%.o)

# External libraries
LIBFT   := ./lib/libft/libft.a
READFLAG := -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

# Colors for terminal output
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
RESET = \033[0m

# Default target
all: $(NAME)

# Link the final executable
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READFLAG) -o $(NAME)
	@echo "$(GREEN)-> Compilation completed: $(NAME)$(RESET)"

# Build object files
$(OBJECTS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Build the libft library
$(LIBFT):
	@make -C ./lib/libft > /dev/null 2>&1

# Clean object files and the objects directory
clean:
	@$(RM) $(OBJECTS_DIR)
	@make clean -C ./lib/libft > /dev/null 2>&1
	@echo "$(YELLOW)-> All .o files removed$(RESET)"

# Remove everything, including the executable
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./lib/libft > /dev/null 2>&1
	@echo "$(RED)-> $(NAME) removed$(RESET)"

# Rebuild everything from scratch
re: fclean all

# Specify targets that aren't files
.PHONY: all clean fclean re

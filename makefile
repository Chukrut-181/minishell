# Program name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Werror -Wall -Wextra -g
RM = rm -rf

# Directories
SOURCES_DIR = ./src/
OBJECTS_DIR = ./objects/

# Source and object files
SRCS    := $(shell find $(SOURCES_DIR) -iname "*.c")
OBJS    := $(patsubst $(SOURCES_DIR)%.c,$(OBJECTS_DIR)%.o,$(SRCS))

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

# Build object files copying the sources directory structure
$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
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

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

# Rule to compile a source file into an object file and store it in the objects directory.
# This rule ensures that:
# 1. The directory structure for the object file is created dynamically.
# 2. The source file is compiled into an object file without linking.
# 
# Pattern Explanation:
# - $(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
#   - Matches any .c file inside the $(SOURCES_DIR) directory and compiles it into a corresponding .o file
#     inside the $(OBJECTS_DIR) directory, preserving the subdirectory structure.
#   - The % is a wildcard representing the matching part of the filename (excluding the extension).
#     For example:
#       - If the source file is `src/builtins/command.c`:
#         - $< is `src/builtins/command.c` (prerequisite).
#         - $@ is `objects/builtins/command.o` (target).
# 
# Commands:
# 1. `mkdir -p $(dir $@)`:
#    - Extracts the directory portion of the target object file ($@).
#    - $(dir $@) ensures that the parent directory for the object file exists.
#      For example:
#        - If $@ is `objects/builtins/command.o`, $(dir $@) expands to `objects/builtins/`.
#    - mkdir -p creates the directory (and any necessary parent directories) if they do not exist.
#    - The `@` suppresses the command's output in the terminal.
# 
# 2. `$(CC) $(CFLAGS) -c $< -o $@`:
#    - Compiles the source file ($<) into an object file ($@).
#    - Flags explained:
#      - `-c`: Compile the source file into an object file, without linking.
#      - `-o $@`: Specifies the name of the output file (the target object file).
#      - $(CFLAGS): Includes compiler options like `-Wall` (all warnings), `-Wextra` (additional warnings),
#        and `-Werror` (treat warnings as errors).
#
# Example Workflow:
# - If the source file is `src/builtins/command.c`:
#   1. The target object file is `objects/builtins/command.o`.
#   2. mkdir -p ensures `objects/builtins/` exists.
#   3. The compiler generates `objects/builtins/command.o` from `src/builtins/command.c`.
$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(dir $@)  # Create the directory for the object file
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

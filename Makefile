# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dachin <dachin@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2026/02/18 12:17:36 by dachin        #+#    #+#                  #
#    Updated: 2026/03/06 17:10:03 by dachin        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


# List of source files
SRCS = src/main.c src/parsing.c src/utils.c src/utils2.c src/utils3.c

# Creates object files by replacing .c with .o. $ references variables or automatic variables
OBJS = $(SRCS:.c=.o)

# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Detect OS
UNAME_S := $(shell uname -s)

# Subproject directories
LIBFT_DIR = Libft

# Subproject libraries
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Main executable name
NAME = pipex

# Default target. Always put this in first place
all: $(NAME)

# Build main executable
$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

# Build subproject libraries
$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

# Pattern rule. Compiles any .c file into .o using specified compiler and flags
# % is a wildcard
# $@ - name of the target
# $< = name of the first prerequisite
# $^ = name of all prerequisites
# -I flag tells the compiler where to look for header files
%.o: %.c $(LIBFT_LIB)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iinclude -c $< -o $@

# $(RM) is prefined in make and equals rm -f. -f force flag avoids errors if files do not exist
clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

# Removes all object files and the library file.
fclean:	clean
	$(RM) $(NAME)
	$(RM) tests/test_runner
	make -C $(LIBFT_DIR) fclean

# Rebuilds everything by clean and all
re:	fclean all

# Declares these targets as phony (not actual files), so Make always runs them when requested.
.PHONY: all clean fclean re test sanitize

# ===== TEST SECTION =====
# Run bash test suite
test: $(NAME)
	@echo "Running test suite..."
	@cd tests && ./run_all_tests.sh

# fsanitise for macOS
sanitize: CFLAGS += -fsanitize=address -g
sanitize: re

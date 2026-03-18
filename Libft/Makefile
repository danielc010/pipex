# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dachin <dachin@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2025/05/28 13:16:09 by dachin        #+#    #+#                  #
#    Updated: 2026/03/18 12:12:02 by dachin        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# List of source files
SRCS			=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
					ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
					ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
					ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
					ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
					ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
					ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
					ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
					ft_lstmap.c ft_itoa_hex.c ft_itoa_uint.c ft_uitoa_hex.c ft_handle_char.c \
					ft_handle_int.c ft_handle_percent.c ft_handle_pointer.c ft_handle_string.c \
					ft_handle_uint.c ft_handle_hex.c ft_printf.c get_next_line.c \
					get_next_line_utils.c get_next_line_bonus.c get_next_line_utils_bonus.c \
					ft_atol.c

# Creates object files by replacing .c with .o. $ references variables or automatic variables
OBJS			= $(SRCS:.c=.o)

# Compiler and compiler flags
CC				= cc
CFLAGS			= -Wall -Wextra -Werror


# Name of output library file
NAME			= libft.a

# Formatting for rules
# TARGET: PREREQUISITE
# 	ACTION

# Default target. Always put this in first place
all:			$(NAME)

# ar builds library by archiving all obj files into $(NAME)
# r - Replace existing files or add new files to the archive.
# c - Create the archive if it does not already exist (suppresses warning if it does).
# s - Index—write an index to the archive, which speeds up linking.
$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

# $(RM) is prefined in make and equals rm -f. -f force flag avoids errors if files do not exist
clean:
				$(RM) $(OBJS)

# Removes all object files and the library file.
fclean:			clean
				$(RM) $(NAME)

# Rebuilds everything by clean and all
re:				fclean all

# Pattern rule. Compiles any .c file into .o using specified compiler and flags
# % is a wildcard
# $@ - name of the target
# $< = name of the first prerequisite
# $^ = name of all prerequisites
# -c compile source file into and object file, stopping before linking stage. Making library needs obj not exe files
# -o specify the output file name
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Declares these targets as phony (not actual files), so Make always runs them when requested.
.PHONY:			all clean fclean re sanitize debug

# fsanitise
sanitize: CFLAGS += -fsanitize=address -g
sanitize: re

# GDB
debug: CFLAGS += -g
debug: re

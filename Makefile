# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/09 20:13:52 by mraasvel      #+#    #+#                  #
#    Updated: 2020/11/16 14:31:29 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT = libft/libft.a
SRC = ft_printf.c conversion.c\
	flagsequence.c flagsequence_utils.c\
	convert_percentage.c\
	convert_character.c\
	convert_string.c\
	convert_pointer.c\
	convert_digit.c\
	convert_unsigned_digit.c\
	convert_hex.c\
	convert_n.c\
	conversion_utils.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
DEBUG = -O0 -g -fsanitize=address -fsanitize=leak

OBJDIR = obj
SRCDIR = src
IFLAG = -I include

vpath %.c src
vpath %.o obj

all: dependencies $(NAME)
.PHONY: all clean fclean re

dependencies:
	@mkdir -p obj
	@mkdir -p src

$(NAME): $(OBJ)
	cp $(LIBFT) $(NAME)
	ar rs $(NAME) $(OBJ)
$(OBJDIR)/%.o: %.c
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

# Dependencies

$(NAME): ./Makefile
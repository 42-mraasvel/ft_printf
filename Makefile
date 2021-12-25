# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/22 13:50:46 by mraasvel      #+#    #+#                  #
#    Updated: 2021/12/25 14:58:54 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT = $(LIBFTDIR)/libft.a

# Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Files
SRC = ft_printf.c\
flagsequence.c\
flagsequence_utils.c\
conversion.c\
conversion_utils.c\
convert_character.c\
convert_string.c\
convert_pointer.c\
convert_digit.c\
convert_unsigned_digit.c\
convert_hex.c\
ft_round_f.c\
convert_n.c\
convert_f.c\
ft_dtoa_f.c\
convert_e.c\
ft_dtoa_e.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# Directories
LIBFTDIR = libft
OBJDIR = obj

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ)
$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -o $@ -c $(CFLAGS) $<
$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFTDIR)
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)
re: fclean all

bonus: $(NAME)

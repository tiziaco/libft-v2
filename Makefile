# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 18:33:34 by tiacovel          #+#    #+#              #
#    Updated: 2024/03/13 12:15:04 by tiacovel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= 		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
						ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
						ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
						ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c
PRINTF_SRCS		=		printf_utils/ft_putchr.c printf_utils/ft_putstr.c printf_utils/ft_putnbr.c printf_utils/ft_putunbr.c printf_utils/ft_putptr.c \
						printf_utils/ft_puthexa.c printf_utils/ft_printf.c
B_SRCS			=		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS			= $(SRCS:.c=.o)
PRINTF_OBJS		= $(PRINTF_SRCS:.c=.o)
B_OBJS			= $(B_SRCS:.c=.o)
	
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -fPIE
NAME			= libft.a
HIDE = @

# ANSI escape codes for colored output
GREEN			= \033[0;32m
NC				= \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_OBJS)
		$(HIDE) ar rcs $(NAME) $(OBJS) $(PRINTF_OBJS)

bonus: $(B_OBJS)
		$(HIDE) $(CC) $(CFLAGS) -c $(B_SRCS) -o $(B_OBJS)
		$(HIDE) ar rc $(NAME) $(B_OBJS)

%.o: %.c
		$(HIDE) $(CC) $(CFLAGS) -c $< -o $@

clean:
		$(HIDE) $(RM) $(PRINTF_OBJS) *.o
		@echo "\033[0;31mLibft objs removed.\033[0m"

fclean: clean
		$(HIDE) $(RM) $(NAME)
		@echo "\033[0;31mLibft.a removed.\033[0m"
		
re: fclean all

.PHONY: all clean fclean re bonus

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 12:19:21 by fgras-ca          #+#    #+#              #
#    Updated: 2024/01/15 22:06:15 by fgras-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RST				= \033[0m
GRAY			= \033[0;90m
RED				= \033[0;91m
GREEN			= \033[0;92m
YELLOW			= \033[0;93m
BLUE			= \033[0;94m
MAGENTA			= \033[0;95m
CYAN			= \033[0;96m
WHITE			= \033[0;97m
ORANGE			= \033[38;5;214m

NAME = libft.a

SOURCES =	ft_atoi.c \
		ft_isalpha.c \
		ft_memchr.c \
		ft_memset.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_toupper.c \
		ft_bzero.c \
		ft_isascii.c \
		ft_memcmp.c \
		ft_strchr.c \
		ft_strlcpy.c \
		ft_strrchr.c \
		ft_calloc.c \
		ft_isdigit.c \
		ft_memcpy.c \
		ft_substr.c \
		ft_isalnum.c \
		ft_isprint.c \
		ft_memmove.c \
		ft_strncmp.c \
		ft_tolower.c\
		ft_strtrim.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_itoa.c \
		ft_strcmp.c \
		ft_strstr.c \
		ft_reallocarray.c \
		ft_strcat.c \
		ft_strcpy.c \
		ft_realloc.c \
		ft_strncpy.c \
		ft_strtol.c \
		ft_strtok.c \

SRCBONUS =	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstiter.c \
		ft_lstmap.c \


OBJECTS = $(SOURCES:.c=.o)

BONUS_OBJ = $(SRCBONUS:.c=.o)

CC = gcc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

all:	$(NAME)

$(NAME):	$(OBJECTS)
	@echo $(CC) (CFLAGS) $(OBJECTS) -o $(NAME)

bonus:	$(OBJECTS) $(BONUS_OBJ)
	$(CC) (CFLAGS) $(OBJECTS) $(BONUS_OBJ) -o $(NAME)

clean:
	@echo $(RM) $(OBJECTS) $(BONUS_OBJ)

fclean:	clean
	@echo $(RM) $(NAME) $(BONUS_OBJ)

re:	fclean all

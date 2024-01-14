# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/14 16:54:48 by fgras-ca          #+#    #+#              #
#    Updated: 2024/01/14 21:30:03 by fgras-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC		=	main.c							\
			./utils/ft_utils_gnl.c			\
			./utils/ft_utils_split.c		\
			./utils/ft_utils_str_1.c		\
			./utils/ft_utils_convert.c		\
			./parsing/ft_map_check.c 		\
			./parsing/ft_read_map.c 		\
			./parsing/ft_map_dimensions.c	\
			./parsing/ft_parsing.c 			\
			./move/ft_collision.c 			\
			./move/ft_key.c					\
			./move/ft_move.c 				\
			./draw/ft_draw.c				\
			./draw/ft_background.c			\
			./draw/ft_2d_view.c				\
			./draw/ft_textures.c			\
			./draw/ft_3d_view.c				\
			./draw/ft_horizontal_ray.c		\
			./draw/ft_vertical_ray.c		\
			./draw/ft_pixel.c				\
			./draw/ft_ray_utils.c			\
			./window/ft_window.c			\
			./window/ft_player.c			\
			./window/ft_map.c				\
			./draw/ft_load_textures.c		\
			./window/ft_rescale.c			\



OBJ		= $(SRC:.c=.o)

FLAG	= cc -Wall -Wextra -Werror -g

RM		= rm -f

$(NAME): $(OBJ)
		$(FLAG) -Iinclude $(OBJ) -Llib -lmlx -lXext -lX11 -lm -o $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re

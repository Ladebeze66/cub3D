# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/14 16:54:48 by fgras-ca          #+#    #+#              #
#    Updated: 2024/01/15 22:11:49 by fgras-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOGO = @echo "🅹🅾🅷🅽 🅰🅽🅳 🅻🅰🅳🅴🅱🅴🆉🅴"

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

NAME = cub3d
LIBFT = libft.a

SRC		=	main.c							\
			./utils/ft_utils_gnl.c			\
			./utils/ft_utils_split.c		\
			./utils/ft_utils_convert.c		\
			./utils/ft_utils_str_1.c		\
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
			./window/ft_refresh_window.c	\
			./parsing/ft_find_map_start.c	\

SRC_DIR_LIBFT = libft/

SRC_LIBFT = $(addprefix $(SRC_DIR_LIBFT), $(LIBFT))

OBJ		= $(SRC:.c=.o)

FLAG	= cc -Wall -Wextra -Werror -g

RM		= rm -f

all:	$(NAME)

$(NAME): $(OBJ)
	@echo "$(RED)Loading Libft...$(RST)"
	@make -C libft
	@echo "$(GREEN)Libft...Done. $(RST)"
	@echo "$(RED)Compilation cub3D... $(RST)"
	@$(FLAG) -Iinclude $(OBJ) -Llib -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "$(GREEN)Compilation complete. $(ORANGE)Type "./cub3d" for execute the program!!$(RST)"
	$(LOGO)

clean:
	@echo "$(RED)Cleaning Libft... $(RST)"
	@make -C libft clean
	@echo "$(GREEN)Libft cleaned!! $(RST)"
	@echo "$(RED)Deleating files objects... $(RST)"
	@echo rm -f $(OBJ)
	@echo "$(GREEN)files deleted!! $(RST)"
	$(LOGO)

fclean:	clean
	@echo "$(RED)fclean Libft... $(RST)"
	@make -C libft fclean
	@echo "$(GREEN)Libft cleaned!! $(RST)"
	@echo "$(RED)Delete program name... $(RST)"
	@echo rm -f $(NAME)
	@echo "$(GREEN)File program deleted!! $(RST)"

re:	fclean all

.PHONY: all clean fclean re

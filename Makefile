# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tosinga <tosinga@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/04 17:43:30 by jvan-kra      #+#    #+#                  #
#    Updated: 2022/10/04 19:34:52 by tosinga       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=		fdf

SRC 	=	    src/main.c \
				src/error.c \
				src/t_fdf.c \
				src/hooks.c \
				src/parser.c \
				src/ft_atoi_save.c \
				src/t_map.c \
				src/fill_image.c \
				src/projections.c \
				src/scaling.c \
				src/offset.c \
				src/update_screen.c \
				src/draw_line.c

HEADERS				=	include/fdf.h \
						include/line.h

INCLUDE_PATH		=	include

LIBFT_LOC			=	lib/libft
LIBFT_LIB			=	$(LIBFT_LOC)
LIBFT_INCLUDE		=	$(LIBFT_LOC)/include

MLX42_LOC			=	lib/MLX42
MLX42_LIB			=	$(MLX42_LOC)
MLX42_INCLUDE		=	$(MLX42_LOC)/include

GNL_LOC				=	lib/get_next_line
GNL_LIB				=	$(GNL_LOC)
GNL_INCLUDE			=	$(GNL_LOC)/include

CFLAGS				=	-Wall -Wextra -Werror
CC					=	gcc
OBJECTS				=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJECTS) $(HEADERS)
		@$(MAKE) -s -C $(LIBFT_LOC)
		@$(MAKE) -s -C $(MLX42_LOC)
		@$(MAKE) -s -C $(GNL_LOC)
		$(CC) $(CFLAGS) $(OBJECTS) -L$(LIBFT_LOC) -lft -L$(MLX42_LOC) -lmlx42 -L$(GNL_LOC) -lgnl -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

%.o : %.c
		$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(LIBFT_INCLUDE) -I$(MLX42_INCLUDE) -I$(GNL_INCLUDE) -c -o $@ $<

clean:
		$(RM) $(OBJECTS)
		@$(MAKE) -s -C $(LIBFT_LOC) clean
		@$(MAKE) -s -C $(MLX42_LOC) clean
		@$(MAKE) -s -C $(GNL_LOC) clean

fclean: clean
		$(RM) $(NAME)
		@$(MAKE) -s -C $(LIBFT_LOC) fclean
		@$(MAKE) -s -C $(MLX42_LOC) fclean
		@$(MAKE) -s -C $(GNL_LOC) fclean

re: 	fclean all

.PHONY:	all clean fclean re

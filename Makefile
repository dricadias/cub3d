# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 19:16:25 by adias-do          #+#    #+#              #
#    Updated: 2026/01/22 19:16:28 by adias-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lm -lmlx -lXext -lX11

LIBFTDIR = libft
RM = rm -rf

SRCS = srcs/main.c \
	srcs/init_structs.c \
	srcs/draw.c
OBJS = $(SRCS:.c=.o)

INCLUDE = -L ./libft -L mlx

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@make -s -C $(LIBFTDIR)
	make -C mlx
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME) -lft ${MLX_FLAGS}

all: $(NAME)

clean:
	$(RM) $(OBJS)
	@make -s -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -s -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
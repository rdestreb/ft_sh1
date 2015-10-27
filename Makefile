#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/25 10:38:16 by rdestreb          #+#    #+#              #
#    Updated: 2015/10/26 11:34:10 by rdestreb         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_minishell1
SRCDIR = ./src
HEADDIR = ./
HEAD = ft_minishell.h
HEADFILES = $(addprefix $(HEADDIR)/, $(HEAD))
SCRFILES = $(addprefix $(SRCDIR)/, $(SRC))
SRC =	main.c \
		print_error.c \
		shell.c \
		prompt.c \
		new_process.c \
		exec.c \
		list.c \
		env.c \
		builtin.c \
		built_env.c \
		built_setenv.c \
		built_unsetenv.c \
		built_exit.c \
		cd.c \

OBJS = $(SCRFILES:.c=.o)
CC = clang
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -L ./libft/ -lft
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C ./libft/

%.o: %.c $(HEADERFILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE) -C ./libft/ $@
	/bin/rm -f $(OBJS)

fclean: clean
	$(MAKE) -C ./libft/ $@
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

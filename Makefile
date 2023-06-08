# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 05:04:18 by ybouzafo          #+#    #+#              #
#    Updated: 2023/06/08 14:16:31 by kelmouto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g3

RM=rm -f
SRC = ft_putendl.c cd_rep.c echo.c pwd.c expan.c handl_redir.c handl_sp.c herdoc.c suntax_error.c main.c  utils.c aide.c \
		 mylibft.c my_split.c parsing.c parsing_add.c handl_quotes.c  print.c get_env.c my_export.c get_my_export.c get_export.c \
		 unset.c exec.c env.c exit.c export_utils.c  check_export.c exec_utils.c skip_quot_exp.c export_syntax.c fill_env.c builtins_utils.c builtins.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(A) $(B)
	$(CC) $(CFLAGS) $(OBJ)   -lreadline -o $(NAME)
clean:
		$(RM) $(OBJ)
fclean: clean
		$(RM) $(NAME)

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 05:04:18 by ybouzafo          #+#    #+#              #
#    Updated: 2023/06/12 18:05:06 by ybouzafo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g3

RM=rm -f
SRC = ft_putendl.c cd_rep.c echo.c pwd.c expan.c handl_redir.c handl_sp.c herdoc.c suntax_error.c main.c  utils.c aide.c \
		 mylibft.c my_split.c parsing.c parsing_add.c handl_quotes.c  print.c get_env.c my_export.c get_my_export.c get_export.c \
		 unset.c exec.c env.c exit.c export_utils.c  check_export.c exec_utils.c cd_normfor.c cd_exec.c echo_norm.c echo_norm_deux.c \
		   export_syntax.c fill_env.c  old_pwd.c builtins_utils.c expand_cmd.c skip_quot_exp.c cmd_expand.c handl_red_norm.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@stty -echoctl
	$(CC) $(CFLAGS) $(OBJ)  -I ~/Users/ybouzafo/goinfre/homebrew/Cellar/readline/8.2.1/include  -L /Users/ybouzafo/goinfre/homebrew/Cellar/readline/8.2.1/lib -lreadline -o $(NAME)
clean:
		$(RM) $(OBJ)
fclean: clean
		$(RM) $(NAME)

re: fclean all

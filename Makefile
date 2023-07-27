# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 19:04:47 by mel-moun          #+#    #+#              #
#    Updated: 2023/07/26 16:50:56 by selkhadr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
CC=cc
libft=libft/libft.a
CFLAGS=-Wall -Wextra -Werror
ARG1=-lreadline -L /Users/$(USER)/.brew/opt/readline/lib
ARGS =-Iinclude -I /Users/$(USER)/.brew/opt/readline/include
SRC= parsing/errors/errors.c\
	parsing/line/change_line.c\
	parsing/line/change_line_utils.c\
	parsing/string/ft_split.c\
	parsing/string/string.c\
	parsing/string/string1.c\
	parsing/string/string3.c\
	parsing/string/string4.c\
	parsing/expand/expand.c\
	parsing/expand/expand_utils.c\
	parsing/expand/expand_utils2.c\
	parsing/expand/expand_utils3.c\
	parsing/linked_list/first_linked_list.c\
	parsing/linked_list/manage_linked.c\
	parsing/linked_list/manage_linked1.c\
	parsing/linked_list/manage_linked3.c\
	parsing/linked_list/utils1_first_linked.c\
	parsing/linked_list/utils2_first_linked.c\
	parsing/linked_list/utils_first_linked.c\
	parsing/tokenizer/tokenizer_part1.c\
	parsing/tokenizer/tokenizer_part2.c\
	parsing/tokenizer/tokenizer_utils.c\
	parsing/tokenizer/tokenizer_utils2.c\
	parsing/tokenizer/tokenizer_utils3.c\
	parsing/env/environment.c\
	execution/chdir.c\
	execution/execution.c\
	execution/exit.c\
	execution/export_sequel.c\
	execution/export.c\
	execution/heredoc.c\
	execution/in_redctn.c\
	execution/out_redctn.c\
	execution/path.c\
	execution/print.c\
	execution/redirection.c\
	execution/unset.c\
	execution/use_builtins.c\
	execution/waiting.c\
	minishell.c\
	prompt.c\

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(libft):
	make -C libft

$(NAME): $(OBJ) $(libft)
	$(CC) $(CFLAGS) $(OBJ) $(libft) $(ARGS) -lreadline -o $(NAME) $(ARG1)

%.o: %.c
	$(CC) $(CFLAGS) $(ARGS) -c $< -o $@

clean:
	make -C libft clean
	rm -rf $(OBJ)

bonus : all

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean  all

.PHONY: all clean fclean re bonus

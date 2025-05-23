# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 15:07:12 by eberkowi          #+#    #+#              #
#    Updated: 2024/12/05 13:34:53 by eberkowi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CC := cc
FLAGS := -Wall -Wextra -Werror -g #REMOVE g
LINKFLAGS := -lreadline

CFILES := main.c \
		utilities.c \
		parsing/parsing.c \
		parsing/split_input.c \
		parsing/add_elements_to_split_input.c \
		parsing/utilities.c \
		parsing/add_quotes_and_special_elements.c \
		parsing/tokenize.c \
		parsing/free_exit_parsing_1.c \
		parsing/free_exit_parsing_2.c \
		parsing/free_exit_parsing_3.c \
		parsing/redirect_tokens.c \
		parsing/add_command_to_struct.c \
		parsing/find_var_in_env.c \
		parsing/linked_list_utils.c \
		parsing/create_heredoc.c \
		parsing/quotes_and_variables.c \
		parsing/expand_quotes_and_vars.c \
		parsing/inner_expansion.c \
		parsing/get_split_element_length.c \
		parsing/add_element_to_quote_split.c \
		parsing/create_quote_split.c \
		parsing/expand_utilities.c \
		parsing/add_elements_to_split_input_utilities.c \
		parsing/readline_to_file.c \
		parsing/readline_to_file_helper.c \
		parsing/combine_quote_split.c \
		environment/list_add_and_remove.c \
		environment/environment_utils.c \
		environment/print_environment.c \
		input_and_signals/handle_inputs.c \
		input_and_signals/signals.c \
		input_and_signals/signal_handlers.c \
		built_ins/echo.c \
		built_ins/export_without_args.c \
		built_ins/export_with_args.c \
		built_ins/unset.c \
		built_ins/pwd.c \
		built_ins/cd.c \
		built_ins/env.c \
		built_ins/exit.c \
		built_ins/ft_itoa_long.c \
		execution/execute_commandline.c \
		execution/pipeline_utils.c \
		execution/execute_builtin.c \
		execution/handle_redirects.c \
		execution/redirect_pipes.c \
		execution/execute_command.c \
		execution/execute_command_freeing.c \
		execution/find_path.c \
		execution/get_path.c \

HEADER := includes/minishell.h
LIBFT := libft/libft.a
SRC_PATH := sources/
OBJ_PATH := objects/

CFILES := $(addprefix $(SRC_PATH), $(CFILES))
OBJS := $(CFILES:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) $(OBJ_PATH)/parsing $(OBJ_PATH)/environment \
	$(OBJ_PATH)/input_and_signals $(OBJ_PATH)/built_ins $(OBJ_PATH)/execution

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LINKFLAGS)

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJ_PATH)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
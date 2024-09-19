/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:21:19 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 14:50:54 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_main
{
	char	*input;
	char	**split_input;
	int		exit_code;  //exit code of the exit command given by user?
} t_main;

typedef struct s_commands
{
	bool	null_terminate;
	char	**command;
	char	**flags;
	char	**heredoc_delimiter;
	char	**redirect_in;
	char	**redirect_out;
	bool    redirect_heredoc;
	char	**redirect_append;
}	t_commands;

//display prompt, readline, and save it in history
void	handle_inputs(char **input);

//error and exit for failed malloc in readline
int	error_exit_handle_input(void);

//Master parsing function that calls are other functions for parsing
int	parsing(t_main *main, t_commands **commands);

//A split for minishell copyright 2024
int	split_input(t_main *main);

//Free all previous malloced splits and exit
void	exit_free_split_element_malloc_failed(t_main *main, int i);

//Split the input into individual elements and check for no spaces before/after symbols
void	add_elements_to_split_input(t_main *main, char *input);

//Returns 1 if the given char is a special character that we need to handle, else 0
int	is_special(char c);

//Add single quote elements to the split_input array
void add_single_quotes_element(t_main *main, char *input, int *id_input, int id_split);

//Add double quote elements to the split_input array
void add_double_quotes_element(t_main *main, char *input, int *id_input, int id_split);

//Add special character elements to the split_input array
void add_special_character_element(t_main *main, char *input, int *i, int split_index);

//Checks for an exit command and exit-code and exits if found or shows error for incorrect format
void	exit_command(t_main *main);

#endif
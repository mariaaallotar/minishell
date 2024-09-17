/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:21:19 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/17 11:57:47 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_main
{
	char	*input;
	char	**split_input;
	int		exit_code;  //exit code of the exit command given by user?
} t_main;

//display prompt, readline, and save it in history
void	handle_input(char **input);

//error and exit for failed malloc in readline
int	error_exit_handle_input(void);

//Master parsing function that calls are other functions for parsing
void	parsing(t_main *main);

//A split for minishell copyright 2024
void	mini_split(t_main *main);

void exit_for_testing(t_main *main); //REMOVE

//Free all previous malloced splits and exit
void	exit_free_split_element_malloc_failed(t_main *main, int i);

//Split the input into individual elements and check for no spaces before/after symbols
void	add_elements_to_split_input(t_main *main, char *input);

#endif
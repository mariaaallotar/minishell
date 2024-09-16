/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:21:19 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/16 11:48:12 by eberkowi         ###   ########.fr       */
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

#endif
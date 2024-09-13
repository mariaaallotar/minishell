/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:21:19 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/13 16:38:21 by maheleni         ###   ########.fr       */
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
	int		status;     //status of what?
	int		exit_code;  //of what?
} t_main;

//display prompt, readline, and save it in history
void	handle_input(char **input);

//error and exit for failed malloc in readline
int	error_exit_handle_input(void);

//checks the input for exit and optional exit code
void handle_exit_command(t_main *main);

#endif
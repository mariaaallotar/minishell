/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:38:06 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/01 15:17:58 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_for_int_after_exit(char *element, int *temp_code)
{
	size_t itoa_result_len;
	size_t element_len;
	size_t len_to_compare;
	char *itoa_result;
	
	*temp_code = ft_atoi(element);
	itoa_result = ft_itoa(*temp_code);
	itoa_result_len = ft_strlen(itoa_result);
	element_len = ft_strlen(element);
	if (itoa_result_len > element_len)
		len_to_compare = itoa_result_len;
	else
		len_to_compare = element_len;
	if (!ft_strncmp(element, itoa_result, len_to_compare))
	{
		free(itoa_result);
		return (1);
	}
	free(itoa_result);
	return (0);
}

void	exit_command(t_main *main)		//remember to print exit to stderr
{	
	int temp_code;

	if (!ft_strncmp(main->split_input[0], "exit", 5))
	{
		//Check for no other elements
		if (!main->split_input[1])
		{
			free(main->input);
			ft_free_split(&main->split_input);
			printf("exit\n");
			exit (main->exit_code);
		}

		//Check for too many elements
		else if (main->split_input[2])
			printf("Error: Too many arguments after exit command\n");

		//Check for integer (and if between 0-255)
		else if (check_for_int_after_exit(main->split_input[1], &temp_code))
		{
			if (temp_code >= 0 && temp_code <= 255)
			{
				free(main->input);
				ft_free_split(&main->split_input);
				printf("exit\n");
				exit(temp_code);
			}
			else
				printf("Error: Exit code must be an int between 0 and 255\n");
		}
		else
			printf("Error: Exit code must be an int between 0 and 255\n");
	}
}

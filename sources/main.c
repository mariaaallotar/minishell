/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/12 10:57:13 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @authors Maria Helenius mariaaallotar
 */
int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	char *str;
	
	str = readline("minishell: ");
	printf("%s\n", str);
	free(str);
	
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marias_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/17 10:48:08 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

int	main(int argc, char *argv[], char *envp[])	//main to test stuff with
{
<<<<<<< Updated upstream
	char *line = readline("prompt: ");
	printf(":%s\n", line);
	// printf("Envp\n");
	// int i = 0;
	// while (envp[i] != NULL)
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	// char *args[] = {"bash", NULL};
	// if (execve("/bin/bash", args, envp) == 0)
	// 	printf("Problem with execv\n");
=======
	printf("Envp\n");
	int i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
    sleep(10);
    sleep(10);
	char *args[] = {"bash", NULL};
	if (execve("/bin/bash", args, envp) == 0)
		printf("Problem with execv\n");
>>>>>>> Stashed changes
}

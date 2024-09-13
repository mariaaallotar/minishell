/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marias_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:21:42 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/13 11:36:29 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])	//main to test stuff with
{
	printf("Envp\n");
	int i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	char *args[] = {"bash", NULL};
	if (execve("/bin/bash", args, envp) == 0)
		printf("Problem with execv\n");
}

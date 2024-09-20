/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:52:20 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/20 15:40:33 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    echo(t_command command)
{
    int new_line;
    int i;

    new_line = 1;
    i = 0;
    if (command.command[i] == NULL)
    {
        printf("First string NULL\n");
        //error
        return ;
    }
    while (command.command[i] != NULL)
    {
        printf("%s\n", command.command[i]);
        i++;
    }
    i = 1;
    if (ft_strncmp(command.command[i], "-n\0", 3) == 0)
    {
        new_line = 0;
        i++;
    }
    printf("After comparison\n");
    while (command.command[i] != NULL)
    {
        printf("%s", command.command[i]);
        i++;
        if (command.command[i] == NULL && new_line)
            printf("\n");
        else
            printf(" ");
    }
}
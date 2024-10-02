/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commandline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:33:14 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/02 11:46:50 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_main *main, t_tokens token)
{
	char	*command;

	(void)main;
	command = token.command[0];
	//make sure that in- and outfiles are correct at this point and pipes closed
	if (ft_strncmp(command, "echo\0", ft_strlen("echo\0")) == 0)
	{
		// echo(token.command);
		printf("Executing echo\n");
		exit(0);
	}
	else if (ft_strncmp(command, "cd\0", ft_strlen("cd\0")) == 0)
	{
		// cd();
		printf("Executing cd\n");
		exit(0);
	}
	else if (ft_strncmp(command, "pwd\0", ft_strlen("pwd\0")) == 0)
	{
		// pwd();
		printf("Executing pwd\n");
		exit(0);
	}
	else if (ft_strncmp(command, "export\0", ft_strlen("export\0")) == 0)
	{
		// export(main, token);
		printf("Executing export\n");
		exit(0);
	}
	else if (ft_strncmp(command, "unset\0", ft_strlen("unset\0")) == 0)
	{
		// unset(main, token);
		printf("Executing unset\n");
		exit(0);
	}
	else if (ft_strncmp(command, "env\0", ft_strlen("env\0")) == 0)
	{
		// env(main, token);
		printf("Executing env\n");
		exit(0);
	}
	else if (ft_strncmp(command, "exit\0", ft_strlen("exit\0")) == 0)
	{
		// pipe_exit();
		printf("Executing exit\n");
		exit(0);
	}
	return (0);
}

void	execute_command(t_main *main, t_tokens token)
{
	char	*path;
	// char	**env;

	path = get_path(main, token.command);
	if (path == NULL)
	{
		if (errno == 127)
			printf("Command not found: %s\n", token.command[0]);
		else
			perror("Error in getting path to command:");
		exit(1);
	}

	//make sure that in- and outfiles are correct at this point and pipes closed

	// env = transform_to_string_array(main->env_list);		//TODO
	// if (execve(path, token.command, env) == -1)
	// {
	// 	free(path);
	// 	//error
	// }

	//this is just for testing without env
	if (execv(path, token.command) == -1)
	{
		//make sure that path is always allocated by execution
		printf("Execv error on command %s\n", token.command[0]);
		free(path);
		//error
	}
}

//pipe[0]: read, pipe[1]: write
void	close_pipes_in_parent(int i, int num_of_pipes, int *pipe_left, int *pipe_right)
{
	if (num_of_pipes > 0 && i == 0)			//first command
		close (pipe_right[1]);
	else if (num_of_pipes == 0 && i > 0)	//last command
		close(pipe_left[0]);
	else if (num_of_pipes > 0 && i > 0)		//middle command
	{
		close(pipe_left[0]);
		close(pipe_right[1]);
	}
}

int	execute_commandline(t_main *main, t_tokens *tokens)
{
	int	pipe_left[2];
	int	pipe_right[2];
	int	*pids;
	int	num_of_pipes;
	int	i;
	int	status;		//just main->exit_code?

	num_of_pipes = main->num_of_pipes;
	pids = malloc ((num_of_pipes + 1) * sizeof(int));
	i = 0;
	while (num_of_pipes >= 0)
	{
		if (i > 0)
		{
			pipe_left[0] = pipe_right[0];
			pipe_left[1] = pipe_right[1];
		}
		if (num_of_pipes > 0)
		{
			if (pipe(pipe_right) == -1)
			{
				//some error
				printf("Pipe error\n");
			}
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Fork error\n");
			//error(NULL);
			exit(1);
		}
		if (pids[i] == 0)
		{		//TODO where and when does in- and output duping happen?
			if (!execute_builtin(main, tokens[i]))
				execute_command(main, tokens[i]);
		}
		else
		{
			close_pipes_in_parent(i, num_of_pipes, pipe_left, pipe_right);
			printf("Pipes closed\n");
		}
		num_of_pipes--;
		i++;
	}
	i = 0;
	while (i < main->num_of_pipes + 1)
	{
		printf("Process id %d\n", pids[i]);
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
		{
        	printf("Child %d exited with status %d\n", pids[i], WEXITSTATUS(status));
    	}
		i++;
	}
	free(pids);
	return (status);
}

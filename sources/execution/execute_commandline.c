/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commandline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:33:14 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/08 15:46:18 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_main *main, t_tokens token)
{
	char	*command;

	command = token.command[0];
	//make sure that in- and outfiles are correct at this point and pipes closed
	if (ft_strncmp(command, "echo\0", ft_strlen("echo\0")) == 0)
	{
		// return (echo(token.command));
		printf("Executing echo\n");
	}
	else if (ft_strncmp(command, "cd\0", ft_strlen("cd\0")) == 0)
	{
		// return (cd());
		printf("Executing cd\n");
	}
	else if (ft_strncmp(command, "pwd\0", ft_strlen("pwd\0")) == 0)
	{
		// return (pwd());
		printf("Executing pwd\n");
	}
	else if (ft_strncmp(command, "export\0", ft_strlen("export\0")) == 0)
	{
		// return (export(main, token));
		printf("Executing export\n");
	}
	else if (ft_strncmp(command, "unset\0", ft_strlen("unset\0")) == 0)
	{
		// return (unset(main, token));
		printf("Executing unset\n");
	}
	else if (ft_strncmp(command, "env\0", ft_strlen("env\0")) == 0)
	{
		// return (env(main, token));
		printf("Executing env\n");
	}
	else if (ft_strncmp(command, "exit\0", ft_strlen("exit\0")) == 0)
	{
		printf("Executing exit\n");
		return(exit_command(main));
	}
	return (0);
}

int	is_builtin(t_tokens token)
{
	char	*command;

	command = token.command[0];
	if (ft_strncmp(command, "echo\0", ft_strlen("echo\0")) == 0)
		return (1);
	else if (ft_strncmp(command, "cd\0", ft_strlen("cd\0")) == 0)
		return (1);
	else if (ft_strncmp(command, "pwd\0", ft_strlen("pwd\0")) == 0)
		return (1);
	else if (ft_strncmp(command, "export\0", ft_strlen("export\0")) == 0)
		return (1);
	else if (ft_strncmp(command, "unset\0", ft_strlen("unset\0")) == 0)
		return (1);
	else if (ft_strncmp(command, "env\0", ft_strlen("env\0")) == 0)
		return (1);
	else if (ft_strncmp(command, "exit\0", ft_strlen("exit\0")) == 0)
		return (1);
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

void	dup2_outfile(t_tokens token)
{
	int				outfile;
	t_redirect_node	node;

	node = token.outfiles;
	while (node != NULL)
	{
		if (node.type == OUTFILE)
			outfile = open(node.name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (node.type == APPEND)
			outfile = open(node.name, O_WRONLY | O_APPEND | O_CREAT, 0644);		//CHECK THAT IS CORRECT
		if (outfile == -1)
		{
			perror("In handle outfile");
			exit(1);
		}
		node = node.next;
	}
	if (dup2(outfile, STDIN_FILENO) == -1)
	{
		perror("dup2");
		//TODO is this correct?
		exit(1);
	}
	close(outfile);
}

void	handle_outfile(t_tokens token, int* pipe_right)
{
	int	outfile;

	if (pipe_right != NULL)
	{
		if (dup2(pipe_right[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			//TODO is this correct?
			exit(1);
		}
		close(pipe_right[0]);
		close(pipe_right[1]);
	}
	if (token.outfiles != NULL)
		dup2_outfile(token);
}

int	dup2_infile(t_tokens token)
{
	int	infile;
	t_redirect_node	node;

	node = token.infiles;
	while(node != NULL)
	{
		if (node != token.infiles)
			close(infile);
		infile = open(node, O_RDONLY);
		if (infile == -1)
		{
			//TODO handle error
			printf("Open error\n");
			exit(1);
		}
		node = node.next;
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("dup2");
		//TODO is this correct?
		exit(1);
	}
	close(infile);
}

void	handle_infile(t_tokens token, int* pipe_left)
{
	if (pipe_left != NULL)
	{
		if (dup2(pipe_left[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			//TODO is this correct?
			exit(1);
		}
		close(pipe_left[0]);
		close(pipe_left[1]);
	}
	if (token.infiles != NULL)
	{
		dup2_infile(token);
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

void	handle_infile_and_outfile(int i, int num_of_pipes, int **pipe_array, t_tokens token)
{
	if (i == 0 && num_of_pipes == 0)
	{
		handle_infile(token, NULL);
		handle_outfile(token, NULL);
	}
	else if (i > 0 && num_of_pipes == 0)
	{
		handle_infile(token, pipe_array[0]);
		handle_outfile(token, NULL);
	}
	else if (i == 0)
	{
		handle_infile(token, NULL);
		handle_outfile(token, pipe_array[1]);
	}
	else
	{
		handle_infile(token, pipe_array[0]);
		handle_outfile(token, pipe_array[1]);
	}
}

int	*malloc_pids(int amount)
{
	int	*pids;

	pids = malloc ((amount) * sizeof(int));
	if (pids == NULL)
	{
		perror(NULL);
		exit(1);
	}
	return (pids);
}

void	create_pipe(int **pipe_array)
{
	if (pipe(pipe_array[1]) == -1)
	{
		//some error
		printf("Pipe error\n");
		exit(1);
	}
}

int	create_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fork error\n");
		//error(NULL);
		exit(1);
	}
	return (pid);
}

void	execute_child_process(t_main *main, t_tokens token)
{
	int	status;

	if (is_builtin(token))
	{
		printf("Executing builtin in childprocess\n");
		status = execute_builtin(main, token);
		exit(status);
	}
	execute_command(main, token);
}

void	reassign_pipe(int **pipe_array)
{
	pipe_array[0][0] = pipe_array[1][0];
	pipe_array[0][1] = pipe_array[1][1];
}

int	execute_commandline(t_main *main, t_tokens *tokens)
{
	int	pipe_array[2][2];
	int	*pids;
	int	num_of_pipes;
	int	i;
	int	status;		//just main->exit_code?

	num_of_pipes = main->num_of_pipes;
	pids = malloc_pids(num_of_pipes + 1);
	i = 0;
	while (num_of_pipes >= 0)
	{
		if (is_builtin(tokens[i]) && num_of_pipes == 0 && i == 0)
		{
			handle_infile(tokens[i], NULL);
			handle_outfile(tokens[i], NULL);
			printf("Executing builtin in parent\n");
			execute_builtin(main, tokens[i]);
		}
		else
		{
			if (i > 0)
				reassign_pipe(pipe_array);
			if (num_of_pipes > 0)
				create_pipe(pipe_array);
			pids[i] = create_fork();
			if (pids[i] == 0)
			{
				handle_infile_and_outfile(i, num_of_pipes, pipe_array, tokens[i]);
				execute_child_process(main, tokens[i]);
			}
			else
			{
				close_pipes_in_parent(i, num_of_pipes, pipe_array[0], pipe_array[1]);
				printf("Pipes closed\n");
			}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:21:19 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/28 10:02:48 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <signal.h>

# define INFILE 100
# define HEREDOC 101
# define OUTFILE 102
# define APPEND 103
# define COMMAND 104
# define REDIRECT 105

typedef struct s_redirect_node t_redirect_node;

struct s_redirect_node
{
	char *name;
	char *delimiter;
	int type;
	t_redirect_node *next;
};

typedef struct s_tokens
{
	char	**command;
	t_redirect_node *infiles;
	t_redirect_node *outfiles;
}	t_tokens;

/**
 * char		*input;
 * char		**split_input;
 * t_list	*env_list;
 * int		exit_code;
 */
typedef struct s_main
{
	char	*input;
	char	**split_input;
	t_list	*env_list;
	t_tokens	**tokens;
	int		exit_code;
	int 	num_of_pipes;
	int		elements_in_command;
	int		id_command;
} t_main;

typedef struct s_parsing
{
	int id_char;
	int num_of_singles;
	int num_of_doubles;
	bool inside_singles;
	bool inside_doubles;
} t_parsing;

/*****************************************************************************/
	//INPUT AND SIGNALS
/*****************************************************************************/

//display prompt, readline, and save it in history
int	handle_inputs(char **input);

void setup_signal_handlers();

void handle_sigint(int sig);

/*****************************************************************************/
	//PARSING
/*****************************************************************************/

//Master parsing function that calls are other functions for parsing
int	parsing(t_main *main, t_tokens **commands);

//A split for minishell copyright 2024
int	split_input(t_main *main);

//Free all previous malloced splits and exit
void	exit_free_split_element_malloc_failed(t_main *main, int i);

//Split the input into individual elements and check for no spaces before/after symbols
int	add_elements_to_split_input(t_main *main, char *input);

//Returns 1 if the given char is a special character that we need to handle, else 0
int	char_is_special(char c);

//Add special character elements to the split_input array
void add_special_element(t_main *main, char *input, int *i, int split_index);

//Our own kind of tokenizing function of the input
int tokenize(t_main *main, t_tokens **command);

//Utility to check for redirection (< or >)
int	is_redirect(char c);

//Free command struct, free split_input, and exit with the given code
void free_split_and_tokens(t_main *main, t_tokens **command);

//Free the command_token utilizing ft_free_split
void free_token_commands(t_main *main, t_tokens **command);

//Free command tokens, command struct, and split_input, then exit with given code
void free_all_and_exit(t_main *main, t_tokens **command);

//Checks for a syntax error where there are two redirects in a row or a redirect then NULL
int check_for_redirect_error(t_main *main, t_tokens **command);

//Checks for and adds redirect_in and heredocs to the token struct
void add_in_or_heredoc(t_main *main, t_tokens **command, int cmd_id, int *spl_id);

//Checks for and adds redirect_out and redirect_append to the token struct
void add_out_or_append(t_main *main, t_tokens **command, int cmd_id, int *spl_id);

//Free and null the split_input
void	free_and_null_split_input(t_main *main);

//Checks for ' or "
int	is_quote(char c);

//Add command to token struct
void	add_command(t_main *main, t_tokens **tokens, int cmd_id, int *spl_id);

//Expand the environment variables
void expand_variables(t_main *main);

//Utilities for creating and adding elements to a linked list
t_redirect_node	*lstnew_redirect_node(char *name, int type);
t_redirect_node	*lstlast_redirect_node(t_redirect_node *lst);
void lstadd_back_redirect_node(t_redirect_node **lst, t_redirect_node *new);

//Free the redirect linked lists of the tokens
void free_token_redirects(t_main *main, t_tokens **tokens);

//Free everything if a linked list node fails to malloc
void free_and_exit_node_malloc_failed(t_main *main, t_tokens **tokens);

//Create and readline the heredoc fd's and put them in the tokens
void create_heredoc(t_main *main, t_tokens **tokens);

//Free and exit if malloc failed for expand variables
void free_and_exit_variable_malloc_failed(t_main *main, int i);

//Remove or interpret quotes and expand variables
void quotes_and_variables(t_main *main, t_tokens **tokens);

//Free all commands above the NULL and free all and exit
void free_and_exit_quote_malloc(t_main *main, t_tokens **tokens, int token_id, int cmd_id);

//Find the given $VAR in the env replace the given element if found
int	find_var_and_remalloc(t_main *main, char **str);

//Same as free all and exit but also free the split_input when there is a NULL in the middle
void	free_all_and_exit_with_free_split_middle(t_main *main, t_tokens **tokens);

//Removes outer double quotes and expands the environment vars within
int expand_quotes_and_vars(t_main *main, t_tokens **tokens, char **str);

//Free and  exit when malloc fails in combine elements for quote_split
void	free_and_exit_combine_elements(t_main *main, t_tokens **tokens, char ***quote_split);

//Expansion of quote and vars in the middle of words or double quotes
int	inner_expansion(t_main *main, char **str);

//Remove the outer quotes of the given string
int	remove_outside_quotes(char **str);

//Create an array of strings that splits the elements of a string into variables and quotes
int	create_quote_split(char *str, char ***quote_split);

/*****************************************************************************/
	//ENVIRONMENT
/*****************************************************************************/

/**
 * Frees all nodes an their content in the environment linked list
 * 
 * @param env_list pointer to the linked list to free
 */
void    free_environment(t_list **env_list);

/**
 * Finds and returns a node with the same key as variable
 * 
 * @param main the main struct of the program
 * @param variable a key-value pair in form KEY=value to find node for
 * @returns pointer to a node with the same key as variable
 */
t_list	*find_node(t_main *main, char *variable);

/**
 * Adds a variable to the environment (a new node to the linked list)
 * 
 * @param main pointer to the main struct
 * @param content the content of the node
 */
int    add_variable(t_main *main, char *content);

/**
 * Updates the value of the variable key in the env linked list
 * 
 * @param main pointer to the main struct
 * @param var the key value pair to update
 */
int	update_variable(t_main *main, char *var);

/**
 * Duplicates (mallocs) the values from envp into a linked list
 * 
 * @param envp the environment pointer gotten from main
 * @param main the main struct of the program
 */
t_list	*copy_env(char *envp[], t_main *main);

/**
 * Prints the contents of all nodes of the linked list
 * 
 * @param env_list the linked list to print
 */
void	print_linked_list(t_list *env_list);

/**
 * Helper function for print_linked_list function
 */
void	print_list_content(void *content);

/**
 * Frees and removes the node that has key varaible_key from the linked list
 * 
 * @param main the main struct of the program
 * @param variable_key the key of the variable to remove
 * @note variable_key needs to have '=' sign! E.g. "PATH="
 */
void	remove_variable(t_main *main, char *variable_key);

char	**convert_list_to_array(t_list *env_list);

/*****************************************************************************/
	//BUILTINS
/*****************************************************************************/

/**
 * Prints the words after echo. If flag -n is given, does not print the newline
 * after last word.
 * 
 * @param main the main struct of the program
 * @param token the token that echo command is part of
 * @returns 0 on success, 1 on error
 */
int    echo(t_main *main, t_tokens token);

/**
 * Checks if the given key is already in the env list.
 * 
 * @param main the main struct of the program
 * @param var a variable in form VAR=value
 * @returns 1 when key was found, 0 when not found
 */
int		existing_key(t_main *main, char *var);

/**
 * Checks if the key of the variable to export has forbidden characters or in
 * forbidden form. I.e. a key kan only contain digits, letters and '_'. Digits
 * can not be in the beginning.
 * 
 * @param var the variable in form VAR=value
 * @returns 1 if key is forbidden, 0 if key is ok
 */
int		forbidden_key(char *var);

/**
 * Exports a variable of form VAR=value to the env list
 * 
 * @param main the main struct of the program
 * @param token the token to be executed
 * @returns 0 on success, 1 on error
 */
int	export(t_main *main, t_tokens token);

/**
 * Unsets a variable from the env list.
 * 
 * @param main the main struct of the program
 * @param token the token to be executed
 * @returns 0 on success, 1 on error
 */
int	unset(t_main *main, t_tokens token);

/**
 * Prints the current working directory
 * 
 * @param main the main struct of the program
 * @param token the token that pwd command is part of
 * @returns 0 on success, 1 on error
 */
int	pwd(t_main *main, t_tokens token);

char	*get_pwd(void);

int	cd(t_main *main, t_tokens token);

/**
 * Prints the updated environment variables
 * 
 * @param main the main struct of the program
 * @param token the token that env command is part of
 * @returns 0 on success, 1 on error
 */
int env(t_main *main, t_tokens token);

int	exit_command(t_main *main, t_tokens token, int parent, int open_fds[2]);

/*****************************************************************************/
	//EXECUTION
/*****************************************************************************/

/**
 * Executes one commandline, by creating the necessary pipes and forking into
 * childprocesses when applicable. 
 * 
 * @param main the main struct of the program
 * @param tokens array of tokens to execute
 * @returns the exitstatus of the last executable
 */
int	execute_commandline(t_main *main, t_tokens *tokens);

/**
 * Checks if command is a builtin or not
 * 
 * @param the token that command is part of
 * @returns 1 if command is builtin, 0 if not
 */
int	is_builtin(t_tokens token);

/**
 * Closes the necessary pipe-filedescriptors depending on the executed commands
 * position in the command line.
 * 
 * @param i index of the command executed in commandline
 * @param num_of_pipes number of pipes left in commandline
 * @param pipe_left array of filedescriptors for the left-hand side pipe of command
 * @param pipe_right array of filedescriptors for the right-hand side pipe of command
 */
void	close_pipes_in_parent(int i, int num_of_pipes, int *pipe_left, int *pipe_right);

/**
 * Finds path to the command and execues it with execve
 * 
 * @param main the main struct of the program
 * @param token  the token to execute
 */
void	execute_command(t_main *main, t_tokens token, int *pids);

/**
 * Calls the right builtin function to execute it
 * 
 * @param main the main struct of the program
 * @param token  the token to execute
 */
int	execute_builtin(t_main *main, t_tokens token, int parent, int open_fds[2]);

/**
 * Executes either a builtin or a command as a child process.
 * If a builtin is executed, the process is exited with the return
 * value of the builtin-function.
 * 
 * @param main the main struct of the program
 * @param token  the token to execute
 */
void	execute_child_process(t_main *main, t_tokens token, int *pids);

/**
 * Executes a bultin in the parent process. Redirects STDIN and STDOUT
 * to correct files if necessary. After execution restores STDIN and SDTOUT
 * filedescriptors.
 * 
 * @param main the main struct of the program
 * @param token  the token to execute
 */
void	execute_builtin_in_parent(t_main *main, t_tokens token);

char	*find_path(t_main *main, char *command, int *pids);

char	*get_path_variable(t_main *main);

char	**get_split_paths(char *path_variable, t_main *main, int *pids);

int	set_path_if_executable(char *env_path, char *command, char **command_path);

char	*get_path(t_main *main, char **command, int *pids);

int	empty_command(char *command);

int	is_direcotory(char *command);

int	is_path_to_executable(char *command);

int	is_path_to_file(char *command);

/**
 * Makes sure that STDIN and STDOUT are redirected to the right files
 * based on number of pipes and position of command in pipeline
 * 
 * @param i position of command in pipeline, first command: i = 0;
 * @param num_of_pipes the number of pipes left to be written into in
 * the pipeline
 */
int	handle_infile_and_outfile(int i, int num_of_pipes,
	int pipe_array[2][2], t_tokens token);

/**
 * Redirects STDIN with dup2 to:
 * (1) pipe: if there is a pipe and no infile
 * (2) infile: if there is infile(s)
 * (3) nowhere: if there is no pipe and no infile(s)
 * 
 * @param token the token to handle infile for
 * @param pipe_left array of ints for the left-hand side pipe,
 * 	NULL if there is no pipe
 */
int	handle_infile(t_tokens token, int* pipe_left);

/**
 * Redirects STDOUT with dup2 to:
 * (1) pipe: if there is a pipe and no outfile
 * (2) outfile: if there is outfile(s)
 * (3) nowhere: if there is no pipe and no outfile(s)
 * 
 * @param token the token to handle outfile for
 * @param pipe_right array of ints for the right-hand side pipe,
 * 	NULL if there is no pipe
 */
int	handle_outfile(t_tokens token, int* pipe_right);

/**
 * Loops through all infiles, opens them and redirects STDIN with dup2
 * to the last one.
 * 
 * @param token the token to handle infile for
 */
int	dup2_infile(t_tokens token);

/**
 * Loops through all outfiles, opens them and redirects STDOUT with dup2
 * to the last one.
 * 
 * @param token the token to handle outfile for
 */
int	dup2_outfile(t_tokens token);

void	free_all_in_child(t_main *main, int *pids);

#endif

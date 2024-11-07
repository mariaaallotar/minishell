/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:21:19 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/07 10:25:33 by maheleni         ###   ########.fr       */
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

extern int signal_received;

typedef struct s_redirect_node t_redirect_node;

struct s_redirect_node
{
	char *name;
	char *delimiter;
	bool delimiter_has_quotes;
	int type;
	t_redirect_node *next;
};

typedef struct s_tokens
{
	char	**command;
	t_redirect_node *redirects;
}	t_tokens;

typedef struct s_expand
{
	bool is_heredoc;
	char quote_type;
}	t_expand;

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
/*****************************************************************************/

	//INPUT AND SIGNALS

/*****************************************************************************/
/*****************************************************************************/

//display prompt, readline, and save it in history
int	handle_inputs(char **input);

void	activate_readline_signals(void);

void	activate_heredoc_signals(void);

void handle_sigint_readline(int sig);

void	ignore_sigint(void);

/*****************************************************************************/
/*****************************************************************************/

	//PARSING

/*****************************************************************************/
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
void tokenize(t_main *main, t_tokens **command);

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

//Utilities for creating and adding elements to a linked list
t_redirect_node	*lstnew_redirect_node(char *name, int type);
t_redirect_node	*lstlast_redirect_node(t_redirect_node *lst);
void lstadd_back_redirect_node(t_redirect_node **lst, t_redirect_node *new);

//Free the redirect linked lists of the tokens
void free_token_redirects(t_main *main, t_tokens **tokens);

//Free everything if a linked list node fails to malloc
void free_and_exit_node_malloc_failed(t_main *main, t_tokens **tokens);

//Create and readline the heredoc fd's and put them in the tokens
int	create_heredoc(t_main *main, t_tokens **tokens);

//Free and exit if malloc failed for expand variables
void free_and_exit_variable_malloc_failed(t_main *main, int i);

//Remove or interpret quotes and expand variables
void quotes_and_variables(t_main *main, t_tokens **tokens);

//Free all commands above the NULL and free all and exit
void free_and_exit_quote_malloc(t_main *main, t_tokens **tokens, int token_id, int cmd_id);

//Find the given $VAR in the env replace the given element if found
int	find_var_in_env(t_main *main, char **str);

//Same as free all and exit but also free the split_input when there is a NULL in the middle
void	free_all_and_exit_with_free_split_middle(t_main *main, t_tokens **tokens);

//Removes outer double quotes and expands the environment vars within
int	expand_quotes_and_vars(t_main *main, t_tokens **tokens, char **str, bool is_heredoc);

//Free and  exit when malloc fails in combine elements for quote_split
void	free_and_exit_combine_elements(t_main *main, t_tokens **tokens, char ***quote_split);

//Expansion of quote and vars in the middle of words or double quotes
int	inner_expansion(t_main *main, char **str, bool is_heredoc);

//Remove the outer quotes of the given string
int	remove_outside_quotes(char **str);

//Create an array of strings that splits the elements of a string into variables and quotes
int	create_quote_split(char *str, char ***quote_split);

//Check for single or double quotes on the outside of the given string
int check_for_outside_quotes(char *str, char *quote_type);

//Add the given quote type to the outside of the given string
int add_quotes_back_to_str(char **str, char quote_type);

//Returns the length of one element of the quote_split for expanding quotes and vars
int	get_split_element_len(char *str, int i);

//Add elements to the quote split in quote and variable expansion
void	add_element_to_quote_split(char ***quote_split, char *str, int id_split, int id_str);

//Expands variables in the quote_split or performs 'inner_expanion' further expanding quotes and vars
void	expand_vars_or_do_inner_expansion(t_main *main, t_tokens **tokens, char ***quote_split, t_expand expand);

//Free and exit for malloc fail in expand_vars_or_do_inner_expansion
void	free_and_exit_quote_split_expand(t_main *main, t_tokens **tokens, char ***quote_split, int i);

//Check for adding back quotes to heredoc strings if they were removed during expansion
int check_for_heredoc_quotes(char **str, bool is_heredoc, char quote_type, char ***quote_split);

//Skip spaces and tabs in given string starting at given index
void	skip_spaces_and_tabs(char *input, int *id_input);

//Check if given character is a space or tab or special char and if the quotes are closed
int	char_is_space_or_special_and_quotes_are_closed(char c, t_parsing p);

//Update the 'inside status' of the given struct
void	update_inside_status(t_parsing *p);

//Update the number of the given quote for the given struct
void	update_number_of_quotes(char c, t_parsing *p);

//Check for unclosed quotes in initial input parsing
int	check_for_unclosed_quotes(t_parsing p);

//Checks for a pipe error where there is a pipe then nothing following
int	check_for_pipe_error(t_main *main, t_tokens **tokens);

/*****************************************************************************/
/*****************************************************************************/

	//ENVIRONMENT

/*****************************************************************************/
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
 */
int	remove_variable(t_main *main, char *variable_key);

char	**convert_list_to_array(t_list *env_list);

/*****************************************************************************/
/*****************************************************************************/

	//BUILTINS

/*****************************************************************************/
/*****************************************************************************/

/**
 * Changes the working directory of the shell. Also updates the PWD and OLDWPD
 * variable in the env list.
 * 
 * @param main pointer to the main struct of the program
 * @param token the token that cd command is part of
 * @returns 
 */
int	cd(t_main *main, t_tokens token);

/**
 * Gets the path to home directory from env list.
 * 
 * @param main pointer to the main struct of the program
 * @returns The path as a string, NULL if HOME variable is unset
 */
char	*get_path_to_home(t_main *main);

/**
 * Updates the PWD and OLDPWD variables in env list depending on the key
 * 
 * @param main pointer to the main struct of the program
 * @param key the key of the variable to update (only PWD or OLDPWD)
 */
int	update_directory_variable(t_main *main, char *key);

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
 * Prints the arguments
 * 
 * @param i position of first aguent to print
 * @param has_new_line 1 if will print newline at the end, 0 if not
 * @param token the token that echo command is part of
 */
void	print_echo_arguments(int i, int has_new_line, t_tokens token);

/**
 * Checks if echo has the flag -n or not, indicating if the trailing newline
 * will be printed or not.
 * 
 * @param str the string that will hold the -n or first argument
 * @returns 1 if -n flag is present, 0 otherwise
 */
int	has_no_newline_flag(char *str);

/**
 * Prints the current environment variables
 * 
 * @param main the main struct of the program
 * @param token the token that env command is part of
 * @returns 0 on success, 1 on error
 */
int env(t_main *main, t_tokens token);

/**
 * Exits the program with the given value, 0 if no argument is given
 * 
 * @param main the main struct of the program
 * @param token the token that exit command is part of
 * @param parent 1 if we are in parent process, 0 if in child process
 * @param open_fds array of the open file descriptors
 * @returns the exitcode if in child process
 */
int	exit_command(t_main *main, t_tokens token, int parent, int open_fds[2]);

/**
 * If in child process: Returns with exit_code.
 * If in parent process: Frees and closes everyhitng and exits.
 * 
 * @param main the main struct of the program
 * @param open_fds array of the open file descriptors
 * @param exit_code the code to exit with or return
 */
void	free_and_exit(t_main *main, int open_fds[2], int exit_code);

/**
 * Sets the numeric value given with the command into temp_code.
 * 
 * @param element the element that can be the numeric value
 * @param exit_code pointer to variable to hold the exit code in
 * @returns 1 if numeric value, 0 if not
 */
int	int_after_exit(char *element, int *exit_code);

/**
 * Exports a variable of form VAR or VAR=value to the env list
 * 
 * @param main the main struct of the program
 * @param token the token to be executed
 * @returns 0 on success, 1 on error
 */
int	export(t_main *main, t_tokens token);

/**
 * Prints error message and the variable that is refers to
 * 
 * @param argument the key-value pair that is to be printed
 * @returns 1, that will be set to the return value of export command
 */
int	print_forbidden_key(char *argument);

/**
 * Checks if the key of the variable to export has forbidden characters or in
 * forbidden form. I.e. a key can only contain digits, letters and '_'. Digits
 * can not be in the beginning.
 * 
 * @param var the variable in form VAR=value
 * @returns 1 if key is forbidden, 0 if key is ok
 */
int		forbidden_key(char *var);

/**
 * Checks if the given key is already in the env list.
 * 
 * @param main the main struct of the program
 * @param var a variable in form VAR=value
 * @returns 1 when key was found, 0 when not found
 */
int		existing_key(t_main *main, char *var);

/**
 * Prints all exported variables in ASCII order
 * 
 * @param main the main struct of the program
 * @returns 0 on success, 1 on fail
 */
int	export_without_args(t_main *main);

/**
 * Finds the node that has the contents next in ascii order
 * 
 * @param prev_node pointer to the previously printed node
 * @param biggest_node pointer to the node that will be printed last
 * @param env_list pointer to the env_list (export_list) that will be printed
 * @returns the node to print the contents of next
 */
t_list	*get_next_node(t_list *prev_node, t_list *biggest_node,
	t_list *env_list);

/**
 * Finds and returns the node that will be printed last
 * 
 * @param env_list pointer to the env_list (export_list) that will be printed
 * @returns the node that will be printed last
 */
t_list	*get_biggest_node(t_list *env_list);

/**
 * Finds and returns the node that will be printed first
 * 
 * @param env_list pointer to the env_list (export_list) that will be printed
 * @returns the node that will be printed first
 */
t_list	*get_smallest_node(t_list *env_list);

/**
 * Prints the current working directory
 * 
 * @param main the main struct of the program
 * @param token the token that pwd command is part of
 * @returns 0 on success, 1 on error
 */
int	pwd(t_main *main, t_tokens token);

/**
 * Gets and returns the current working directory in a buffer that is malloced
 * by getcwd()
 * 
 * @returns the path to the current working direcotry
 */
char	*get_pwd(void);

/**
 * Removes a variable from the env list (export list)
 * 
 * @param main the main struct of the program
 * @param token the token to be executed
 * @returns 0 on success, 1 on error
 */
int	unset(t_main *main, t_tokens token);

/*****************************************************************************/
/*****************************************************************************/

	//EXECUTION

/*****************************************************************************/
/*****************************************************************************/

/**
 * Executes one commandline, by creating the necessary pipes and forking into
 * childprocesses when applicable. 
 * 
 * @param main the main struct of the program
 * @param tokens array of tokens to execute
 */
void	execute_commandline(t_main *main, t_tokens *tokens);

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


void	close_pipes_on_error(int *pipe);

int	create_fork(int i, int num_of_pipes, int pipe_array[2][2], int *pids);

void	reassign_pipe_right_to_left(int pipe_array[2][2]);

int	prepare_pipes(int i, int num_of_pipes, int pipe_array[2][2], int *pids);

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

void	restore_stdin_stdout(t_main *main, int original_stdin,
	int original_stdout);

int	is_builtin_not_part_of_pipeline(t_tokens token, int num_of_pipes);

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
int	execute_builtin_in_parent(t_main *main, t_tokens token, int num_of_pipes); //TODO check params

char	*find_path(t_main *main, char *command, int *pids);

char	*get_path_variable(t_main *main);

char	**get_split_paths(char *path_variable, t_main *main, int *pids);

int	set_path_if_executable(char *env_path, char *command, char **command_path);

char	*get_path(t_main *main, char **command, int *pids);

int	empty_command(char *command);

int	is_directory(char *command);

int	is_path_to_executable(char *command);

int	is_path_to_file(char *command);

void	free_all_in_child(t_main *main, int *pids);

void	free_all_in_parent(t_main *main);

void	remove_heredocs(t_main *main, t_tokens **tokens);

int	handle_redirects(t_tokens token);

int	dup2_file(int file, int std_fileno);

int	open_outfile(t_redirect_node *node);

int	open_infile(t_redirect_node	*node);

int redirect_pipes(int i, int num_of_pipes, int pipe_array[2][2]);

int redirect_pipe_right(int* pipe_right);

int redirect_pipe_left(int* pipe_left);

#endif
